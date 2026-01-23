// Input class
// Class stores the current state on keyboard and mouse input.
// Store which keys are pressed or released, mouse position and mouse button presses.
// @author Paul Robertson EDIT Erin Michno Hughes
// @reviser William Kavanagh (2025)

#pragma once
#include <vector>
#include <SFML/Window/Keyboard.hpp>	// ScanCodeCount in constructor

class Input
{
public:
	enum class MouseState { UP, DOWN, PRESSED, SCROLL_NO, SCROLL_UP, SCROLL_DOWN};

	Input();
	// Functions for setting key as pressed, released and checking current state.
	void setKeyDown(sf::Keyboard::Scancode key);
	void setKeyUp(sf::Keyboard::Scancode key);
	bool isKeyDown(sf::Keyboard::Scancode key);
	bool isPressed(sf::Keyboard::Scancode key);

	// called every frame (from main()) to copy current over to previous
	void update();

	// Functions are mouse input, including getting and setting current position and mouse button presses.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setLeftMouse(MouseState state);
	bool isLeftMouseDown();
	bool isLeftMousePressed();
	void setRightMouse(MouseState state);
	bool isRightMouseDown();
	bool isRightMousePressed();

	// scrolling functionality (Added by hamish Glencross 23/01/2026)

	//may not need these two
	void setScrollingUp(MouseState state);
	void setScrollingDown(MouseState state);
	void setScrollingNo(MouseState state);

	bool isScrollingUp();
	bool isScrollingDown();

private:
	// booleans representing keys (pressed = true, released = false)
	std::vector<bool> m_keys;
	std::vector<bool> m_previousKeys;
	
	// Mouse structure, store mouse relevant information
	struct Mouse
	{
		int x, y;
		MouseState left, right, scroll;
	};
	// Mouse variable
	Mouse m_mouse;
};
