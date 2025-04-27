#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::update(float fps)
{
	// This condition returns true when the player has a gamepad plugged in to a USB port
	if (sf::Joystick::isConnected(0))
	{
		// The location of both the horizontal and vertical positions of the transform component are altered

		/* The m_XExtent and m_YExtent variables will be updated each frame to hold values that represent the extent to which
		the player has moved their gamepad thumbstick in a horizontal and vertical direction. The range of values is from -100
		to 100, and so the preceding code has the effect of moving the transform component at full speed in any direction when
		the thumbstick is positioned at any of its full extents or a fraction of that speed when it is partially positioned
		between the center (not moving at all) and its full extent. This means that the player will have finer control over
		the speed of the ship should they opt to use a gamepad instead of the keyboard */
		m_TC->getLocation().x += ((m_Speed / 100) * m_XExtent) * fps;
		m_TC->getLocation().y += ((m_Speed / 100) * m_YExtent) * fps;
	}

	// Left and right
	if (m_IsHoldingLeft)
	{
		m_TC->getLocation().x -= m_Speed * fps;
	}

	else if (m_IsHoldingRight)
	{
		m_TC->getLocation().x += m_Speed * fps;
	}

	// Up and down
	if (m_IsHoldingUp)
	{
		m_TC->getLocation().y -= m_Speed * fps;
	}

	else if (m_IsHoldingDown)
	{
		m_TC->getLocation().y += m_Speed * fps;
	}

	// Update the collider
	m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y, m_TC->getSize().x, m_TC->getSize().y);

	// Make sure the ship doesn't go outside the allowed area
	if (m_TC->getLocation().x > WorldState::WORLD_WIDTH - m_TC->getSize().x)
	{
		m_TC->getLocation().x = WorldState::WORLD_WIDTH - m_TC->getSize().x;
	}

	else if (m_TC->getLocation().x < 0)
	{
		m_TC->getLocation().x = 0;
	}

	if (m_TC->getLocation().y > WorldState::WORLD_HEIGHT - m_TC->getSize().y)
	{
		m_TC->getLocation().y = WorldState::WORLD_HEIGHT - m_TC->getSize().y;
	}

	else if (m_TC->getLocation().y < WorldState::WORLD_HEIGHT / 2)
	{
		m_TC->getLocation().y = WorldState::WORLD_HEIGHT / 2;
	}
}

void PlayerUpdateComponent::updateShipTravelWithController(float x, float y)
{
	m_XExtent = x;
	m_YExtent = y;
}

void PlayerUpdateComponent::moveLeft()
{
	m_IsHoldingLeft = true;
	stopRight();
}

void PlayerUpdateComponent::moveRight()
{
	m_IsHoldingRight = true;
	stopLeft();
}

void PlayerUpdateComponent::moveUp()
{
	m_IsHoldingUp = true;
	stopDown();
}

void PlayerUpdateComponent::moveDown()
{
	m_IsHoldingDown = true;
	stopUp();
}

void PlayerUpdateComponent::stopLeft()
{
	m_IsHoldingLeft = false;
}

void PlayerUpdateComponent::stopRight()
{
	m_IsHoldingRight = false;
}

void PlayerUpdateComponent::stopUp()
{
	m_IsHoldingUp = false;
}

void PlayerUpdateComponent::stopDown()
{
	m_IsHoldingDown = false;
}