#include "GameState.h"
Menu::Menu(Player* player):GameState(), button_start(L"ИГРАТЬ", ButtonSize::Medium, sf::Vector2f(550,700)), button_name(L"сменить имя", ButtonSize::Small, sf::Vector2f(600, 900)),
button_readyName(L"Завершить", ButtonSize::Small, sf::Vector2f(600, 690))
{
	if (!BackGround_texture.loadFromFile("resources/images/menu.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/menu.png");
	BackGround_sprite.setTexture(BackGround_texture);

	if (!textInput_texture.loadFromFile("resources/images/text.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/text.png");
	textInput_sprite.setTexture(textInput_texture);
	textInput_sprite.setPosition(460,490);

	Input_name.setFillColor(sf::Color(0, 0, 0));
	Input_name.setFont(m_font);
	Input_name.setCharacterSize(100);

	text.setFont(m_font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setString(L"Введите свое имя");
	text.setPosition(335, 300);

	people = player;

	start = false;
}

void Menu::Input(sf::RenderWindow& mWindow, sf::Event& mevent)
{
	if (ChangeName) 
	{
		mWindow.setKeyRepeatEnabled(false);
		if (mevent.type == sf::Event::TextEntered && !wasKey)
		{
			wasKey = true;
			//cout << mevent.key.code << endl;

			if (mevent.text.unicode < 128) 
			{
				if (mevent.text.unicode == 8) {
					if (name.size() != 0)
						name.erase(name.size() - 1);
				}
				else 
				if (name.size()<10)
				{
					name += mevent.text.unicode;
					
				}
				//cout << name;
			}
		}

	}

	InputKeyboard(mevent);
	if (sf::Event::MouseButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_move != MouseInput::click_l)
		{
			mouse_move = MouseInput::click_l;
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

State Menu::Update() 
{
	if (ChangeName) 
	{
		if (name == "") button_readyName.ButtonInactive();
		else button_readyName.ButtonActive();
		if (button_readyName.OnButton(GotCoordsPeople)) 
		{
			button_readyName.ButtonSetFocus();
			if (mouse_move == MouseInput::click_l && !wasClick )
			{
				ChangeName = false;
				wasClick = true;
				//people->SetName(name);
				std::ofstream out("resources/memory/name.txt");
				if (out.is_open())
				{
					out << name << std::endl;
				}
				out.close();
				if (start)
				{
					start = false;
					return State::SetShipPosition;
				}
			}
		}

		std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;
		Input_name.setString(cv.from_bytes(name));
		Input_name.setOrigin(Input_name.getGlobalBounds().width / 2, Input_name.getGlobalBounds().height / 2);
		Input_name.setPosition(720, 540);

		if (mouse_move == MouseInput::none && wasClick) 
			wasClick = false;
		if (keyboard == KeyboardInput::none) 
			wasKey = false;

		return State::none;
	}
	if (button_start.OnButton(GotCoordsPeople)) 
	{
		button_start.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick) 
		{
			wasClick = true;
			ifstream file;
			file.open("resources/memory/name.txt");
			if (file.is_open())
			{
				getline(file, name);
				if (name == "") 
				{
					ChangeName = true;
					start = true;
				}
				else 
				{

					//std::cout << name;
					people->SetName(name);
				}
			}
			else 
			{
				ChangeName = true;
				start = true;
				std::ofstream outfile("resources/memory/name.txt");
				outfile.close();
			}
			file.close(); 
			if (ChangeName) return State::none;
			return State::SetShipPosition;
		}
	}
	if (button_name.OnButton(GotCoordsPeople))
	{
		button_name.ButtonSetFocus();
		if (mouse_move == MouseInput::click_l && !wasClick)
		{
			ifstream file;
			file.open("resources/memory/name.txt");
			if (file.is_open())
			{
				getline(file, name);
			}
			else
			{
				std::ofstream outfile("resources/memory/name.txt");
				outfile.close();
			}
			file.close(); 

			ChangeName = true;
			wasClick = true;
		}
	}
	if (mouse_move == MouseInput::click_l && !wasClick) wasClick = true;
	if (mouse_move == MouseInput::none && wasClick) wasClick = false;
	if (keyboard == KeyboardInput::none) wasKey = false;
    return State::none;
}
void  Menu::Draw(sf::RenderWindow& mWindow)
{
	mWindow.draw(BackGround_sprite);
	if (ChangeName) 
	{
		mWindow.draw(window_sprite);
		mWindow.draw(textInput_sprite);
		mWindow.draw(text);
		mWindow.draw(Input_name);
		button_readyName.Draw(mWindow);
	}
	else 
	{
		button_start.Draw(mWindow);
		button_name.Draw(mWindow);
	}

}