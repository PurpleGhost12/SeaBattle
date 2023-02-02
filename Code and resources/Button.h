#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
 enum class ButtonSize
 {
	Small = 0,
	Medium,
	Large
};

class Button
{
private:
	bool button_active = true;;
	bool InFocus=false;

	ButtonSize m_size;

	sf::Texture Button_texture;
	sf::Sprite Button_sprite;

	sf::Text button_text;

	sf::Font button_font;

public:

	Button(sf::String text, ButtonSize  size, sf::Vector2f position=sf::Vector2f(0,0), bool active=true);

	bool OnButton(sf::Vector2f A);
	void ButtonSetPosition(sf::Vector2f position);
	void ButtonSetFocus();
	void Draw(sf::RenderWindow& mWindow);

	void ButtonActive(); 
	void ButtonInactive(); 
};

