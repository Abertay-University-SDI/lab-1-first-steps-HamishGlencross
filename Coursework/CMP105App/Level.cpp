#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{	
	srand(time(0));

	m_timerMode = false;

	m_startedMoving = false;
	
	m_foodTimerLength = 5;
	m_foodTimer = m_foodTimerLength;
	
	m_foodToWin = 10;
	m_noOfLives = 3;

	m_gameTime = 0.f;
	m_foodEaten = 0;

	// initialise game objects

	m_player.setRadius(10.f);
	m_player.setFillColor(sf::Color::Magenta);
	m_player.setPosition({ 300.f, 300.f });

	m_food.setRadius(5.f);
	m_food.setFillColor(sf::Color::Yellow);

	m_wall.setSize({ 50.f,25.f });
	m_wall.setPosition({ 600.f, 300.f });

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
	if (!m_isGameOver)
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
		if (m_input.isScrollingUp())
		{
			std::cout << "Scrolled Up" << std::endl;
			m_player.setRadius(m_player.getRadius() * 1.05);
		}
		if (m_input.isScrollingDown())
		{
			std::cout << "Scrolled Down" << std::endl;
			m_player.setRadius(m_player.getRadius() / 1.05);
		}
	}
}

// Update game objects
void Level::update(float dt)
{
	if (m_isGameOver)
	{
		return;
	}

	// In update because can be changed while playing
	m_playerStartPos = { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f };

	m_player.setOrigin({ m_player.getRadius(), m_player.getRadius() });


	//================
	// Wall collision
	//================

	if (m_timerMode)
	{
		if (m_player.getPosition().x > m_window.getSize().x)
		{
			m_player.setPosition({ 0 , m_player.getPosition().y });
		}
		if (m_player.getPosition().x < 0)
		{
			m_player.setPosition({ (float)m_window.getSize().x , m_player.getPosition().y });
		}
		if (m_player.getPosition().y > m_window.getSize().y)
		{
			m_player.setPosition({ m_player.getPosition().x , 0 });
		}
		if (m_player.getPosition().y < 0)
		{
			m_player.setPosition({ m_player.getPosition().x , (float)m_window.getSize().y });
		}
			
		//Also should account for radius
	}
	else
	{
		if (m_player.getPosition().x > m_window.getSize().x ||
		m_player.getPosition().x < 0 || 
		m_player.getPosition().y > m_window.getSize().y || 
		m_player.getPosition().y < 0)
		{
			m_noOfLives--;

			if (m_noOfLives > 0)
			{
				std::cout << "You lost a life, Lives left: " << m_noOfLives << std::endl;

				m_player.setPosition({ m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
				m_direction = Level::DirectionPressed::NONE;
			}
			else
			{
				std::cout << "GAME OVER" << std::endl;
				std::cout << "Game Time: " << m_gameTime << std::endl;
				std::cout << "Food Eaten: " << m_foodEaten << std::endl;

				m_isGameOver = true;
			}
		}		
	}

	//====================
	// direction changing
	//====================

	switch (m_direction)
	{
	case Level::DirectionPressed::UP:
		m_player.move({ 0,-m_playerSpeed * dt });
		m_startedMoving = true;
		break;
	case Level::DirectionPressed::DOWN:
		m_player.setPosition({ m_player.getPosition().x, m_player.getPosition().y + m_playerSpeed * dt });
		m_startedMoving = true;
		break;
	case Level::DirectionPressed::LEFT:
		m_player.move({ -m_playerSpeed * dt,0 });
		m_startedMoving = true;
		break;
	case Level::DirectionPressed::RIGHT:
		m_player.move({ m_playerSpeed * dt,0 });
		m_startedMoving = true;
		break;
	case Level::DirectionPressed::NONE:
		break;
	default:
		break;
	}

	//================
	// Food Collision
	//================

	if (m_player.getGlobalBounds().findIntersection(m_food.getGlobalBounds()))
	{
		//collision detected
		m_foodEaten++;

		spawnFood();
		m_playerSpeed *= 1.1f;

		if (m_timerMode)
		{
			m_foodTimer = m_foodTimerLength;
		}
	}

	//======================
	// Wall/Enemy Collision
	//======================
	
	//eeek

	if (m_wall.getGlobalBounds().findIntersection(m_player.getGlobalBounds()) && !m_timerMode)
	{
		std::cout << "You lost a life, Lives left: " << m_noOfLives << std::endl;

		m_player.setPosition({ m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
		m_direction = Level::DirectionPressed::NONE;
	}
	


	//===============
	// Win Detection
	//===============

	if (m_foodEaten >= m_foodToWin)
	{
		m_isGameOver = true;

		std::cout << "YOU WIN!" << std::endl;
		std::cout << "Game Time: " << m_gameTime << std::endl;
		//std::cout << "Food Eaten: " << m_foodEaten << std::endl;
	}

	//===========================
	// Timer mode loss detection
	//===========================

	if (m_timerMode)
	{
		if (m_foodTimer < 0)
		{
			std::cout << "GAME OVER" << std::endl;
			std::cout << "Game Time: " << m_gameTime << std::endl;
			std::cout << "Food Eaten: " << m_foodEaten << std::endl;

			m_isGameOver = true;
		}
	}

	if (m_timerMode && m_startedMoving) 
	{
		m_foodTimer -= dt;
	}

	m_gameTime += dt;
}

void Level::spawnFood()
{
	float x = rand() % (m_window.getSize().x);
	float y = rand() % (m_window.getSize().y);

	//ensures food doesnt spawn too close to the edge

	if (x < m_player.getRadius() * 1.25f) { x += m_player.getRadius(); }
	if (x > m_window.getSize().x - (m_player.getRadius() * 1.25f)) { x -= m_player.getRadius(); }
	if (y < m_player.getRadius() * 1.25f) { x += m_player.getRadius(); }
	if (y > m_window.getSize().y - (m_player.getRadius() * 1.25f)) { y -= m_player.getRadius(); }

	if (m_wall.getGlobalBounds().contains({ x, y }))
	{
		x *= rand() % 2;
		y *= rand() % 2;
	}

	m_food.setPosition({x,y});
}

// Render level
void Level::render()
{
	beginDraw();

	m_window.draw(m_player);

	m_window.draw(m_food);

	m_window.draw(m_wall);

	endDraw();
}