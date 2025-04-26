#include "Hud.h"

Hud::Hud() : m_StartText(m_Font), m_TimeText(m_Font), m_LevelText(m_Font)
{
	Vector2u resolution;

	resolution.x = VideoMode::getDesktopMode().size.x;
	resolution.y = VideoMode::getDesktopMode().size.y;

	// Load the font
	m_Font.openFromFile("fonts/Roboto-Light.ttf");// when Paused
	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(100);
	m_StartText.setFillColor(Color::White);
	m_StartText.setString("Press Enter when ready!");

	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f, 
		textRect.position.y + textRect.size.y / 2.0f));

	m_StartText.setPosition(Vector2f(resolution.x / 2.0f, resolution.y / 2.0f));

	// Time
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(75);
	m_TimeText.setFillColor(Color::White);
	m_TimeText.setPosition(Vector2f(resolution.x - 150, 0));
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(Vector2f(25, 0));
	m_LevelText.setString("1");
}

Text Hud::getMessage()
{
	return m_StartText;
}

Text Hud::getLevel()
{
	return m_LevelText;
}

Text Hud::getTime()
{
	return m_TimeText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setTime(String text)
{
	m_TimeText.setString(text);
}