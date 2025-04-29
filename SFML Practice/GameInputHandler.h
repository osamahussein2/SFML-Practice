#pragma once
#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameScreen;

class GameInputHandler : public InputHandler
{
private:
	shared_ptr<PlayerUpdateComponent> m_PUC;
	shared_ptr<TransformComponent> m_PTC;

	bool mBButtonPressed = false;

public:

	void initialize();
	void handleGamepad() override;
	void handleKeyPressed(std::optional<Event> event, RenderWindow& window) override;
	void handleKeyReleased(std::optional<Event> event, RenderWindow& window) override;
};