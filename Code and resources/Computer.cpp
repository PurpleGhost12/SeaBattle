#include "Players.h"

Computer::Computer(sf::Vector2f locateMap, bool RightSide) :Players("computer", locateMap, RightSide)
{
	//int n = 0;
	SetCoords(m_move);
	now_way = waySearch::none;
}
void Computer::NewGame()
{
	m_map.ClearMap();
	m_fleet.NewGame();
	SetCoords(m_move);
}
/*int GetRandomNumber(int min, int max)
{
	// ”становить генератор случайных чисел
	srand(time(NULL));

	// ѕолучить случайное число - формула
	int num = min + rand() % (max - min + 1);

	return num;
}*/

bool Computer::UpdateSetShip()
{
	SetRandomShip();
	return true;
}

bool Computer::UpdateGameMap(sf::Vector2f a, MouseInput  mstate)//true-the move is made
{
	sf::Vector2i m_coords;
	if (m_map.GetMapCoords(a, m_coords))
	{
		if (mstate == MouseInput::click_l)
		{
			Num_Ship n_ship;
			if (m_map.Move(m_coords, n_ship))
			{
				if (n_ship != Num_Ship::NONE) 
				{
					m_fleet.DamageShip((int)n_ship);
					if (n_ship != Num_Ship::NONE && !m_fleet.AliveShip((int)n_ship))
					{
						m_map.GetMapCoords(m_fleet.GetCoordsShip((int)n_ship), m_coords);
						m_map.KillShip(m_coords, m_fleet.GetTypeShip((int)n_ship));
					}
					return false; // when the hit continues the turn
				}
				return true;
			}
		}
		else
		{
			m_map.SetFocus(m_coords);
		}
	}
	return false;
}
sf::Vector2i Computer::GiveWayVector(waySearch  m_way)
{
	switch (m_way)
	{
	case Computer::waySearch::Up:
		return sf::Vector2i(0, -1);
		break;
	case Computer::waySearch::Down:
		return sf::Vector2i(0, 1);
		break;
	case Computer::waySearch::Right:
		return sf::Vector2i(1, 0);
		break;
	case Computer::waySearch::Left:
		return sf::Vector2i(-1, 0);
		break;
	default:
		return sf::Vector2i(0, 0);
		break;
	}
}
void Computer::SetReverseWay(waySearch& m_way)
{
	switch (m_way)
	{
	case Computer::waySearch::Up:
		m_way = waySearch::Down;
		break;
	case Computer::waySearch::Down:
		m_way = waySearch::Up;
		break;
	case Computer::waySearch::Right:
		m_way = waySearch::Left;
		break;
	case Computer::waySearch::Left:
		m_way = waySearch::Right;
		break;
	default:
		m_way = waySearch::none;
		break;
	}
}

bool Computer::DeleteCoords(sf::Vector2i del) 
{
	it = find(m_move.begin(), m_move.end(), del);
	if (it != m_move.end())
		m_move.erase(it);
	else return false;
	return true;
}

void Computer::UpdateMove(bool ship, bool kill) 
{
	if (ship) 
	{
		num_shot++;
		if (kill) 
		{
			ship = false;		
			int k, g, i, j;
			if (now_way == waySearch::Up || now_way == waySearch::none) m_map.SetRange(Last_coords, num_shot, i, j, k, g);
			if (now_way== waySearch::Down) m_map.SetRange(Last_coords - sf::Vector2i(0, num_shot - 1), num_shot, i, j, k, g);
			if (now_way == waySearch::Left)
			{ 
				m_map.SetRange(sf::Vector2i(Last_coords.y, Last_coords.x), num_shot, k, g, i, j);
			}
			if (now_way == waySearch::Right)
			{
				m_map.SetRange(sf::Vector2i(Last_coords.y, Last_coords.x-num_shot +1), num_shot, k, g, i, j);
			}
			for (int i1 = i; i1 <= j; i1++)
			{
				for (int k1 = k; k1 <= g; k1++)
				{
					DeleteCoords(sf::Vector2i(i1, k1));
				}
			}
			now_way = waySearch::none;
			num_shot = 0;
		}
		else 
		{
			if (num_shot == 1) 
			{
				First_coords = Last_coords;
				do 
				{
					now_way = (waySearch)GetRandomNumber(0, 3);
					it = find(m_move.begin(), m_move.end(), Last_coords+GiveWayVector(now_way));
				} while (it == m_move.end());
			}
			else 
			{
				if (find(m_move.begin(), m_move.end(), Last_coords + GiveWayVector(now_way)) == m_move.end()) 
				{
					Last_coords = First_coords;
					SetReverseWay(now_way);
				}
			}
		}
	}
	else 
	{
		if (num_shot > 1) 
		{
			Last_coords = First_coords;
			SetReverseWay(now_way);
		}
		if (num_shot == 1) 
		{
			Last_coords = First_coords;
			do
			{
				now_way = (waySearch)GetRandomNumber(0, 3);
				it = find(m_move.begin(), m_move.end(), Last_coords + GiveWayVector(now_way));
			} while (it == m_move.end());
		}
	}
}
sf::Vector2i Computer::Move() 
{
	if (now_way == waySearch::none)
	{
		Last_coords=m_move[GetRandomNumber(0, m_move.size() - 1)];
	}
	else 
	{
		Last_coords = Last_coords + GiveWayVector(now_way);
	}		
	if (!DeleteCoords(Last_coords))
		std::cout<<"No\n";
	//std::cout << m_move.size()<<std::endl;
	Sleep(500);
	return Last_coords;
}