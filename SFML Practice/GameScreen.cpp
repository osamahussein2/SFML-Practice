#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "GameObject.h"
#include "WorldState.h"
#include "BulletUpdateComponent.h"
#include "InvaderUpdateComponent.h"

class BulletSpawner;

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
	m_PhysicsEnginePlayMode.initilize(m_ScreenManagerRemoteControl->shareGameObjectSharer());

	WorldState::NUM_INVADERS = 0;

	// Store all the bullet locations and initialize all the BulletSpawners in the invaders
	// Count the number of invaders
	int i = 0;
	
	auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
	auto end = m_ScreenManagerRemoteControl->getGameObjects().end();

	for (it; it != end; ++it)
	{
		/* The first if block tests whether the current game object is a bullet. If it is, then its integer location in the
		vector of game objects is stored in the m_BulletObjectLocations vector */
		if ((*it).getTag() == "bullet")
		{
			m_BulletObjectLocations.push_back(i);
		}

		/* The second if block detects whether the current game object is an invader and, if it is, calls the
		initializeBulletSpawner function on its update component and passes in a pointer to a BulletSpawner by calling the
		getBulletSpawner function. The invaders are now capable of spawning bullets */
		if ((*it).getTag() == "invader")
		{
			static_pointer_cast<InvaderUpdateComponent>((*it).getFirstUpdateComponent())->initializeBulletSpawner
			(getBulletSpawner(), i);

			WorldState::NUM_INVADERS++;
		}

		++i;
	}

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
		if (m_WaitingToSpawnBulletForPlayer)
		{
			static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->getGameObjects()
				[m_BulletObjectLocations[m_NextBullet]].getFirstUpdateComponent())->
				spawnForPlayer(m_PlayerBulletSpawnLocation);

			m_WaitingToSpawnBulletForPlayer = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size())
			{
				m_NextBullet = 0;
			}
		}

		if (m_WaitingToSpawnBulletForInvader)
		{
			static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->getGameObjects()
				[m_BulletObjectLocations[m_NextBullet]].getFirstUpdateComponent())->
				spawnForInvader(m_InvaderBulletSpawnLocation);

			m_WaitingToSpawnBulletForInvader = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size())
			{
				m_NextBullet = 0;
			}
		}

		auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
		auto end = m_ScreenManagerRemoteControl->getGameObjects().end();

		for (it; it != end; ++it)
		{
			(*it).update(fps);
		}

		m_PhysicsEnginePlayMode.detectCollisions(m_ScreenManagerRemoteControl->getGameObjects(), m_BulletObjectLocations);

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

	// Draw the GameObject instances
	auto it = m_ScreenManagerRemoteControl->getGameObjects().begin();
	auto end = m_ScreenManagerRemoteControl->getGameObjects().end();

	for (it; it != end; ++it)
	{
		(*it).draw(window);
	}

	// Draw the UIPanel view(s)
	Screen::draw(window);
}

BulletSpawner* GameScreen::getBulletSpawner()
{
	// This returns a pointer to GameScreen, which gives us access to the spawnBullet function
	return this;
}