#include "PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f startPosition, float gravity)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::update(float elapsedTime)
{
	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}

		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();

	// Feet
	m_Feet.position.x = r.position.x + 3;
	m_Feet.position.y = r.position.y + r.size.y - 1;
	m_Feet.size.x = r.size.x - 6;
	m_Feet.size.y = 1;

	// Head
	m_Head.position.x = r.position.x;
	m_Head.position.y = r.position.y + (r.size.y * .3);
	m_Head.size.x = r.size.x;
	m_Head.size.y = 1;

	// Right
	m_Right.position.x = r.position.x + r.size.x - 2;
	m_Right.position.y = r.position.y + r.size.y * .35;
	m_Right.size.x = 1;
	m_Right.size.y = r.size.y * .3;

	// Left
	m_Left.position.x = r.position.x;
	m_Left.position.y = r.position.y + r.size.y * .5;
	m_Left.size.x = 1;
	m_Left.size.y = r.size.y * .3;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);
}

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().size.x / 2,
		m_Position.y + m_Sprite.getGlobalBounds().size.y / 2
	);
}

FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}

void PlayableCharacter::stopFalling(float position)
{
	m_Position.y = position - getPosition().size.y;
	m_Sprite.setPosition(m_Position);

	m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position)
{
	m_Position.x = position - m_Sprite.getGlobalBounds().size.x;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().size.x;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump()
{
	// Stop a jump early
	m_IsJumping = false;
	m_IsFalling = true;
}