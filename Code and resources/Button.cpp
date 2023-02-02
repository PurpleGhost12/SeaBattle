#include "Button.h"
Button::Button(sf::String text, ButtonSize  size, sf::Vector2f position, bool active)
{
	m_size = size;
	if (!button_font.loadFromFile("resources/fonts/impact.ttf"))
		throw std::runtime_error("ResourceHolder::loadFont - Failed to load resources/fonts/impact.ttf");

	button_text.setFont(button_font);
	button_text.setString(text);
	button_text.setFillColor(sf::Color(0,0,0));

	if (size == ButtonSize::Small) 
	{
		button_text.setCharacterSize(30);

		if (!Button_texture.loadFromFile("resources/images/ButtonS.png"))
			throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/ButtonS.png");
	}
	if (size == ButtonSize::Medium)
	{
		button_text.setCharacterSize(45);

		if (!Button_texture.loadFromFile("resources/images/ButtonM.png"))
			throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/images/ButtonM.png");
	}



	Button_sprite.setTexture(Button_texture);
	Button_sprite.setPosition(position);
	
	button_text.setOrigin((button_text.getLocalBounds().width / 2), (button_text.getLocalBounds().height / 2));

	button_active = active;

	if (m_size == ButtonSize::Small)
	{
		Button_sprite.setTextureRect(sf::IntRect(0, 0, 228, 74));

		button_text.setPosition(position.x +114, position.y + 25);

	}
	if (m_size == ButtonSize::Medium)
	{
		Button_sprite.setTextureRect(sf::IntRect(0, 0, 314, 118));

		button_text.setPosition(position.x + 154, position.y + 45);

	}

	if (!button_active) 
	{
		Button_sprite.setColor(sf::Color(100, 100, 100));
	}

}
void Button::ButtonActive()
{ 
	button_active = true; 
	Button_sprite.setColor(sf::Color(255, 255, 255));
};
void Button::ButtonInactive()
{ 
	button_active = false; 
	Button_sprite.setColor(sf::Color(100, 100, 100));
};
bool Button::OnButton(sf::Vector2f A) 
{
	if (!button_active) return false;

	//if (Button_sprite.getLocalBounds().contains(A))
		//std::cout << "button";
	return Button_sprite.getGlobalBounds().contains(A);
}
void  Button::ButtonSetPosition(sf::Vector2f position)
{
	Button_sprite.setPosition(position);

	if (m_size == ButtonSize::Small)
	{

		button_text.setPosition(position.x + 114, position.y + 25);

	}
	if (m_size == ButtonSize::Medium)
	{

		button_text.setPosition(position.x + 154, position.y + 45);

	}
}
void Button::ButtonSetFocus() 
{
	InFocus = true;
}
void Button::Draw(sf::RenderWindow& mWindow) 
{
	if (InFocus) 
	{
		if (m_size == ButtonSize::Small) 
		{
			Button_sprite.setTextureRect(sf::IntRect(0,0, 228,74));
		}
		if (m_size == ButtonSize::Medium)
		{
			Button_sprite.setTextureRect(sf::IntRect(0, 0, 314, 118));
		}
		button_text.setFillColor(sf::Color(255,255, 255));
		InFocus = false;
	}
	else 
	{
		if (m_size == ButtonSize::Small)
		{
			Button_sprite.setTextureRect(sf::IntRect(0, 74, 228, 74));
		}
		if (m_size == ButtonSize::Medium)
		{
			Button_sprite.setTextureRect(sf::IntRect(0, 118, 314, 118));
		}
		button_text.setFillColor(sf::Color(0, 0, 0));
	}
	mWindow.draw(Button_sprite);
	mWindow.draw(button_text);

}