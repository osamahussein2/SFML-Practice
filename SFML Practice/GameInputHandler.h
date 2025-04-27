#pragma once
#include "InputHandler.h"

class GameScreen;

class GameInputHandler : public InputHandler
{
public:
	void initialize();
	void handleGamepad() override;
	void handleKeyPressed(std::optional<Event> event, RenderWindow& window) override;

	void handleKeyReleased(std::optional<Event> event, RenderWindow& window) override;
};