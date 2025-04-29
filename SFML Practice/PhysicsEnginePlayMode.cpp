#include "DevelopState.h"
#include "PhysicsEnginePlayMode.h"
#include <iostream>
#include "SoundEngine.h"
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectInvaderCollisions(vector<GameObject>& objects, const vector<int>& bulletPositions)
{
	Vector2f offScreen(-1, -1);
	auto invaderIt = objects.begin();
	auto invaderEnd = objects.end();

	for (invaderIt; invaderIt != invaderEnd; ++invaderIt)
	{
		// The first if statement checks whether the current game object is both active and an invader
		if ((*invaderIt).isActive() && (*invaderIt).getTag() == "invader")
		{
			auto bulletIt = objects.begin();

			// Jump to the first bullet
			advance(bulletIt, bulletPositions[0]);
			auto bulletEnd = objects.end();

			/* If it is an active invader, another loop is entered and each of the game objects that represents a bullet is
			looped through */
			for (bulletIt; bulletIt != bulletEnd; ++bulletIt)
			{
				/* The next if statement checks whether the current invader has collided with the current bullet and whether
				that bullet was fired by the player (we don't want invaders shooting themselves) */
				if ((*invaderIt).getEncompassingRectCollider().findIntersection((*bulletIt) .getEncompassingRectCollider())
					&& (*bulletIt).getTag() == "bullet" 
					&& static_pointer_cast<BulletUpdateComponent>((*bulletIt).getFirstUpdateComponent())->m_BelongsToPlayer)
				{
					/* When this test is true, a sound is played, the bullet is moved off-screen, the number of invaders is
					decremented, the player's score is increased, and the invader is set to inactive */
					SoundEngine::playInvaderExplode();

					(*invaderIt).getTransformComponent()->getLocation() = offScreen;
					(*bulletIt).getTransformComponent()->getLocation() = offScreen;

					WorldState::SCORE++;
					WorldState::NUM_INVADERS--;
					(*invaderIt).setInactive();
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::detectPlayerCollisionsAndInvaderDirection(vector<GameObject>& objects, 
	const vector<int>& bulletPositions)
{
	Vector2f offScreen(-1, -1);

	FloatRect playerCollider = 
		m_Player->getEncompassingRectCollider();

	shared_ptr<TransformComponent> playerTransform = 
		m_Player->getTransformComponent();

	Vector2f playerLocation = 
		playerTransform->getLocation();

	auto it3 = objects.begin();
	auto end3 = objects.end();

	// Loop through all game objects
	for (it3; it3 != end3; ++it3)
	{
		/* The first if test checks whether the current object is active, has a collider, and is not the player. We don't want
		to test the player colliding with themselves */
		if ((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() != "Player")
		{
			// Get a reference to all the parts of the current game object we might need
			FloatRect currentCollider = (*it3).getEncompassingRectCollider();

			// Detect collisions between objects with the player
			if (currentCollider.findIntersection(playerCollider))
			{
				if ((*it3).getTag() == "bullet")
				{
					SoundEngine::playPlayerExplode();
					WorldState::LIVES--;
					(*it3).getTransformComponent()->
						getLocation() = offScreen;
				}

				if ((*it3).getTag() == "invader")
				{
					SoundEngine::playPlayerExplode();
					SoundEngine::playInvaderExplode();
					WorldState::LIVES--;
					(*it3).getTransformComponent()->
						getLocation() = offScreen;

					WorldState::SCORE++;
					(*it3).setInactive();
				}
			}

			shared_ptr<TransformComponent>
				currentTransform =
				(*it3).getTransformComponent();

			Vector2f currentLocation =
				currentTransform->getLocation();

			string currentTag = (*it3).getTag();
			Vector2f currentSize =
				currentTransform->getSize();

			// Handle the direction and descent of the invaders
			if (currentTag == "invader")
			{
				// This is an invader
				if (!m_NeedToDropDownAndReverse &&
					!m_InvaderHitWallThisFrame)
				{
					// Currently no need to dropdown 
					// and reverse from previous frame 
					// or any hits this frame
					if (currentLocation.x >=
						WorldState::WORLD_WIDTH - currentSize.x)
					{
						// The invader is passed its furthest right position
						if (static_pointer_cast
							<InvaderUpdateComponent>((*it3)
								.getFirstUpdateComponent())->
							isMovingRight())
						{
							// The invader is travelling right so set 
							// a flag that an invader has collided 
							m_InvaderHitWallThisFrame = true;
						}
					}
					else if (currentLocation.x < 0)
					{
						// The invader is past its furthest left position
						if (!static_pointer_cast<InvaderUpdateComponent>(
							(*it3).getFirstUpdateComponent())->isMovingRight())
						{
							// The invader is travelling left so 
							// set a flag that an invader has collided 
							m_InvaderHitWallThisFrame = true;
						}
					}
				}
				else if (m_NeedToDropDownAndReverse
					&& !m_InvaderHitWallPreviousFrame)
				{
					// Drop down and reverse has been set
					if ((*it3).hasUpdateComponent())
					{
						// Drop down and reverse
						static_pointer_cast<InvaderUpdateComponent>(
							(*it3).getFirstUpdateComponent())
							->dropDownAndReverse();
					}
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::handleInvaderDirection()
{
	/* This function just sets and unsets Booleans accordingly so that the next pass through the 
	detectPlayerCollisionAndDirection function will actually drop-down the invaders and change their direction */
	if (m_InvaderHitWallThisFrame) 
	{
		m_NeedToDropDownAndReverse = true;
		m_InvaderHitWallThisFrame = false;
	}

	else {
		m_NeedToDropDownAndReverse = false;
	}
}

void PhysicsEnginePlayMode::initilize(GameObjectSharer& gos) 
{
	/* The pointer to PlayerUpdateComponent is initialized, as well as the pointer to the player GameObject. This will avoid
	calling these relatively slow functions during the game loop */
	m_PUC = static_pointer_cast<PlayerUpdateComponent>(
		gos.findFirstObjectWithTag("Player")
		.getComponentByTypeAndSpecificType("update", "player"));

	m_Player = &gos.findFirstObjectWithTag("Player");
}

void PhysicsEnginePlayMode::detectCollisions(
	vector<GameObject>& objects,
	const vector<int>& bulletPositions)
{
	detectInvaderCollisions(objects, bulletPositions);
	detectPlayerCollisionsAndInvaderDirection(
		objects, bulletPositions);

	handleInvaderDirection();
}