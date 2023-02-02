#include "GameState.h"
PlayGame::PlayGame(Player* mplayer, Computer* mcomputer):GameState(),people_name("", m_font, 60), computer_name(mcomputer->GetName(), m_font, 60),
button_people(L"Игрок", ButtonSize::Medium,sf::Vector2f(370,500)), button_computer(L"Компьютер", ButtonSize::Medium, sf::Vector2f(780, 500)), button_random(L"Случайно", ButtonSize::Medium, sf::Vector2f(580, 640)),
button_yes(L"Да", ButtonSize::Medium, sf::Vector2f(370, 550)), button_no(L"Нет", ButtonSize::Medium, sf::Vector2f(780, 550))
{
	people = mplayer;
	computer = mcomputer;

	people_name.setFillColor(sf::Color(0,0,0));
	computer_name.setFillColor(sf::Color(0, 0, 0));

	now_move = Who::player2;

	arrow_texture.loadFromFile("resources/images/arrow.png");
	arrow_sprite.setTexture(arrow_texture);

	arrow_sprite.setOrigin(42.5, 38);
	arrow_sprite.setPosition(720,383);
	arrow_sprite.setRotation(180);
	arrow_sprite.setColor(sf::Color(0,255,0));

	if (!BackGround_texture.loadFromFile("resources/images/SeaBattle222.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/SeaBattle222.png");
	BackGround_sprite.setTexture(BackGround_texture);

	if (!GameOver_texture.loadFromFile("resources/images/GameOver.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/GameOver.png");
	GameOver_Sprite.setTexture(GameOver_texture);
	GameOver_Sprite.setPosition(sf::Vector2f(185, 280));

	if (!Winner_texture.loadFromFile("resources/images/Win3.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/Win3.png");
	Winner_sprite.setTexture(Winner_texture);
	Winner_sprite.setPosition(240,300);

	if (!Loser_texture.loadFromFile("resources/images/lose.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/lose.png");
	Loser_Sprite.setTexture(Loser_texture);
	Loser_Sprite.setPosition(240, 300);

	text.setFont(m_font);
	text.setCharacterSize(95);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setString(L"Кто ходит первый?");
	text.setPosition(335, 300);

	text2.setFont(m_font);
	text2.setCharacterSize(95);
	text2.setFillColor(sf::Color(255, 255, 255));
	text2.setString(L"Вернуться в меню?");
	text2.setPosition(335, 350);

	game = false;
	wasClick = false;
	now_move = Who::player2;
}

void PlayGame::Input(sf::RenderWindow& mWindow, sf::Event& mevent)
{
	if (now_move == Who::player1 && game) //player1-computer
	{
		GotCoordsComp = computer->Move();
	}
	else 
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mouse_move = MouseInput::click_l;
		}
		else
		{
			mouse_move = MouseInput::focus;
		}
		sf::Vector2i pos = sf::Mouse::getPosition(mWindow);
		GotCoordsPeople = mWindow.mapPixelToCoords(pos);
	}
	InputKeyboard(mevent);
}
void PlayGame::ChangeMove() 
{
	if (now_move == Who::player2)//player1-computer
	{
		now_move = Who::player1;
		arrow_sprite.setRotation(0);
		arrow_sprite.setColor(sf::Color(255, 0, 0));
	}
	else
	{
		now_move = Who::player2;
		arrow_sprite.setRotation(180);
		arrow_sprite.setColor(sf::Color(255, 183, 0));
	}
}
State PlayGame::Update()
{
	if (first)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;

		people_name.setString(cv.from_bytes(people->GetName()));

		people_name.setOrigin(people_name.getGlobalBounds().width / 2, people_name.getGlobalBounds().height / 2);
		computer_name.setOrigin(computer_name.getGlobalBounds().width / 2, computer_name.getGlobalBounds().height / 2);

		people_name.setPosition(974, 798);
		computer_name.setPosition(470, 798);

		if (mouse_move != MouseInput::none)
			wasClick_mouse = true;
		if (keyboard != KeyboardInput::none)
			wasClick = true;
		first = false;
	}
	if (ChooseOne) 
	{
		if (button_computer.OnButton(GotCoordsPeople)) 
		{
			button_computer.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick_mouse)
			{
				ChooseOne = false;
				wasClick_mouse = true;
				game = true;
				now_move = Who::player1;
				arrow_sprite.setRotation(0);
				arrow_sprite.setColor(sf::Color(255, 0, 0));
			}
		}
		if (button_people.OnButton(GotCoordsPeople))
		{
			button_people.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick_mouse)
			{
				ChooseOne = false;
				wasClick_mouse = true;
				game = true;
				now_move = Who::player2;
				arrow_sprite.setRotation(180);
				arrow_sprite.setColor(sf::Color(255, 183, 0));
			}
		}
		if (button_random.OnButton(GotCoordsPeople))
		{
			button_random.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick_mouse)
			{
				ChooseOne = false;
				wasClick_mouse = true;
				game = true;
				now_move = Who(people->GetRandomNumber(0,1));
				if (now_move == Who::player1)//player1-computer
				{
					arrow_sprite.setRotation(0);
					arrow_sprite.setColor(sf::Color(255, 0, 0));
				}
				if (now_move == Who::player2)
				{
					arrow_sprite.setRotation(180);
					arrow_sprite.setColor(sf::Color(0, 255, 0));
				}
			}
		}
		if (mouse_move == MouseInput::click_l && !wasClick) 
			wasClick = true;
		if (keyboard == KeyboardInput::none && wasClick) 
			wasClick = false;
		if (mouse_move == MouseInput::focus && wasClick_mouse) 
			wasClick_mouse = false;
		return State::none;
	}
	if (BackMenu)
	{
		if (button_yes.OnButton(GotCoordsPeople)) 
		{
			button_yes.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick_mouse) 
			{
				wasClick_mouse = true;
				first = true;
				ChooseOne = true;
				//game = true;
				ShowEnd = false;
				show_gameover = false;
				people->NewGame();
				computer->NewGame();
				wasClick = false;
				now_move = Who::player2; // while there is no choice who goes
				BackMenu = false;
				return State::Menu;
			}
		}
		if (button_no.OnButton(GotCoordsPeople))
		{
			button_no.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick_mouse) 
			{
				wasClick_mouse = true;
				BackMenu = false;
			}
		}
		if (mouse_move == MouseInput::click_l && !wasClick)
			wasClick = true;
		if (keyboard == KeyboardInput::none && wasClick)
			wasClick = false;
		if (mouse_move == MouseInput::focus && wasClick_mouse)
			wasClick_mouse = false;
		return State::none;
	}

	if (keyboard == KeyboardInput::escape) 
	{
		BackMenu = true;
	}

	if (game) 
	{
		if (now_move == Who::player1) //player1-computer
		{
			bool kill, ship;
			if (people->UpdateGameMap(GotCoordsComp, ship, kill)) 
				ChangeMove();
			computer->UpdateMove(ship, kill);;
		}
		else
		if (!wasClick_mouse)
		{
			if (computer->UpdateGameMap(GotCoordsPeople, mouse_move))
				ChangeMove();
		}

		//mouse_move = MouseInput::none;

		if (people->EndShips()) 
		{
			game = false;
			win = false;
			show_gameover = true;
		}
		if (computer->EndShips()) 
		{
			show_gameover = true;
			game = false;
			win = true;
		}
	}
	else 
	{
		if (show_gameover && keyboard != KeyboardInput::none && !wasClick) 
		{
			show_gameover = false;	
			wasClick = true;
		}
		if (!ShowEnd && keyboard != KeyboardInput::none && !wasClick)
		{
			ShowEnd = true;
			wasClick = true;
		}
		if (ShowEnd && keyboard != KeyboardInput::none && !wasClick)
		{
			first = true;
			ChooseOne = true;
			//game = true;
			ShowEnd = false;
			show_gameover = false;
			people->NewGame();
			computer->NewGame();
			wasClick = false;
			now_move = Who::player2; // while there is no choice who goes

			return State::Menu;
		}
	}
	if (mouse_move == MouseInput::click_l && !wasClick) wasClick = true;
	if (keyboard == KeyboardInput::none && wasClick) wasClick = false;
	if (mouse_move == MouseInput::focus && wasClick_mouse) wasClick_mouse = false;
	return State::none;
}

