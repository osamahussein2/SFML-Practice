#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"
void GameInputHandler::initialize() 
{
}

void GameInputHandler::handleGamepad()
{
}

void GameInputHandler::handleKeyPressed(std::optional<Event> event, RenderWindow& window)
{
	// Handle key presses
	if (event->is<Event::KeyPressed>() == Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
	}
}

void GameInputHandler::handleKeyReleased(std::optional<Event> event, RenderWindow& window)
{
}

