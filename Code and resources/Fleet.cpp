#include "Fleet.h"
#include <iostream>
Fleet::Fleet()
{
	if (!Ships_Image.loadFromFile("resources/images/ships2.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/ships2.png");
	Ships_Image.createMaskFromColor(sf::Color(0, 0, 0));
	Ships_Texture.loadFromImage(Ships_Image);
	mFleet[0]= ship(4, Ships_Texture);
	for (int i = 1; i < 3; i++) mFleet[i] = ship(3, Ships_Texture);
	for (int i = 3; i < 6; i++) mFleet[i] = ship(2, Ships_Texture);
	for (int i = 6; i < 10; i++) mFleet[i] = ship(1, Ships_Texture); // 0 12 345 6789
	ShipAlive = 10;
}
void Fleet::NewGame()
{
	mFleet[0].live = 4;
	for (int i = 1; i < 3; i++) mFleet[i].live = 3;
	for (int i = 3; i < 6; i++) mFleet[i].live = 2;
	for (int i = 6; i < 10; i++) mFleet[i].live = 1;
	ShipAlive = 10;
}

void Fleet::SetShip(sf::Vector2f x, int num, bool rotate)
{
	mFleet[num].SpriteCoordinate = x;
	mFleet[num].ship_Sprite.setPosition(x);
	if (rotate) 
	{
		mFleet[num].ship_Sprite.setRotation(270);
	}
	else 
	{
		mFleet[num].ship_Sprite.setRotation(0);
	}
}
void Fleet::SetShipCoordsSprite(sf::Vector2f a, int num) 
{
	mFleet[num].SpriteCoordinate = a;
	mFleet[num].ship_Sprite.setPosition(a);
	//std::cout << a.x <<" "<< a.y << std::endl;
}
void Fleet::RotateShip(int num) 
{
	if (mFleet[num].ship_Sprite.getRotation() == 0) 
	{
		mFleet[num].ship_Sprite.setRotation(270);
	}
	else 
	{
		mFleet[num].ship_Sprite.setRotation(0);
	}
}

void Fleet::Draw(sf::RenderWindow& mWindow)
{
	for (int i = 0; i < 10; i++) 
	{
		if (mFleet[i].live==0) mWindow.draw(mFleet[i].ship_Sprite);
	}
}
void Fleet:: DrawAll(sf::RenderWindow& mWindow) 
{
	for (int i = 0; i < 10; i++)
	{
		mWindow.draw(mFleet[i].ship_Sprite);
	}
}

void Fleet::DamageShip(int num) 
{
	if (num < 0 || num>10)
		std::cout << 1;
	if (num<10) mFleet[num].live--;
	if (mFleet[num].live == 0) ShipAlive--;
}

bool Fleet::HaveAliveShip() 
{
	return !(ShipAlive == 0);
}

bool Fleet::AliveShip(int num) 
{
	return mFleet[num].live;
}

int Fleet::GetTypeShip(int n) 
{
	return mFleet[n].type;
}

sf::Vector2f Fleet::GetCoordsShip(int num) 
{
	return mFleet[num].SpriteCoordinate;
}


bool Fleet::IsShip(int num_ship, sf::Vector2f a) 
{
	return mFleet[num_ship].ship_Sprite.getGlobalBounds().contains(a.x, a.y);
}
bool  Fleet::GetShipRotate(int num)
{
	return (mFleet[num].ship_Sprite.getRotation() > 0);
}