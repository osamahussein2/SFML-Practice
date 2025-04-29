#pragma once
#include "GameObject.h"
#include <vector>
#include <string>
#include "GameObjectSharer.h"

using namespace std;

class LevelManager : public GameObjectSharer 
{
private:
	vector<GameObject> m_GameObjects;

	const std::string WORLD_FOLDER = "world";
	const std::string SLASH = "/";

	void runStartPhase();
	void activateAllGameObjects();

public:
	vector<GameObject>& getGameObjects();
	void loadGameObjectsForPlayMode(string screenToLoad);

	/****************************************************
	*****************************************************
	From GameObjectSharer interface
	*****************************************************
	*****************************************************/

	vector<GameObject>& GameObjectSharer::getGameObjectsWithGOS()
	{
		return m_GameObjects;
	}

	GameObject& GameObjectSharer::findFirstObjectWithTag(string tag)
	{
		auto it = m_GameObjects.begin();
		auto end = m_GameObjects.end();

		/* This allows any class with a GameObjectSharer instance to track down a specific game object using its tag. The
		code loops through all the GameObject instances in the vector and returns the first match */
		for (it; it != end; ++it)
		{
			if ((*it).getTag() == tag)
			{
				return (*it);
			}
		}

		/* If no match is found, a null pointer will be returned and crash the game. We use an #ifdef statement to output
		some text to the console to tell us what caused the crash so that we won't be scratching our heads for hours should
		we accidentally search for a tag that doesn't exist */
#ifdef debuggingErrors
		cout << "LevelManager.h findFirstGameObjectWithTag() " << "- TAG NOT FOUND ERROR!" << endl;
#endif
		return m_GameObjects[0];
	}
};