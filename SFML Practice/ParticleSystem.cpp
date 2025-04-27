#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles)
{
	m_Vertices.setPrimitiveType(PrimitiveType::Points);
	m_Vertices.resize(numParticles);

	// Create the particles
	for (int i = 0; i < numParticles; i++)
	{
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;

		Vector2f direction;

		direction = Vector2f(cos(angle) * speed, sin(angle) * speed);
		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::update(float dt)
{
	m_Duration -= dt;
	vector<Particle>::iterator i;

	int currentVertex = 0;

	/* The for loop goes through each of the Particle instances in m_Particles. For each one, it calls its update function and
	passes in dt. Each particle will update its position. */
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		// Move the particle
		(*i).update(dt);

		/* After the particle has updated itself, the appropriate vertex in m_Vertices is updated by using the particle's
		getPosition function. . At the end of each pass through the for loop, currentVertex is incremented, ready for the
		next vertex. */
		
		// Update the vertex array
		m_Vertices[currentVertex++].position = i->getPosition();
	}

	if (m_Duration < 0)
	{
		m_IsRunning = false;
	}
}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
	m_IsRunning = true;
	m_Duration = 2;

	int currentVertex = 0;

	// Iterate through all the Particle objects in m_Particles and then we do so in a for loop
	for (auto it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		/* Set each particle in the vertex array to yellow and set each position to startPosition, which was passed in as a
		parameter. Remember that each particle starts life in the same position, but they are each assigned a different
		velocity. */
		m_Vertices[currentVertex++].color = Color::Yellow;
		it->setPosition(startPosition);
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
	return m_IsRunning;
}