#include "Map.h"

Map::Map(sf:: Vector2f mLocation) 
{
	sf::Image ig;
	if (!ig.loadFromFile("resources/images/Ceil2.png"))
		throw std::runtime_error("ResourceHolder::loadTexture - Failed to load resources / images / Ceil2.png");
	ig.createMaskFromColor(sf::Color(255, 255, 255));
	ig.createMaskFromColor(sf::Color(234, 236, 239));
	Ceil_Texture.loadFromImage(ig);
	Location = mLocation;
	Ceil_Sprite.setTexture(Ceil_Texture);


}

bool Map::SetRange(sf::Vector2i A, int type, int& i, int& j, int& k, int& g ) //ñòàâèò äèàïîçîí
{
	if (A.y + type > 10) return false;
	if (A.x == 0) i = 0;
	else i = A.x - 1;

	if (A.x == 9) j = 9;
	else j = A.x + 1;

	if (A.y == 0) k = 0;
	else k = A.y - 1;

	if (A.y + type == 10) g = A.y + type-1;//g = A.y + type
	else g = A.y + type ;//g = A.y + type+1
	return true;
}
bool Map::CheckCeil(sf::Vector2i A, int type, WayShip mway)
{
	int i, j, k, g;
	if (mway == WayShip::DOWN)
	{
		if (!SetRange(A, type, i, j, k, g)) return false;
	}
	else
	{
		int t = A.x;
		A.x = A.y;
		A.y = t;
		if (!SetRange(A, type, k, g, i, j)) return false;
	}
	for (int i1 = i; i1 <= j; i1++)
	{
		for (int k1 = k; k1 <= g; k1++)
		{
			if (OurMap[i1][k1].number_ship != Num_Ship::NONE) return false;
		}
	}
	return true;
}
void Map::Clear(sf::Vector2i A, int type, WayShip mway)//ñäåëàòü clear äëÿ äâóõ ïîëîæåíèé
{
	if (mway== WayShip::DOWN)
		for (int i = A.y; i < A.y + type; i++)
		{
			OurMap[A.x][i].number_ship = Num_Ship::NONE;
		}
	else 
		for (int i = A.x; i < A.x + type; i++)
		{
			OurMap[i][A.y].number_ship = Num_Ship::NONE;
		}
}

bool Map::SetShip(sf::Vector2i A, Num_Ship num, int type, WayShip mway) //ÏÐÎÂÅÐÈÒÜ ÂÍÈÌÀÒÅËÜÍÎ
{

		if (!CheckCeil(A, type, mway)) return false;
		if (mway == WayShip::DOWN)
		{
			for (int i = A.y; i < A.y + type; i++)
			{
				OurMap[A.x][i].number_ship = num;
			}
			return true;
		}
		else 
		{
			for (int i = A.x; i < A.x + type; i++)
			{
				OurMap[i][A.y].number_ship = num;
			}
			return true;
		}

}

bool Map:: RotateShip(sf::Vector2i A, int type) 
{
	if (type == 1) return true;
	Num_Ship n = OurMap[A.x][A.y].number_ship;
	WayShip mway;
	if (A.x<9 && OurMap[A.x + 1][A.y].number_ship != Num_Ship::NONE) mway = WayShip::RIGHT;
	else mway = WayShip::DOWN;
	Clear(A, type, mway);
	if (mway == WayShip::DOWN && !CheckCeil(A, type, WayShip::RIGHT))
	{
		SetShip(A, n, type, mway);
		return false;
	}
	else 
		if (mway == WayShip::DOWN)
		{
			for (int i = A.x; i < A.x + type; i++)
			{
				OurMap[i][A.y].number_ship = n;
			}
			return true;
		}
	if (mway == WayShip::RIGHT && !CheckCeil(A, type, WayShip::DOWN))
	{
		SetShip(A, n, type, mway);
		return false;
	}
	else
		if (mway == WayShip::RIGHT)
		{
			for (int i = A.y; i < A.y + type; i++)
			{
				OurMap[A.x][i].number_ship = n;
			}
			return true;
		}
}
void Map::ClearShip(sf::Vector2i A, int type)
{
	if (A.x < 9 && OurMap[A.x + 1][A.y].number_ship != Num_Ship::NONE) Clear(A, type, WayShip::RIGHT);
	else Clear(A, type, WayShip::DOWN);
}
void Map::KillShip(sf::Vector2i A, int type) 
{
	int i, j, k, g;
	if (type != 1 && A.y+1<=9 && OurMap[A.x][A.y + 1].number_ship != Num_Ship::NONE) 
		SetRange(A, type, i, j, k, g);
	else 
	{
		int t = A.x;
		A.x = A.y;
		A.y = t;
		SetRange(A, type, k, g, i, j);
	}
	for (int i1 = i; i1 <= j; i1++)
	{
		for (int k1 = k; k1 <= g; k1++)
		{
			//if ((i1 != A.x) || (k1 < A.y) || (k1 == A.y + type)) 
				OurMap[i1][k1].shot = true;
		}
	}
}

