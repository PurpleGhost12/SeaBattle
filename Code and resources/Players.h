#pragma once
#include <SFML/Graphics.hpp>
#include<Windows.h>
#include <string>
#include<map>
#include "Fleet.h"
#include "Map.h"


enum class MouseInput 
{
	click_r=0,
	click_l,
	focus,
	released,
	none
};

class Players 
{
protected:

	std::string m_name;
	Fleet m_fleet;
	Map m_map;

	int SetShip;
	float dX, dY;

	bool RSide;

	std::vector<sf::Vector2i>::iterator it;

	sf::Image ship_image;
	sf::Texture ship_texture;
	sf::Sprite ship_sprite;

	void DrawShip(sf::RenderWindow& m_window, int& start, int& step, int& dx, int k, int y);
	void SetCoords(std::vector<sf::Vector2i>& mlist);
	bool SetRandomShip();
	void SetRand(int type, int num, std::vector<sf::Vector2i>& mlist);

public:

	Players(std::string name, sf::Vector2f LocateMap, bool RightSide);


	bool EndShips() { return !m_fleet.HaveAliveShip();}

	virtual bool UpdateSetShip() { return true; };// 
	virtual bool UpdateGameMap() { return true; };//true-the move is made

	//virtual bool Move() = 0;


	int GetRandomNumber(int min, int max);
	std::string GetName() { return m_name; }

	void DrawOur(sf::RenderWindow& m_window);
	void DrawEnemy(sf::RenderWindow& m_window);
	void DrawShips(sf::RenderWindow& m_window);
};


class Player:public Players 
{
private:
	Num_Ship now_move=Num_Ship::NONE;
	void ReturnShip(Num_Ship ship);

	bool click = false;

public:
	Player(std::string name, sf::Vector2f LocateMap, bool RightSide);
	void NewGame();

	void SetName(std::string name) { m_name = name; };

	bool UpdateSetShip(sf::Vector2f a, MouseInput&   mstate, bool random = false, bool clear=false);
	bool UpdateGameMap(sf::Vector2i a, bool& ship, bool& kill);

};


class Computer: public Players 
{
private:
	std::vector<sf::Vector2i> m_move;
	bool ship = false;
	int num_shot = 0;
	sf::Vector2i First_coords;
	sf::Vector2i Last_coords;

	enum class waySearch 
	{
		Up=0,
		Down=1,
		Right,
		Left,
		none
	};

	waySearch  now_way;

	sf::Vector2i GiveWayVector(waySearch  m_way);
	void SetReverseWay(waySearch& m_way);
	bool DeleteCoords(sf::Vector2i del);

public:
	Computer(sf::Vector2f LocateMap, bool RightSide);
	void NewGame();

	bool UpdateSetShip();
	bool UpdateGameMap(sf::Vector2f a, MouseInput   mstate);

	void UpdateMove(bool ship, bool kill);

	sf::Vector2i Move();

	////test
	/*void TestDraw() 
	{
		m_map.TestDraw();
	}*/
};

