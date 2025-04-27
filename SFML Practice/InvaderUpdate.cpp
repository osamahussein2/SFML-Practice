#include "InvaderUpdateComponent.h"
#include "BulletSpawner.h"
#include "WorldState.h"
#include "SoundEngine.h"

void InvaderUpdateComponent::update(float fps)
{
	// The first if and else blocks move the invader right or left each frame
	if (m_MovingRight)
	{
		m_TC->getLocation().x += m_Speed * fps;
	}
	else
	{
		m_TC->getLocation().x -= m_Speed * fps;
	}

	// Update the collider to the new position
	m_RCC->setOrMoveCollider(m_TC->getLocation().x, m_TC->getLocation().y, m_TC->getSize().x, m_TC->getSize().y);
	
	/* This code tracks how long it's been since this invader last fired a shot and then tests to see if the player is one
	world unit to the left or right of the invader (+ or – for the random accuracy modifier, so that each invader is a little
	bit different) */
	m_TimeSinceLastShot += fps;

	// Is the middle of the invader above the
	// player +- 1 world units
	if ((m_TC->getLocation().x + (m_TC->getSize().x / 2)) > (m_PlayerTC->getLocation().x - m_AccuracyModifier) &&
		(m_TC->getLocation().x + (m_TC->getSize().x / 2)) < (m_PlayerTC->getLocation().x + 
			(m_PlayerTC->getSize().x + m_AccuracyModifier)))
	{
		/* Inside the preceding if test, another test makes sure that the invader has waited long enough since the last shot
		it took. If it has, then a shot is taken. A sound is played, a spawn location for the bullet is calculated, the
		spawnBullet function of the BulletSpawner instance is called, and a new random time to wait before another shot can be
		taken is calculated */

		// Has the invader waited long enough since the last shot
		if (m_TimeSinceLastShot > m_TimeBetweenShots)
		{
			SoundEngine::playShoot();
			Vector2f spawnLocation;

			spawnLocation.x = m_TC->getLocation().x + m_TC->getSize().x / 2;
			spawnLocation.y = m_TC->getLocation().y + m_TC->getSize().y;

			m_BulletSpawner->spawnBullet(spawnLocation, false);
			
			srand(m_RandSeed);
			int mTimeBetweenShots = (((rand() % 10)) + 1) / WorldState::WAVE_NUMBER;

			m_TimeSinceLastShot = 0;
		}
	}
}

void InvaderUpdateComponent::dropDownAndReverse()
{
	// Reverse direction
	m_MovingRight = !m_MovingRight;

	// The vertical location is increased by the height of an invader
	m_TC->getLocation().y += m_TC->getSize().y;

	/* The speed of the invader is increased relative to how many waves the player has cleared and how many invaders remain to
	be destroyed. The more waves that are cleared and the fewer invaders remaining, the faster the invaders will move */
	m_Speed += (WorldState::WAVE_NUMBER) + (WorldState::NUM_INVADERS_AT_START - WorldState::NUM_INVADERS) * m_SpeedModifier;
}

bool InvaderUpdateComponent::isMovingRight()
{
	/* It will be used to test whether to look out for collisions with the left of the screen (when moving left) or the right
	of the screen (when moving right) and will allow the collision to trigger a call to the dropDownAndReverse function */
	return m_MovingRight;
}

void InvaderUpdateComponent::initializeBulletSpawner(BulletSpawner* bulletSpawner, int randSeed)
{
	m_BulletSpawner = bulletSpawner;
	m_RandSeed = randSeed;

	// Set up the random values that make each invader behave slightly differently from the others
	srand(m_RandSeed);

	m_TimeBetweenShots = (rand() % 15 + m_RandSeed);
	m_AccuracyModifier = (rand() % 2);

	m_AccuracyModifier += 0 + static_cast<float>(rand()) / (static_cast <float> (RAND_MAX / (10)));
}