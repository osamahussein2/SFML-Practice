#include "ZombieShooter.h"
#include "Zombie.h"

Zombie* createHorde(int numZombies, IntRect arena)
{
	/* Declare a pointer to the Zombie type called zombies and initialize it with the memory address of the first element of
	an array, which we dynamically allocate on the heap */
	Zombie* zombies = new Zombie[numZombies];

	int maxY = arena.size.y - 20;
	int minY = arena.position.y + 20;

	int maxX = arena.size.x - 20;
	int minX = arena.position.x + 20;

	for (int i = 0; i < numZombies; i++)
	{
		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);

		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		// Bloater, crawler or runner
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);

		// Spawn the new zombie into the array
		zombies[i].spawn(x, y, type, i);

	}
	return zombies;
}