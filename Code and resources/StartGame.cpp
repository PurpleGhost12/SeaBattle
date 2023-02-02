#include"GameState.h"
StartGame::StartGame(Player* mplayer, Computer* mcomputer):GameState(), button_back(L"ÌÅÍÞ",ButtonSize::Medium, sf::Vector2f(20,750)),
button_start(L"ÑÒÀÐÒ", ButtonSize::Medium, sf::Vector2f(400, 900), false),
button_random(L"ÑËÓ×ÀÉÍÎ", ButtonSize::Medium, sf::Vector2f(400, 750)),
button_clear(L"Î×ÈÑÒÈÒÜ", ButtonSize::Medium, sf::Vector2f(20, 900))
{
	people = mplayer;
	computer = mcomputer;
	if (!BackGround_texture.loadFromFile("resources/images/SetShip.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to loadresources/images/SetShip.png");
	BackGround_sprite.setTexture(BackGround_texture);
	mouse_move = MouseInput::none;
	now_move = Num_Ship::NONE;
}
void StartGame::Input(sf::RenderWindow& mWindow, sf::Event& mevent)
{
	InputKeyboard(mevent);
	mouse_move = MouseInput::none;
	if (sf::Event::MouseButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_move != MouseInput::click_l)
		{
			mouse_move = MouseInput::click_l;
		}
		else
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mouse_move != MouseInput::click_l && mouse_move != MouseInput::click_r)
			{
				mouse_move = MouseInput::click_r;
			}
	}
	if (mevent.type == sf::Event::MouseButtonReleased)
	{
		if (mevent.key.code == sf::Mouse::Left && mouse_move == MouseInput::click_l) 
		{
			mouse_move = MouseInput::none;
		}
		if (mevent.key.code == sf::Mouse::Right && mouse_move == MouseInput::click_r)
		{
			mouse_move = MouseInput::none;
		}
	}

	sf::Vector2i pos = sf::Mouse::getPosition(mWindow);
	GotCoordsPeople = mWindow.mapPixelToCoords(pos);
}
State StartGame::Update() 
{
	if (first) 
	{
		if (mouse_move != MouseInput::none)
			wasClick = true;
		first = false;
	}
	if (button_back.OnButton(GotCoordsPeople)) 
	{
		button_back.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick) 
		{
			wasClick = true;
			people->UpdateSetShip(GotCoordsPeople, mouse_move, false, true);
			return State::Menu;
		}
	}
	if (button_start.OnButton(GotCoordsPeople)&& ReadyPeople)
	{
		button_start.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick)
		{
			first = true;
			wasClick = true;
			computer->UpdateSetShip();
			return State::Game;
		}
	}
	if (button_random.OnButton(GotCoordsPeople))
	{
		button_random.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick)
		{
			wasClick = true;
			people->UpdateSetShip(GotCoordsPeople, mouse_move, true);
			ReadyPeople = true;
			return State::none;
		}
	}
	if (button_clear.OnButton(GotCoordsPeople))
	{
		button_clear.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick)
		{
			wasClick = true;
			people->UpdateSetShip(GotCoordsPeople, mouse_move, false, true);
			ReadyPeople = false;
			return State::none;
		}
	}
	if (people->UpdateSetShip(GotCoordsPeople, mouse_move))
		ReadyPeople = true;
	else 
		ReadyPeople = false;

	if (ReadyPeople)
	{
		//std::cout << "yes\n";
		button_start.ButtonActive();
	}
	else 
	{
		button_start.ButtonInactive();
	}
	if (mouse_move == MouseInput::click_l && !wasClick) 
		wasClick = true;
	if (mouse_move == MouseInput::none && wasClick) 
		wasClick = false;
	return State::none;
}
void StartGame::Draw(sf::RenderWindow& mWindow) 
{
	mWindow.draw(BackGround_sprite);
	people->DrawOur(mWindow);
	button_start.Draw(mWindow);
	button_back.Draw(mWindow);
	button_clear.Draw(mWindow);
	button_random.Draw(mWindow);
}