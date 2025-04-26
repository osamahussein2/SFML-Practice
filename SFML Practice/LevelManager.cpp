#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	m_CurrentLevel++;

	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	// Load the appropriate level from a text file
	string levelToLoad;

	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;

	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;

	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	}

	// This will open a stream to the file name contained in levelToLoad
	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	/* Clear inputFile using its clear function. The seekg function, which is called with the 0, ios::beg parameters, moves
	the file cursor's position (where characters will be read from next) to the beginning of the file. */

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	/* Declare a pointer to a pointer called arrayLevel. Note that this is done on the free store/heap using the new keyword.
	Once we have initialized this twodimensional array, we will be able to return its address to the calling code and it will
	persist until we either delete it or the game is closed. */

	// Prepare the 2D array to hold the int values from the file
	int** arrayLevel = new int* [m_LevelSize.y];

	/* The for loop loops from 0 to m_LevelSize.y - 1. In each pass of the loop, it adds a new array of int values, on the
	heap, to match the value of m_LevelSize.x. */
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;

	// The while loop executes repeatedly until inputFile gets past the last row
	while (inputFile >> row)
	{
		/* Inside the while loop, there is a for loop which goes through each character of the current row and stores it in
		the two-dimensional array, arrayLevel. Notice that we access the right element of the two-dimensional array with
		arrayLevel[y][x]=. The atoi function converts the char val into an int. This is required because we have a 
		two-dimensional array for int, and not for char. */
		for (int x = 0; x < row.length(); x++) 
		{
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}

		y++;
	}

	// Close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(PrimitiveType::Triangles);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	/* The nested for loops loop from zero through to the width and height of the level. For each position in the array, six 
	vertices are put into the VertexArray and six texture coordinates are assigned from the sprite-sheet. */

	// Start at the beginning of the vertex array
	int currentVertex = 0;
	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			/* The positions of the vertices and texture coordinates are calculated using the currentVertex variable, TILE
			SIZE, and the VERTS_IN_QUAD constants. */

			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 4].position = Vector2f(x * TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 5].position = Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 4].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 5].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			/* At the end of each loop of the inner for loop, currentVertex is increased by VERTS_IN_QUAD, moving nicely on 
			to the next tile */

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
} // End of nextLevel function

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}

Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}