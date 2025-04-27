#include "DevelopState.h"
#include "GameObject.h"
#include <iostream>
#include "UpdateComponent.h"
#include "RectColliderComponent.h"

void GameObject::update(float fps)
{
	/* Inside the update function, a test is done to see if this GameObject instance is active and has an update component. A
	game object does not have to have an update component, although it is true that all the game objects in this project do. */
	if (m_Active && m_HasUpdateComponent)
	{
		/* Loop through all the components it has, starting from m_FirstUpdateComponent through to m_FirstUpdateComponent +
		m_NumberUpdateComponents. This code implies that a game object can have multiple update components */
		for (int i = m_FirstUpdateComponentLocation; i < m_FirstUpdateComponentLocation + m_NumberUpdateComponents; i++)
		{
			/* It is because a component could be one of many types that we create a temporary update-related component
			(tempUpdate), cast the component from the vector of components to UpdateComponent */
			shared_ptr<UpdateComponent> tempUpdate = static_pointer_cast<UpdateComponent>(m_Components[i]);

			if (tempUpdate->enabled())
			{
				tempUpdate->update(fps);
			}
		}
	}
}

void GameObject::draw(RenderWindow& window)
{
	/* Check whether the game object is active and that it has a graphics component. If it does, then a check is done to see
	if the graphics component is enabled. If all these tests succeed, then the draw function is called */
	if (m_Active && m_HasGraphicsComponent)
	{
		if (m_Components[m_GraphicsComponentLocation]->enabled())
		{
			getGraphicsComponent()->draw(window, getTransformComponent());
		}
	}
}

shared_ptr<GraphicsComponent> GameObject::getGraphicsComponent()
{
	/* The getGraphicsComponent function gives any code that has an instance of the contained game object access to the
	graphics component */
	return static_pointer_cast<GraphicsComponent>(m_Components[m_GraphicsComponentLocation]);
}

shared_ptr<TransformComponent> GameObject::getTransformComponent()
{
	/* The getTransformComponent function gives any code that has an instance of the contained game object access to the
	transform component */
	return static_pointer_cast<TransformComponent>(m_Components[m_TransformComponentLocation]);
}

void GameObject::addComponent(shared_ptr<Component> component)
{
	/* The first thing that happens inside the function is that the Component instance is added to the m_Components vector.
	Next, the component is enabled using the enabled function. */
	m_Components.push_back(component);
	component->enableComponent();

	if (component->getType() == "update")
	{
		m_HasUpdateComponent = true;
		m_NumberUpdateComponents++;

		if (m_NumberUpdateComponents == 1)
		{
			m_FirstUpdateComponentLocation =
				m_Components.size() - 1;
		}
	}

	else if (component->getType() == "graphics")
	{
		// No iteration in the draw method required
		m_HasGraphicsComponent = true;
		m_GraphicsComponentLocation = m_Components.size() - 1;
	}

	else if (component->getType() == "transform")
	{
		// Remember where the Transform component is
		m_TransformComponentLocation = m_Components.size() - 1;
	}

	else if (component->getType() == "collider" && component->getSpecificType() == "rect")
	{
		// Remember where the collider component(s) is
		m_HasCollider = true;
		m_NumberRectColliderComponents++;

		if (m_NumberRectColliderComponents == 1)
		{
			m_FirstRectColliderComponentLocation =
				m_Components.size() - 1;
		}
	}
}

void GameObject::setActive()
{
	m_Active = true;
}

void GameObject::setInactive()
{
	m_Active = false;
}

bool GameObject::isActive()
{
	return m_Active;
}

void GameObject::setTag(String tag)
{
	m_Tag = "" + tag;
}

std::string GameObject::getTag()
{
	return m_Tag;
}

void GameObject::start(GameObjectSharer* gos)
{
	/* The start function gives access to any component in any game object the components of any other game object. The start
	function is called once all the GameObject instances have been composed from all their components */
	auto it = m_Components.begin();
	auto end = m_Components.end();

	// Loop through every component and shares a new class instance, a GameObjectSharer instance
	for (it; it != end; ++it)
	{
		/* When start is called on each component, the this pointer is also passed in to give each component easy access to
		its contained GameObject instance */
		(*it)->start(gos, this);
	}
}

// Slow - only use in start function
shared_ptr<Component> GameObject::getComponentByTypeAndSpecificType(string type, string specificType)
{
	auto it = m_Components.begin();
	auto end = m_Components.end();

	/* The getComponentByTypeAndSpecificType function has a nested for loop that looks for a match of a component type to the
	first string parameter and then looks for a match of the specific component type in the second string parameter */
	for (it; it != end; ++it)
	{
		/* The code needs to know exactly what derived Component type is being returned so that it can cast it to the
		required type */
		if ((*it)->getType() == type)
		{
			if ((*it)->getSpecificType() == specificType)
			{
				// Return a shared pointer to a base class Component instance
				return (*it);
			}
		}
	}
#ifdef debuggingErrors
cout << "GameObject.cpp::getComponentByTypeAndSpecificType-" << "COMPONENT NOT FOUND ERROR!" << endl;
#endif

return m_Components[0];
}

FloatRect& GameObject::getEncompassingRectCollider()
{
	/* The getEncompassingRectCollider function checks whether the game object has a collider and, if it has, returns it to
	the calling code */
	if (m_HasCollider)
	{
		return (static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation]))
			->getColliderRectF();
	}
}

string GameObject::getEncompassingRectColliderTag()
{
	/* This simple function returns the tag of the collider. This will be useful for determining what type of object is being
	tested for collision */
	return static_pointer_cast<RectColliderComponent>(m_Components[m_FirstRectColliderComponentLocation])->getColliderTag();
}

shared_ptr<UpdateComponent> GameObject::getFirstUpdateComponent()
{
	/* getFirstUpdateComponent uses the m_FirstUpdateComponent variable to locate the update component and then returns it to
	the calling code */
	return static_pointer_cast<UpdateComponent>(m_Components[m_FirstUpdateComponentLocation]);
}

bool GameObject::hasCollider()
{
	return m_HasCollider;
}

bool GameObject::hasUpdateComponent()
{
	return m_HasUpdateComponent;
}