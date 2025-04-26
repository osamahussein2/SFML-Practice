#include "Engine.h"

void Engine::loadLevel()
{
	// Set m_Playing to false to stop parts of the update function from executing
	m_Playing = false;

	/* Loop through all the horizontal arrays within m_ArrayLevel and delete them. After the for loop, we delete m_ArrayLevel
	itself. */

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];
	}

	delete[] m_ArrayLevel;

	/* m_ArrayLevel = m_LM.nextLevel(m_VALevel) calls nextLevel and prepares the VertexArray m_VALevel, as well as the
	two-dimensional array known as m_ArrayLevel. The level is set up and ready to go. */

	// Load the next 2d array with the map for the level and repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn Thomas and Bob
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
	m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}