void PlayGame::Draw(sf::RenderWindow& mWindow)
{
	mWindow.draw(BackGround_sprite);
	mWindow.draw(arrow_sprite);
	mWindow.draw(people_name);
	mWindow.draw(computer_name);
	if (ChooseOne) 
	{
		mWindow.draw(window_sprite);
		mWindow.draw(text);
		button_computer.Draw(mWindow);
		button_people.Draw(mWindow);
		button_random.Draw(mWindow);
	}
	else 
	{
		if (BackMenu) 
		{
			mWindow.draw(window_sprite);
			mWindow.draw(text2);
			button_yes.Draw(mWindow);
			button_no.Draw(mWindow);
		}
		else 
		{
			if (game)
			{
				people->DrawOur(mWindow);
				people->DrawShips(mWindow);
				computer->DrawEnemy(mWindow);
				computer->DrawShips(mWindow);
			}
			else
			{
				people->DrawOur(mWindow);
				people->DrawShips(mWindow);
				computer->DrawOur(mWindow);
				computer->DrawShips(mWindow);

				if (show_gameover)
				{
					mWindow.draw(GameOver_Sprite);
				}
				if (ShowEnd)
				{
					if (win)
					{
						mWindow.draw(Winner_sprite);
					}
					else
					{
						mWindow.draw(Loser_Sprite);
					}
				}
			}
		}
	}
}