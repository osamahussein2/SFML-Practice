#pragma once
#include "InputHandler.h"

class GameOverInputHandler : public InputHandler
{
public:
	void handleKeyPressed(std::optional<Event> event, RenderWindow& window) override;
	void handleLeftClick(std::string& buttonInteractedWith, RenderWindow& window) override;
};