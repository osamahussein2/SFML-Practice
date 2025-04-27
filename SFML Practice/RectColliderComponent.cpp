#include "RectColliderComponent.h"

RectColliderComponent::RectColliderComponent(string name) {
	m_Tag = "" + name;
}

string RectColliderComponent::getColliderTag() {
	return m_Tag;
}

void RectColliderComponent::setOrMoveCollider(float x, float y, float width, float height) {

	m_Collider.position.x = x;
	m_Collider.position.y = y;
	m_Collider.size.x = width;
	m_Collider.size.y = height;
}

FloatRect& RectColliderComponent::getColliderRectF() {
	return m_Collider;
}