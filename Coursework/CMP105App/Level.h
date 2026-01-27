#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	bool m_isGameOver = false;
	bool m_timerMode;

	bool m_startedMoving;

	float m_foodTimer;
	float m_foodTimerLength;

	int m_noOfLives;
	int m_foodToWin;
	
	void handleInput(float dt) override;
	void update(float dt);
	void render();

	sf::Vector2f m_playerStartPos;

	float m_playerSpeed;

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	
	float m_gameTime;

	sf::CircleShape m_player;
	sf::CircleShape m_food;
	sf::RectangleShape m_wall;
	sf::RectangleShape m_enemy;
	
	void spawnFood();
	int m_foodEaten;

	

	enum class DirectionPressed { UP, DOWN, LEFT, RIGHT, NONE};
	DirectionPressed m_direction;
	
	//sf::Text m_dReminder;
};