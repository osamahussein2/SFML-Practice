#include "LevelManager.h"
#include "PlayModeObjectLoader.h"
#include <iostream>

void LevelManager::loadGameObjectsForPlayMode(string screenToLoad)
{
	/* The loadLevelForPlayMode function clears the vector, instantiates a PlayModeObjectLoader instance that does all the
	file reading, and packs the GameObject instances in the vector */
	m_GameObjects.clear();
	string levelToLoad = "" + WORLD_FOLDER + SLASH + screenToLoad;

	PlayModeObjectLoader pmol;
	pmol.loadGameObjectsForPlayMode(levelToLoad, m_GameObjects);

	runStartPhase();
}

vector<GameObject>& LevelManager::getGameObjects()
{
	return m_GameObjects;
}

void LevelManager::runStartPhase()
{
	/* All the GameObject instances are passed a GameObjectSharer (this) and given the opportunity to set themselves up,
	ready to be played */
	auto it = m_GameObjects.begin();
	auto end = m_GameObjects.end();

	for (it; it != end; ++it)
	{
		(*it).start(this);
	}

	activateAllGameObjects();
}
void LevelManager::activateAllGameObjects()
{
	auto it = m_GameObjects.begin();
	auto end = m_GameObjects.end();

	// Loop through the vector to call setActive on every GameObject instance
	for (it; it != end; ++it)
	{
		(*it).setActive();
	}
}