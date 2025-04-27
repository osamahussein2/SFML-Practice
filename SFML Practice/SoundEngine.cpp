#include <SFML/Audio.hpp>
#include <assert.h>
#include "SoundEngine.h"

using namespace std;
using namespace sf;

SoundEngine* SoundEngine::m_s_Instance = nullptr;

SoundEngine::SoundEngine() : m_ShootSound(m_ShootBuffer), m_PlayerExplodeSound(m_PlayerExplodeBuffer), 
m_InvaderExplodeSound(m_InvaderExplodeBuffer), m_ClickSound(m_ClickBuffer), m_UhSound(m_ShootBuffer), 
m_OhSound(m_ShootBuffer)
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;

	// Load the sound into the buffers
	m_ShootBuffer.loadFromFile("sounds/shoot.ogg");
	m_PlayerExplodeBuffer.loadFromFile("sounds/playerexplode.ogg");
	m_InvaderExplodeBuffer.loadFromFile("sounds/invaderexplode.ogg");
	m_ClickBuffer.loadFromFile("sounds/click.ogg");

	// Associate the sounds with the buffers
	m_ShootSound.setBuffer(m_ShootBuffer);
	m_PlayerExplodeSound.setBuffer(m_PlayerExplodeBuffer);
	m_InvaderExplodeSound.setBuffer(m_InvaderExplodeBuffer);
	m_ClickSound.setBuffer(m_ClickBuffer);
}
void SoundEngine::playShoot()
{
	m_s_Instance->m_ShootSound.play();
}

void SoundEngine::playPlayerExplode()
{
	m_s_Instance->m_PlayerExplodeSound.play();
}

void SoundEngine::playInvaderExplode()
{
	m_s_Instance->m_InvaderExplodeSound.play();
}

void SoundEngine::playClick()
{
	m_s_Instance->m_ClickSound.play();
}