#include "ZombieShooter.h"
#include <ctime>

int createBackground(VertexArray& rVA, IntRect arena)
{
	// Anything we do to rVA we are really doing to background (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 6;

	int worldWidth = arena.size.x / TILE_SIZE;
	int worldHeight = arena.size.y / TILE_SIZE;

	// What type of primitive are we using?
	rVA.setPrimitiveType(PrimitiveType::Triangles);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 4].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			rVA[currentVertex + 5].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			//rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			/* The condition checks whether the current quad is either one of the very first or the very last quads in the
			arena. If it is (one of the first or last), then this means it is part of the boundary */

			// Define the position in the Texture for current quad
			// // Either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 3].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 4].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 5].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}

			// Run through the nested for loop each time the quad does not represent a border / wall tile
			else
			{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);

				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);

				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);

				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

				rVA[currentVertex + 3].texCoords = Vector2f(0, 0 + verticalOffset);

				rVA[currentVertex + 4].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

				rVA[currentVertex + 5].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

				//rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}


			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;

		}
	}

	return TILE_SIZE;
}