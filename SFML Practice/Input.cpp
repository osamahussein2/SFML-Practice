#include "Engine.h"

void Engine::input()
{
	//Event event;

	while (const std::optional event = m_Window.pollEvent())
	{
		if (event->is<Event::KeyPressed>())
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				m_Window.close();
			}

			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				m_Playing = true;
			}

			// Switch between Thomas and Bob
			if (Keyboard::isKeyPressed(Keyboard::Key::Q))
			{
				m_Character1 = !m_Character1;
			}

			// Switch between full and split-screen
			if (Keyboard::isKeyPressed(Keyboard::Key::E))
			{
				m_SplitScreen = !m_SplitScreen;
			}
		}
	}

	// Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
	}

	// Handle input specific to Bob
	if (m_Bob.handleInput())
	{
		// Play a jump sound
	}
}