#pragma once
#include <SFML/Graphics.hpp>
class Fleet
{
private:
	

	sf::Image Ships_Image;
	sf::Texture Ships_Texture;
	int ShipAlive;

	struct ship
	{
		int type=0; //Ship Type
		int live=0; //Life

		bool wayDown=false;

		sf::Vector2f SpriteCoordinate;
		sf::Sprite ship_Sprite;
		ship() 
		{

		}
		ship(int n_type, sf::Texture& ship):SpriteCoordinate(0, 0)
		{
			type = n_type;
			live = type;
			wayDown = true;
			ship_Sprite.setTexture(ship);
			if (type == 4) ship_Sprite.setTextureRect(sf::IntRect(0, 0, 54, 54 * 4));
			if (type == 3) ship_Sprite.setTextureRect(sf::IntRect(54, 0, 54, 54 * 3));
			if (type == 2) ship_Sprite.setTextureRect(sf::IntRect(54 * 2, 0, 54, 54 * 2));
			if (type == 1) ship_Sprite.setTextureRect(sf::IntRect(54 * 3, 0, 54, 54));

			ship_Sprite.setOrigin(27, 27);
			ship_Sprite.setColor(sf::Color(0, 0, 0));
		}
	};

    ship mFleet[10];
public:

	Fleet();
	void NewGame();

	void Draw(sf::RenderWindow& mWindow);
	void DrawAll(sf::RenderWindow& mWindow);

	void SetShip(sf:: Vector2f x, int num, bool rotate);
	void RotateShip(int num);

	void DamageShip(int num);

	bool HaveAliveShip();

	bool AliveShip(int num);

	int GetTypeShip(int n);
	bool GetShipRotate(int num);
	bool IsShip(int num_ship, sf::Vector2f a);

	void SetShipCoordsSprite(sf::Vector2f a, int num);

	sf::Vector2f GetCoordsShip(int num);
	sf::Texture GetShipTexture() { return Ships_Texture; };
	sf::Image GetShipImage() { return Ships_Image; };
};

