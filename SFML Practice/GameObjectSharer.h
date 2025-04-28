#pragma once
#include<vector>
#include<string>

class GameObject;

class GameObjectSharer 
{
public:
	// The getGameObjectsWithGOS function returns a reference to the entire vector of GameObject instances
	virtual std::vector<GameObject>& getGameObjectsWithGOS() = 0;

	// The findFirstObjectWithTag function returns just a single GameObject reference
	virtual GameObject& findFirstObjectWithTag(std::string tag) = 0;
};