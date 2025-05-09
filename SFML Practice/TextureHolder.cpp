#include "TextureHolder.h"

// Include the "assert feature"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	/* In the constructor, assert(m_s_Instance == nullptr) ensures that m_s_Instance equals nullptr. If it doesn't the game
	will exit execution. Then, m_s_Instance = this assigns the pointer to this instance. Now, consider where this code is
	taking place. The code is in the constructor. The constructor is the way that we create instances of objects from classes.
	So, effectively, we now have a pointer to a TextureHolder that points to the one and only instance of itself */
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename)
{
	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;
	// auto is the equivalent of map<string, Texture>

	// Create an iterator to hold a key-value-pair (kvp)
	// and search for the required kvp
	// using the passed in file name
	auto keyValuePair = m.find(filename);

	// auto is equivalent of map<string, Texture>::iterator

	// Did we find a match?
	if (keyValuePair != m.end())
	{
		// Yes
		// Return the texture,
		// the second part of the kvp, the texture
		return keyValuePair->second;
	}

	else
	{
		// File name not found
		// Create a new key value pair using the filename
		auto& texture = m[filename];

		// Load the texture from file in the usual way
		texture.loadFromFile(filename);

		// Return the texture to the calling code
		return texture;
	}
}