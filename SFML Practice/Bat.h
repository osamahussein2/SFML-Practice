
/* #pragma once declaration at the top of the file prevents the file from being processed by the compiler more than once.
As our games get more complicated with perhaps dozens of classes, this will speed up compilation time */

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f m_Position;

	// A RectangleShape object
	RectangleShape m_Shape;
	float m_Speed = 1000.0f;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;

public:
	Bat(float startX, float startY);

	/* When we code a public function with the sole purpose of passing back private data from a class, we call it a
	getter function. */
	FloatRect getPosition();
	RectangleShape getShape();

	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	void update(Time dt);
};