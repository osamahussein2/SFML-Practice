#include "Engine.h"

Engine::Engine() : m_BackgroundSprite(m_BackgroundTexture)
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().size.x;
	resolution.y = VideoMode::getDesktopMode().size.y;

	m_Window.create(VideoMode(Vector2u(resolution.x, resolution.y)), "Thomas was late", State::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView = View(FloatRect(Vector2f(0, 0), Vector2f(resolution.x, resolution.y)));

	// Initialize the split-screen Views
	m_LeftView.setViewport(FloatRect(Vector2f(0.001f, 0.001f), Vector2f(0.498f, 0.998f)));
	m_RightView.setViewport(FloatRect(Vector2f(0.5f, 0.001f), Vector2f(0.499f, 0.998f)));
	m_BGLeftView.setViewport(FloatRect(Vector2f(0.001f, 0.001f), Vector2f(0.498f, 0.998f)));
	m_BGRightView.setViewport(FloatRect(Vector2f(0.5f, 0.001f), Vector2f(0.499f, 0.998f)));

	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background (2).png");
	
	m_BackgroundSprite = Sprite(m_BackgroundTexture);

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");
}

void Engine::run()
{
	// Timing
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Update the total game time
		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Call each part of the game loop in turn
		input();
		update(dtAsSeconds);
		draw();
	}
}