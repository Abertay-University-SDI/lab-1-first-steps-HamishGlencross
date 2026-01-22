#pragma once

#include "Framework/BaseLevel.h"

class Level : BaseLevel{
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

	sf::Vector2f m_playerStartPos;

	float m_playerSpeed;

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	
	sf::CircleShape m_player;

	//sf::Text m_dReminder;
};