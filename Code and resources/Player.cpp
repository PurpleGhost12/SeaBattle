#include "Players.h"
///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Player::Player(std::string name, sf::Vector2f LocateMap, bool RightSide):Players(name, LocateMap, RightSide)
{
	for (int k = 0; k < 10; k++) ReturnShip((Num_Ship)k);
	SetShip = 0;
}
void Player::NewGame()
{
	m_map.ClearMap();
	m_fleet.NewGame();

	for (int k = 0; k < 10; k++) ReturnShip((Num_Ship)k);
	SetShip = 0;
}
void Player::ReturnShip(Num_Ship ship) 
{
	int k = (int)ship;
	int start, step;
	int dX = 0;
	sf::Vector2f a = m_map.GetLocationMap();
	if (RSide)
	{
		start = a.x + 54 * 10 - 30;
		step = -54 - 4;
	}
	else
	{
		start =a.x + 54 * 10 - 15;
		step = -54 - 4;
	}
	for (int i = 0; i < k; i++) 
	{
		dX += step;
	}
	m_fleet.SetShip(sf::Vector2f(start + dX, 800+54*(4-m_map.GetShipType(ship))), (int)ship, false);
}
bool Player::UpdateSetShip(sf::Vector2f a, MouseInput& mstate, bool random, bool clear)
{
	if (random)
	{
		m_map.ClearMap();
		SetRandomShip();
		SetShip = 10;
		return SetShip == 10;
	}
	if (clear)
	{
		m_map.ClearMap();
		for (int k = 0; k < 10; k++) ReturnShip((Num_Ship)k);
		SetShip = 0;
		return SetShip == 10;
	}
	if (now_move == Num_Ship::NONE && mstate != MouseInput::none && (mstate != MouseInput::click_r || (mstate == MouseInput::click_r && !click)))
	{
		if (m_fleet.IsShip(0, a)) 
			now_move = Num_Ship::SHIP_4_1;
		if (m_fleet.IsShip(1, a)) 
			now_move = Num_Ship::SHIP_3_1;
		if (m_fleet.IsShip(2, a)) 
			now_move = Num_Ship::SHIP_3_2;
		if (m_fleet.IsShip(3, a)) 
			now_move = Num_Ship::SHIP_2_1;
		if (m_fleet.IsShip(4, a)) 
			now_move = Num_Ship::SHIP_2_2;
		if (m_fleet.IsShip(5, a)) 
			now_move = Num_Ship::SHIP_2_3;
		if (m_fleet.IsShip(6, a)) 
			now_move = Num_Ship::SHIP_1_1;
		if (m_fleet.IsShip(7, a)) 
			now_move = Num_Ship::SHIP_1_2;
		if (m_fleet.IsShip(8, a)) 
			now_move = Num_Ship::SHIP_1_3;
		if (m_fleet.IsShip(9, a)) 
			now_move = Num_Ship::SHIP_1_4;

		if (now_move != Num_Ship::NONE && mstate !=  MouseInput::click_r && m_map.HaveMap(m_fleet.GetCoordsShip((int)now_move))) 
		{
			sf::Vector2i a;
			m_map.GetMapCoords(m_fleet.GetCoordsShip((int)now_move), a);
			m_map.ClearShip(a, m_map.GetShipType(now_move));
			SetShip--;
		}
		sf::Vector2f p = m_fleet.GetCoordsShip((int)now_move);
		//std::cout << "sprite " << p.x << " " << p.y << std::endl;
		dX = a.x - p.x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
		dY = a.y - p.y;
	}
	else  
		if (now_move != Num_Ship::NONE) 
		{
			if (mstate == MouseInput::none) //setship?
			{
				sf::Vector2i b;
				if (m_map.GetMapCoords(m_fleet.GetCoordsShip((int)now_move), b))
				{
					WayShip ship_rotate;
					if (m_fleet.GetShipRotate((int)now_move)) ship_rotate = WayShip::RIGHT;
					else ship_rotate = WayShip::DOWN;
					if (m_map.SetShip(b, now_move, m_map.GetShipType(now_move), ship_rotate))
					{
						m_fleet.SetShipCoordsSprite(m_map.GetCoordsForShip(b), (int)now_move);
						SetShip++;
					}
					else ReturnShip(now_move);
					now_move = Num_Ship::NONE;
				}
				else
				{
					ReturnShip(now_move);
					now_move = Num_Ship::NONE;
				}
			}
			else
				if (mstate == MouseInput::click_l)
				{
					//std::cout << dX << " " << dY << std::endl;
					//std::cout << a.x << " " << a.y<< std::endl;
					m_fleet.SetShipCoordsSprite(sf::Vector2f(a.x - dX, a.y - dY), (int)now_move);
					//std::cout << "move!\n";					
				}
				else 
					if (mstate == MouseInput::click_r && !click) 
					{
						sf::Vector2i a;
						if (m_map.GetMapCoords(m_fleet.GetCoordsShip((int)now_move), a))
						{
							if (m_map.RotateShip(a, m_map.GetShipType(now_move)))
							{
								m_fleet.RotateShip((int)now_move);
							}
						}
						//mstate = MouseInput::none;
						now_move = Num_Ship::NONE;
						click = true;
					}
		}
	if (mstate == MouseInput::none && click) click = false;
	//mstate = MouseInput::none;
	//now_move = Num_Ship::NONE;
	//SetRandomShip();
	//std::cout << SetShip << std::endl;
	return SetShip == 10;
}

bool Player::UpdateGameMap(sf::Vector2i a, bool& ship, bool &kill) 
{
	sf::Vector2i m_coords;
	Num_Ship n_ship;
	if (!m_map.Move(a, n_ship))
		std::cout<<"No";
	if (n_ship != Num_Ship::NONE)
	{
		m_fleet.DamageShip((int)n_ship);
		if (!m_fleet.AliveShip((int)n_ship))
		{
			m_map.GetMapCoords(m_fleet.GetCoordsShip((int)n_ship), m_coords);
			m_map.KillShip(m_coords, m_fleet.GetTypeShip((int)n_ship));
			kill = true;
		}
		else kill = false;
		ship = true;
		return false;
	}
	ship = false;
	kill = false;
	return true;
}