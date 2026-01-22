#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{	
	srand(time(0));
	
	m_gameTime = 0.f;
	m_foodEaten = 0;

	// initialise game objects

	m_player.setRadius(10.f);
	m_player.setFillColor(sf::Color::Magenta);
	m_player.setPosition({ 300.f, 300.f });

	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Yellow);

	spawnFood();

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
		m_direction = DirectionPressed::RIGHT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
	{
		std::cout << "S pressed" << std::endl;
		m_direction = DirectionPressed::DOWN;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		std::cout << "A pressed" << std::endl;
		m_direction = DirectionPressed::LEFT;
	}
	if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
	{
		std::cout << "W pressed" << std::endl;
		m_direction = DirectionPressed::UP;
	}

}

// Update game objects
void Level::update(float dt)
{
	if (m_isGameOver) 
	{
		return;
	}

	m_playerStartPos = { m_window.getSize().x/2.f, m_window.getSize().y/2.f};
	
	//==========
	// Bounding
	//==========

	if (m_player.getPosition().x > m_window.getSize().x || 
		m_player.getPosition().x < 0 || 
		m_player.getPosition().y > m_window.getSize().y || 
		m_player.getPosition().y < 0)
	{
		std::cout << "GAME OVER" << std::endl;
		std::cout << "Game Time: " << m_gameTime << std::endl;
		std::cout << "Food Eaten: " << m_foodEaten << std::endl;

		m_isGameOver = true;
	}

	//====================
	// direction changing
	//====================

	switch (m_direction)
	{
	case Level::DirectionPressed::UP:
		m_player.move({ 0,-m_playerSpeed * dt });
		break;
	case Level::DirectionPressed::DOWN:
		m_player.setPosition({ m_player.getPosition().x, m_player.getPosition().y + m_playerSpeed * dt });
		break;
	case Level::DirectionPressed::LEFT:
		m_player.move({ -m_playerSpeed * dt,0 });
		break;
	case Level::DirectionPressed::RIGHT:
		m_player.move({ m_playerSpeed * dt,0 });
		break;
	default:
		break;
	}

	//===========
	// Collision
	//===========

	float x_dist = (m_player.getPosition().x + m_player.getRadius()) - (m_food.getPosition().x + m_food.getRadius());
	float y_dist = (m_player.getPosition().y + m_player.getRadius()) - (m_food.getPosition().y + m_food.getRadius());

	float squared_dist = (x_dist * x_dist) + (y_dist * y_dist);
	float radii_sum = m_player.getRadius() + m_food.getRadius();

	if (squared_dist < (radii_sum * radii_sum))
	{
		//collision detected
		m_foodEaten++;

		spawnFood();
		m_playerSpeed *= 1.1f;
	}

	m_gameTime += dt;
}

void Level::spawnFood()
{
	float x = rand() % m_window.getSize().x;
	float y = rand() % m_window.getSize().y;

	m_food.setPosition({x,y});
}

// Render level
void Level::render()
{
	beginDraw();

	m_window.draw(m_player);

	m_window.draw(m_food);

	endDraw();
}



