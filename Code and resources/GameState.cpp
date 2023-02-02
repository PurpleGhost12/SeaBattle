#include"GameState.h"
GameState::GameState()
{
	if (!window_texture.loadFromFile("resources/images/window.png"))
		throw std::runtime_error("ResourceHolder::loadImage - Failed to load resources/fonts/impact.ttf");
	window_sprite.setTexture(window_texture);
	window_sprite.setPosition(296, 225);

	if (!m_font.loadFromFile("resources/fonts/impact.ttf"))
		throw std::runtime_error("ResourceHolder::loadFont - Failed to load resources/fonts/impact.ttf");
	keyboard = KeyboardInput::none;
	mouse_move = MouseInput::none;
}

void GameState::InputKeyboard(sf::Event& mevent)
{
	if (mevent.type == sf::Event::KeyPressed || mevent.type == sf::Event::TextEntered)
	{
		keyboard = KeyboardInput::anything;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		{
			keyboard = KeyboardInput::escape;
		}
	}
	else
		keyboard = KeyboardInput::none;
}