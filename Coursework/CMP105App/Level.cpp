#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// initialise game objects

	m_player.setRadius(10.f);
	m_player.setFillColor(sf::Color::Magenta);
	m_player.setPosition({ 300.f, 300.f });

	m_playerStartPos = { 300.f, 300.f };

	m_playerSpeed = 300;

	/*
	m_dReminder.
	m_dReminder.setPosition({ 300, 100 });
	m_dReminder.setString("Move right is D");
	*/
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_input.isLeftMousePressed())
	{
		std::cout << "left mouse pressed" << std::endl;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::D)) 
	{
		std::cout << "D pressed" << std::endl;
		m_player.move({ m_playerSpeed * dt,0 });
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		std::cout << "S pressed" << std::endl;
		m_player.setPosition({ m_player.getPosition().x, m_player.getPosition().y + m_playerSpeed * dt });
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		std::cout << "A pressed" << std::endl;
		m_player.move({ -m_playerSpeed * dt,0 });
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		std::cout << "W pressed" << std::endl;
		m_player.move({ 0,-m_playerSpeed*dt});
	}

}

// Update game objects
void Level::update(float dt)
{
	if (m_player.getPosition().x > m_window.getSize().x || 
		m_player.getPosition().x < 0 || 
		m_player.getPosition().y > m_window.getSize().y || 
		m_player.getPosition().y < 0)
	{
		m_player.setPosition(m_playerStartPos);
	}

}

// Render level
void Level::render()
{
	beginDraw();

	m_window.draw(m_player);

	endDraw();
}

