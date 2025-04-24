#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
public:
	TextureHolder();

	/* This means that GetTexture will return a reference, which is efficient because it avoids making a copy of what could
	be a large graphic */
	static Texture& GetTexture(string const& filename);

private:
	// A map container from the STL, that holds related pairs of String and Texture
	map<string, Texture> m_Textures;

	// A pointer of the same type as the class itself the one and only instance
	static TextureHolder* m_s_Instance;
};
#endif