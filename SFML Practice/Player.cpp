#include "Player.h"
#include "TextureHolder.h"

Player::Player() : m_Sprite(Sprite(m_Texture))
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	// 
	//m_Texture.loadFromFile("graphics/player (1).png");
	//m_Sprite = Sprite(m_Texture);

	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/player (1).png"));
	//m_Sprite.setTexture(m_Texture);

	// Set the origin of the sprite to the center for smooth rotation
	m_Sprite.setOrigin(Vector2f(25, 25));
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	m_Position.x = arena.size.x / 2;
	m_Position.y = arena.size.y / 2;

	// Copy the details of the arena to the player's m_Arena
	m_Arena.position.x = arena.position.x;
	m_Arena.size.x = arena.size.x;
	m_Arena.position.y = arena.position.y;
	m_Arena.size.y = arena.size.y;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Store the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return m_LastHit;
}
bool Player::hit(Time timeHit)
{
	/* This if statement checks to see whether the time that's passed in as a parameter is 200 milliseconds further ahead
	than the time stored in m_LastHit. If it is, m_LastHit is updated with the time passed in and m_Health has 10 deducted
	from its current value */
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;

		return true;
	}

	else
	{
		return false;
	}
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

Angle Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	// Keep the player in the arena
	if (m_Position.x > m_Arena.size.x - m_TileSize)
	{
		// This calculation will detect the player straying into the wall
		m_Position.x = m_Arena.size.x - m_TileSize;
	}

	if (m_Position.x < m_Arena.position.x + m_TileSize)
	{
		m_Position.x = m_Arena.position.x + m_TileSize;
	}

	if (m_Position.y > m_Arena.size.y - m_TileSize)
	{
		m_Position.y = m_Arena.size.y - m_TileSize;
	}

	if (m_Position.y < m_Arena.position.y + m_TileSize)
	{
		m_Position.y = m_Arena.position.y + m_TileSize;
	}

	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / 3.141;
	m_Sprite.setRotation(degrees(angle));
}

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * 0.2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * 0.2);
}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}