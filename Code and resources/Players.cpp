#include "Players.h"

using namespace std;
Players::Players(std::string name, sf::Vector2f LocateMap, bool RightSide):m_map(LocateMap), m_fleet()
{
	m_name = name;
	SetShip = 0;
	RSide = RightSide;
	ship_image= m_fleet.GetShipImage();
	ship_image.createMaskFromColor(sf::Color(0, 0, 0));
	ship_texture.loadFromImage(ship_image);
	ship_texture.setSmooth(true);
	ship_sprite.setTexture(ship_texture);
	ship_sprite.setColor(sf::Color(0, 0, 0));
}
void Players::DrawOur(sf::RenderWindow& m_window) 
{
	m_fleet.DrawAll(m_window);
	m_map.Draw(m_window);
}
void Players::DrawEnemy(sf::RenderWindow& m_window) 
{
	m_fleet.Draw(m_window);
	m_map.Draw(m_window);
}
void Players::DrawShip(sf::RenderWindow& m_window, int& start, int& step, int& dx, int k, int y) 
{
	ship_sprite.setPosition(start + dx,y);
	dx += step;
	if (!m_fleet.AliveShip(k)) ship_sprite.setColor(sf::Color(117, 125, 143));
	m_window.draw(ship_sprite);
	ship_sprite.setColor(sf::Color(0, 0, 0));
}
void  Players::DrawShips(sf::RenderWindow& m_window)
{
	sf::Vector2f location = m_map.GetLocationMap();
	int start, step;
	if (RSide)
	{
		start = location.x - 35;
		step = 54 + 4;
	}
	else
	{
		start = location.x + 54 * 10 - 15;
		step = -54 - 4;
	}

	int dX = 0;
	ship_sprite.setTextureRect(sf::IntRect(54 * 3, 0, 54, 54));
	for (int k = 6; k < 10; k++)
	{
		DrawShip(m_window, start, step, dX, k, 775 + 54 * 3);
	}
	ship_sprite.setTextureRect(sf::IntRect(54 * 2, 0, 54, 54 * 2));
	for (int k = 3; k < 6; k++)
	{
		DrawShip(m_window, start, step, dX, k, 775 + 54 * 2);
	}
	ship_sprite.setTextureRect(sf::IntRect(54, 0, 54, 54 * 3));
	for (int k = 1; k < 3; k++)
	{
		DrawShip(m_window, start, step, dX, k, 775 + 54);
	}
	ship_sprite.setTextureRect(sf::IntRect(0, 0, 54, 54 * 4));
	DrawShip(m_window, start, step, dX, 0, 775);
}
void Players::SetCoords(std::vector<sf::Vector2i>& mlist)
{
	mlist.clear();
	for (int i = 0; i < 10; i++)
		for (int k = 0; k < 10; k++)
		{
			mlist.push_back(sf::Vector2i(i, k));
		}
}
int generateNum()
{
	static int s = 0;
	return ++s;
}
int Players::GetRandomNumber(int min, int max)
{
	// Set a random number generator
	srand(time(NULL)+ generateNum());
	int num = min + rand() % (max - min + 1);

	return num;
}

bool Players::SetRandomShip() 
{
	std::vector <sf::Vector2i> mlist;
	SetCoords(mlist);
	SetRand(4, 0, mlist);
	for (int i = 1; i < 3; i++) SetRand(3, i, mlist);
	for (int i = 3; i < 6; i++) SetRand(2, i, mlist);
	for (int i = 6; i < 10; i++) SetRand(1, i, mlist);
	return true;
}


///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


void Players::SetRand(int type, int num, std::vector<sf::Vector2i>& mlist)
{
	bool end = false;
	sf::Vector2i coords;
	std::vector<sf::Vector2i> list2 = mlist;
	while (!end)
	{
		if (GetRandomNumber(0, 1) == 0) //down
		{
			coords = list2[GetRandomNumber(0, list2.size() - 1)];
			if (m_map.SetShip(coords, Num_Ship(num), type))
			{
				m_fleet.SetShip(m_map.GetCoordsForShip(coords), num, false);
				end = true;
				int i, j, k, g;
				m_map.SetRange(coords, type, i, j, k, g);
				for (int i1 = i; i1 <= j; i1++)
				{
					for (int k1 = k; k1 <= g; k1++)
					{
						it = find(mlist.begin(), mlist.end(), sf::Vector2i(i1, k1));
						if (it != mlist.end()) mlist.erase(it);
					}
				}
			}
			else
			{
				if (m_map.SetShip(coords, Num_Ship(num), type, WayShip::RIGHT))
				{
					m_fleet.SetShip(m_map.GetCoordsForShip(coords), num, true);
					end = true;
					int i, j, k, g;
					int t = coords.x;
					coords.x = coords.y;
					coords.y = t;
					m_map.SetRange(coords, type, k, g, i, j);
					for (int i1 = i; i1 <= j; i1++)
					{
						for (int k1 = k; k1 <= g; k1++)
						{
							it = find(mlist.begin(), mlist.end(), sf::Vector2i(i1, k1));
							if (it != mlist.end()) mlist.erase(it);
						}
					}
				}
				else
				{
					list2.erase(find(list2.begin(), list2.end(), coords));
				}
			}
		}
		else
		{
			coords = list2[GetRandomNumber(0, list2.size() - 1)];
			if (m_map.SetShip(coords, Num_Ship(num), type, WayShip::RIGHT))
			{
				m_fleet.SetShip(m_map.GetCoordsForShip(coords), num, true);
				end = true;
				int i, j, k, g;
				int t = coords.x;
				coords.x = coords.y;
				coords.y = t;
				m_map.SetRange(coords, type, k, g, i, j);
				for (int i1 = i; i1 <= j; i1++)
				{
					for (int k1 = k; k1 <= g; k1++)
					{
						it = find(mlist.begin(), mlist.end(), sf::Vector2i(i1, k1));
						if (it != mlist.end()) mlist.erase(it);
					}
				}
			}
			else
			{
				if (m_map.SetShip(coords, Num_Ship(num), type))
				{
					m_fleet.SetShip(m_map.GetCoordsForShip(coords), num, false);
					end = true;
					int i, j, k, g;
					m_map.SetRange(coords, type, i, j, k, g);
					for (int i1 = i; i1 <= j; i1++)
					{
						for (int k1 = k; k1 <= g; k1++)
						{
							it = find(mlist.begin(), mlist.end(), sf::Vector2i(i1, k1));
							if (it != mlist.end()) mlist.erase(it);
						}
					}
				}
				else
				{
					list2.erase(find(list2.begin(), list2.end(), coords));
				}
			}
		}
	}
}