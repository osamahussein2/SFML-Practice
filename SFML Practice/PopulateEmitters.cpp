#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel)
{
	// Make sure the vector is empty
	vSoundEmitters.empty();

	// Keep track of the previous emitter
	// so we don't make too many
	FloatRect previousEmitter;

	// Search for fire in the level
	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++)
	{
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++)
		{
			/* The code sets up a nested for loop that loops through arrayLevel, looking for fire tiles. When it finds one,
			it makes sure that it does not intersect with previousEmitter */

			if (arrayLevel[y][x] == 2) // fire is present
			{
				// Skip over any fire tiles too
				// near a previous emitter
				if (!FloatRect(Vector2f(x * TILE_SIZE, y * TILE_SIZE),
					Vector2f(TILE_SIZE, TILE_SIZE)).findIntersection(previousEmitter))
				{
					// Add the coordinates of this water block
					vSoundEmitters.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					// Update previousEmitter to avoid getting large clusters of sound emitters

					// Make a rectangle 6 blocks x 6 blocks, so we don't make any more emitters too close to this one
					previousEmitter.position.x = x * TILE_SIZE;
					previousEmitter.position.y = y * TILE_SIZE;
					previousEmitter.size.x = TILE_SIZE * 6;
					previousEmitter.size.y = TILE_SIZE * 6;
				}
			}
		}
	}
	return;
}