#include "Input.h"

Input::Input()
{
	// size pressed vectors based on scanCode count
	int maxKeys = static_cast<int>(sf::Keyboard::ScancodeCount);
	m_keys.assign(maxKeys, false);
	m_previousKeys.assign(maxKeys, false);

	// set default values
	m_mouse.left = MouseState::UP;
	m_mouse.right = MouseState::UP;
	m_mouse.scroll = MouseState::SCROLL_NO;
	m_mouse.x = 0;
	m_mouse.y = 0;
}

void Input::setKeyDown(sf::Keyboard::Scancode key)
{
	int i = static_cast<int>(key);
	if (i >= 0 && i < m_keys.size())
	{
		m_keys[i] = true;
	}
}

void Input::setKeyUp(sf::Keyboard::Scancode key_pressed)
{
	int key = static_cast<int>(key_pressed);
	if (key >= 0 && key < m_keys.size())
	{
		m_keys[key] = false;
	}
}

bool Input::isKeyDown(sf::Keyboard::Scancode key_pressed)
{
	int key = static_cast<int>(key_pressed);
	if (key >= 0 && key < m_keys.size())
	{
		return m_keys[key];
	}
	return false;
}

// It is pressed if it is DOWN now, but was UP last frame.
bool Input::isPressed(sf::Keyboard::Scancode key_pressed)
{
	int key = static_cast<int>(key_pressed);
	if (key >= 0 && key < m_keys.size())
	{
		return m_keys[key] && !m_previousKeys[key];
	}
	return false;
}

void Input::update()
{
	// frame state passed to last frame history
	m_previousKeys = m_keys;

	if (m_mouse.left == MouseState::PRESSED)
	{
		m_mouse.left = MouseState::DOWN;
	}
	if (m_mouse.right == MouseState::PRESSED)
	{
		m_mouse.right = MouseState::DOWN;
	}
	if (m_mouse.scroll != MouseState::SCROLL_NO)
	{
		m_mouse.scroll = MouseState::SCROLL_NO;
	}
}

void Input::setMouseX(int lx)
{
	m_mouse.x = lx;
}

void Input::setMouseY(int ly)
{
	m_mouse.y = ly;
}

void Input::setMousePosition(int lx, int ly)
{
	setMouseX(lx);
	setMouseY(ly);
}

int Input::getMouseX()
{
	return m_mouse.x;
}

int Input::getMouseY()
{
	return m_mouse.y;
}

void Input::setLeftMouse(MouseState state)
{
	m_mouse.left = state;
}

bool Input::isLeftMouseDown()
{
	if (m_mouse.left == MouseState::DOWN || m_mouse.left == MouseState::PRESSED)
	{
		return true;
	}
	return false;
}

bool Input::isLeftMousePressed()
{
	if (m_mouse.left == MouseState::PRESSED)
	{

		return true;
	}
	return false;
}

void Input::setRightMouse(MouseState state)
{
	m_mouse.right = state;
}

bool Input::isRightMouseDown()
{
	if (m_mouse.right == MouseState::DOWN || m_mouse.right == MouseState::PRESSED)
	{
		return true;
	}
	return false;
}

bool Input::isRightMousePressed()
{
	if (m_mouse.right == MouseState::PRESSED)
	{

		return true;
	}
	return false;
}


//scrolling

void Input::setScrollingUp(MouseState state)
{
	m_mouse.scroll = state;
}

void Input::setScrollingDown(MouseState state)
{
	m_mouse.scroll = state;
}

void Input::setScrollingNo(MouseState state)
{
	m_mouse.scroll = state;
}

bool Input::isScrollingUp()
{
	if (m_mouse.scroll == MouseState::SCROLL_UP)
	{
		return true;
	}
	return false;
}

bool Input::isScrollingDown()
{
	if (m_mouse.scroll == MouseState::SCROLL_DOWN)
	{
		return true;
	}
	return false;
}

