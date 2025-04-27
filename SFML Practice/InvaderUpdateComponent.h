#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

class BulletSpawner;

class InvaderUpdateComponent : public UpdateComponent
{
private:
	string m_SpecificType = "invader";

	/* There is a pointer to the transform component so that the invader can move, as well as a pointer to the collider
	component so that it can update its location and be collided with */
	shared_ptr<TransformComponent> m_TC;
	shared_ptr<RectColliderComponent> m_RCC;

	/* There are pointers to the player's transform and collider so that an invader can query the position of the player and
	make decisions about when to shoot bullets */

	shared_ptr<TransformComponent> m_PlayerTC;
	shared_ptr<RectColliderComponent> m_PlayerRCC;

	BulletSpawner* m_BulletSpawner;

	float m_Speed = 10.0f;
	bool m_MovingRight = true;
	float m_TimeSinceLastShot;
	float m_TimeBetweenShots = 5.0f;
	float m_AccuracyModifier;
	float m_SpeedModifier = 0.05;
	int m_RandSeed;

public:
	void dropDownAndReverse();
	bool isMovingRight();
	void initializeBulletSpawner(BulletSpawner* bulletSpawner, int randSeed);

	/****************************************************
 *****************************************************
 From Component interface base class
 *****************************************************
 *****************************************************/
	
	string Component::getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {

		// Where is the player?
		m_PlayerTC = static_pointer_cast<TransformComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType(
				"transform", "transform"));

		m_PlayerRCC = static_pointer_cast<RectColliderComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType(
				"collider", "rect"));

		// Where is this specific invader
		m_TC = static_pointer_cast<TransformComponent>(
			self->getComponentByTypeAndSpecificType(
				"transform", "transform"));

		m_RCC = static_pointer_cast<RectColliderComponent>(
			self->getComponentByTypeAndSpecificType(
				"collider", "rect"));
	}

	/****************************************************
 *****************************************************
 From UpdateComponent
 *****************************************************
 *****************************************************/
	void update(float fps) override;
};