#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "WorldState.h"

int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;

GameScreen::GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res) : m_BackgroundSprite(m_BackgroundTexture)
{
	m_GIH = make_shared<GameInputHandler>();
	auto guip = make_unique<GameUIPanel>(res);
	addPanel(move(guip), smrc, m_GIH);

	auto m_GOIH = make_shared<GameOverInputHandler>();
	auto gouip = make_unique<GameOverUIPanel>(res);
	addPanel(move(gouip), smrc, m_GOIH);

	m_ScreenManagerRemoteControl = smrc;
	float screenRatio = VideoMode::getDesktopMode().size.x / VideoMode::getDesktopMode().size.y;

	WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH / screenRatio;

	m_View.setSize(Vector2f(WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT));
	m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH / 2, WorldState::WORLD_HEIGHT / 2));

	m_BackgroundTexture.loadFromFile("graphics/background (3).png");

	m_BackgroundSprite = Sprite(m_BackgroundTexture);
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	auto textureSize = m_BackgroundSprite.getTexture().getSize();
	m_BackgroundSprite.setScale(Vector2f(m_View.getSize().x / textureSize.x, m_View.getSize().y / textureSize.y));
}

void GameScreen::initialise()
{
	m_GIH->initialize();

	WorldState::NUM_INVADERS = 0;
	m_GameOver = false;

	if (WorldState::WAVE_NUMBER == 0)
	{
		WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;

		WorldState::WAVE_NUMBER = 1;
		WorldState::LIVES = 3;
		WorldState::SCORE = 0;
	}
}

void GameScreen::update(float fps)
{
	Screen::update(fps);
	if (!m_GameOver)
	{
		if (WorldState::NUM_INVADERS <= 0)
		{
			WorldState::WAVE_NUMBER++;
			m_ScreenManagerRemoteControl->loadLevelInPlayMode("level1");
		}
		if (WorldState::LIVES <= 0)
		{
			m_GameOver = true;
		}
	}
}

void GameScreen::draw(RenderWindow& window)
{
	// Change to this screen's view to draw
	window.setView(m_View);
	window.draw(m_BackgroundSprite);

	// Draw the UIPanel view(s)
	Screen::draw(window);
}