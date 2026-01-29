#include "Sheep.h"


Sheep::Sheep() {
	for (int i = 0; i < 4; i++) {
		m_walkDown.addFrame(sf::IntRect({ i * 64, 0 }, { 64, 64 }));
		m_downRight.addFrame(sf::IntRect({ i * 64, 128 }, { 64, 64 }));
		m_up.addFrame(sf::IntRect({ i * 64 + 256, 0 }, { 64, 64 }));
		m_upRight.addFrame(sf::IntRect({ i * 64, 64 }, { 64, 64 }));
		m_right.addFrame(sf::IntRect({ i * 64 + 256, 64 }, { 64,64 }));
		m_walkDown.setFrameSpeed(.25f);
		m_walkDown.setLooping(true);
		m_downRight.setFrameSpeed(.25f);
		m_downRight.setLooping(true);
		m_up.setFrameSpeed(.25f);
		m_up.setLooping(true);
		m_upRight.setFrameSpeed(.25f);
		m_upRight.setLooping(true);
		m_right.setFrameSpeed(.25f);
		m_right.setLooping(true);
		m_currentAnimation = &m_walkDown;
	}

}

void Sheep::update(float dt) {
	m_currentAnimation->animate(dt);
	setTextureRect(m_currentAnimation->getCurrentFrame());

	if (m_gameOver) return;

	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		move({ 0, -orthog_speed });
		m_currentAnimation->setFlipped(false);
		m_currentAnimation = &m_up;
		break;
	case Direction::UP_RIGHT:
		move({ diagonal_speed, -diagonal_speed });
		m_currentAnimation->setFlipped(false);
		m_currentAnimation = &m_upRight;
		break;
	case Direction::RIGHT:
		move({ orthog_speed,0 });
		m_currentAnimation->setFlipped(false);
		m_currentAnimation = &m_right;
		break;
	case Direction::DOWN_RIGHT:
		move({ diagonal_speed, diagonal_speed });
		m_currentAnimation->setFlipped(false);
		m_currentAnimation = &m_downRight;
		break;
	case Direction::DOWN:
		move({ 0, orthog_speed });
		m_currentAnimation->setFlipped(false);
		m_currentAnimation = &m_walkDown;
		break;
	case Direction::DOWN_LEFT:
		move({ -diagonal_speed, diagonal_speed });
		m_currentAnimation->setFlipped(true);
		m_currentAnimation = &m_downRight;
		break;
	case Direction::LEFT:
		move({ -orthog_speed,0 });
		m_currentAnimation->setFlipped(true);
		m_currentAnimation = &m_right;
		break;
	case Direction::UP_LEFT:
		move({ -diagonal_speed, -diagonal_speed });
		m_currentAnimation->setFlipped(true);
		m_currentAnimation = &m_upRight;
		break;
	}

}

void Sheep::handleInput(float dt) {
	if (m_gameOver) return;
	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}

	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir) {
		m_inputBuffer = INPUT_BUFFER_LENGTH;
	}

}
