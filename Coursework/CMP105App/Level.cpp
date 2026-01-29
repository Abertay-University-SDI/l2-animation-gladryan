#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	m_sheepTexture.loadFromFile("gfx/sheep_sheet.png");
	sf::IntRect texture_rect({ 12, 8 }, { 40, 48 });
	m_sheep.setTexture(&m_sheepTexture);
	m_sheep.setTextureRect(texture_rect);
	m_sheep.setSize({ 100, 100 });

	m_sheep.setInput(&m_input);
}

// handle user input
void Level::handleInput(float dt)
{
	m_sheep.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	if (m_sheep.m_gameOver) return;
	sf::Vector2f pos = m_sheep.getPosition();
	sf::Vector2f size = m_sheep.getSize();

	if (pos.x < 0 || pos.x + size.x > m_window.getSize().x || pos.y < 0 || pos.y + size.y > m_window.getSize().y)
	{
		m_sheep.m_gameOver = true;
		std::cout << "Game Over!";
	};
	m_sheep.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_sheep);
	endDraw();
}

