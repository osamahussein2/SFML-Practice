#include "Engine.h"
bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;

	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;
	block.size.x = TILE_SIZE;
	block.size.y = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.position.x / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.position.y / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.position.x / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.position.y / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero or higher than the end of the array
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;

	if (endX >= m_LM.getLevelSize().x) endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y) endY = m_LM.getLevelSize().y;

	// Has the character fallen out of the map?
	FloatRect level(Vector2f(0, 0), Vector2f(m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE));

	if (!character.getPosition().findIntersection(level))
	{
		// respawn the character
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	// Loop through all the local blocks
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.position.x = x * TILE_SIZE;
			block.position.y = y * TILE_SIZE;

			// Has character been burnt or drowned?
			// Use head as this allows him to sink a bit
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().findIntersection(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);

					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2) // Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();
					}

					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}

			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().findIntersection(block))
				{
					character.stopRight(block.position.x);
				}

				else if (character.getLeft().findIntersection(block))
				{
					character.stopLeft(block.position.x);
				}

				if (character.getFeet().findIntersection(block))
				{
					character.stopFalling(block.position.y);
				}

				else if (character.getHead().findIntersection(block))
				{
					character.stopJump();
				}
			}

			// More collision detection here once we have
			// learned about particle effects
			
			// Have the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this by seeing if an effect is already running
			if (!m_PS.running()) 
			{
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().findIntersection(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());
					}
				}
			}

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}
		}
	}

	// All done, return, whether or not a new level might be required
	return reachedGoal;
}