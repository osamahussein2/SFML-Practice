#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

void GameOverInputHandler::handleKeyPressed(std::optional<Event> event, RenderWindow& window)
{
	if (event->is<Event::KeyPressed>() == Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleLeftClick(std::string& buttonInteractedWith, RenderWindow& window)
{
	if (buttonInteractedWith == "Play") 
	{
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
	}

	else if (buttonInteractedWith == "Home") 
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}