bool Map::Move(sf::Vector2i A, Num_Ship& D) 
{
	if (OurMap[A.x][A.y].shot == true)  return false;
	OurMap[A.x][A.y].shot = true;
	D = OurMap[A.x][A.y].number_ship;
	return true;
}

void Map::SetFocus(sf::Vector2i A) 
{
	OurMap[A.x][A.y].InFocus = true;
}

bool Map::GetMapCoords(sf::Vector2f A, sf::Vector2i& B)
{
	B.x = floor((A.x - Location.x) / Ceil_Size);
	B.y = floor((A.y - Location.y) / Ceil_Size);
	return ((B.x >= 0 && B.y >= 0)&&(B.x<=9 && B.y<=9));
}
sf::Vector2f  Map::GetCoordsForShip(sf::Vector2i A)
{
	sf::Vector2f newCoords;
	newCoords.x = A.x * Ceil_Size+Ceil_Size/2 + Location.x;
	newCoords.y = A.y * Ceil_Size + Ceil_Size/2 + Location.y;
	return newCoords;
}
bool Map::GetShipWayDown(sf::Vector2f A)
{
	sf::Vector2i B;
	GetMapCoords(A, B);
	if (A.y + 1 <= 9 && OurMap[B.x][B.y + 1].number_ship != Num_Ship::NONE) return true;
	return false;
}

void Map::Draw(sf:: RenderWindow& mWindow) 
{
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
			if (OurMap[i][j].shot == true && OurMap[i][j].number_ship != Num_Ship::NONE)
			{
				Ceil_Sprite.setTextureRect(sf::IntRect(Ceil_Size, 0, Ceil_Size, Ceil_Size));
				Ceil_Sprite.setPosition(Location.x + Ceil_Size*i, Location.y +Ceil_Size*j);
				mWindow.draw(Ceil_Sprite);
			}
			if (OurMap[i][j].shot == true && OurMap[i][j].number_ship == Num_Ship::NONE)
			{
				Ceil_Sprite.setTextureRect(sf::IntRect(0, 0, Ceil_Size, Ceil_Size));
				Ceil_Sprite.setPosition(Location.x + Ceil_Size * i, Location.y + Ceil_Size * j);
				mWindow.draw(Ceil_Sprite);
			}
			if (OurMap[i][j].InFocus && OurMap[i][j].shot!=true) 
			{
				Ceil_Sprite.setTextureRect(sf::IntRect(Ceil_Size*2, 0, Ceil_Size, Ceil_Size));
				Ceil_Sprite.setPosition(Location.x + Ceil_Size * i, Location.y + Ceil_Size * j);
				mWindow.draw(Ceil_Sprite);
				OurMap[i][j].InFocus = false;
			}
		}
	}
}
bool Map::HaveMap(sf::Vector2f a) 
{
	return (Location.x < a.x&& a.x < Location.x + Ceil_Size * 10 && Location.y < a.y&& a.y < Location.y + Ceil_Size * 10);
}
void Map::ClearMap() 
{
	for (int i = 0; i < 10; i++) 
	{
		for (int k = 0; k < 10; k++) 
		{
			OurMap[i][k].shot = false;
			OurMap[i][k].number_ship = Num_Ship::NONE;
			OurMap[i][k].InFocus = false;
		}
	}
}
int Map::GetShipType(Num_Ship n) 
{
	switch (n)
	{
	case Num_Ship::NONE:
		return 0;
		break;
	case Num_Ship::SHIP_4_1:
		return 4;
		break;
	case Num_Ship::SHIP_3_1:
		return 3;
		break;
	case Num_Ship::SHIP_3_2:
		return 3;
		break;
	case Num_Ship::SHIP_2_1:
		return 2;
		break;
	case Num_Ship::SHIP_2_2:
		return 2;
		break;
	case Num_Ship::SHIP_2_3:
		return 2;
		break;
	case Num_Ship::SHIP_1_1:
		return 1;
		break;
	case Num_Ship::SHIP_1_2:
		return 1;
		break;
	case Num_Ship::SHIP_1_3:
		return 1;
		break;
	case Num_Ship::SHIP_1_4:
		return 1;
		break;
	default:
		break;
	}
}