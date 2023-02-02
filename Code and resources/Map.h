#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
enum class Num_Ship {
	NONE = -1,
	SHIP_4_1 = 0,
	SHIP_3_1,
	SHIP_3_2,
	SHIP_2_1,
	SHIP_2_2,
	SHIP_2_3,
	SHIP_1_1,
	SHIP_1_2,
	SHIP_1_3,
	SHIP_1_4,
};
enum class WayShip {
	RIGHT=0, 
	DOWN
};
using namespace std;
class Map
{
private:
	struct InfoCell
	{	
		bool shot;  
		Num_Ship number_ship;
		bool InFocus;
		InfoCell() 
		{
			InFocus = false;
			shot = false;
			number_ship = Num_Ship::NONE;
		}
	};

	InfoCell OurMap[10][10];

	sf::Texture Ceil_Texture;
	sf::Sprite Ceil_Sprite;

	sf::Vector2f Location;

	static const int Ceil_Size=54;


public:
	Map() {};
	Map(sf::Vector2f mLocation);

	bool SetShip(sf::Vector2i A, Num_Ship num, int type, WayShip mway= WayShip::DOWN); 
	bool RotateShip(sf::Vector2i A, int type);
	void ClearShip(sf::Vector2i A, int type);

	bool Move(sf:: Vector2i A, Num_Ship &D);
	void SetFocus(sf::Vector2i A);
	void KillShip(sf::Vector2i A, int type);


	bool SetRange(sf::Vector2i A, int type, int& i, int& j, int& k, int& g);
	bool CheckCeil(sf::Vector2i A, int type, WayShip mway);
	void Clear(sf::Vector2i A, int type, WayShip mway);
	void ClearMap();

	void Draw(sf::RenderWindow& mWindow);

	bool GetMapCoords(sf::Vector2f A, sf::Vector2i &B);
	bool GetShipWayDown(sf::Vector2f A);
	int GetShipType(Num_Ship n);
	sf::Vector2f  GetCoordsForShip(sf::Vector2i A);
	bool HaveMap(sf::Vector2f a);

	sf::Vector2f GetLocationMap() { return Location; };

	///%%%%%test
	/*void TestDraw() 
	{
		for (int i = 0; i < 10; i++) 
		{
			for (int k = 0; k < 10; k++) 
			{
				if (OurMap[i][k].number_ship != Num_Ship::NONE) std::cout << " 1 ";
				else  cout << " 0 ";
			}
			cout << std::endl;
		}
		cout << std::endl;
		cout << std::endl;
	}*/
};

