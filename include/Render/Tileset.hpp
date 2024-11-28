#pragma once
#include <vector>
#include <string>

#include "Render/Texture.hpp"

class Tileset {
public:
	Tileset(const std::string& filename, const vec2& tilesize);
	Tileset(const std::string& filename, float tilewidth, float tileheight);
	~Tileset() = default;

	std::vector<Texture>& operator[](int index);
private:
	vec2 m_tilesize;
	Texture m_tileset;
	std::vector<std::vector<Texture>> m_tiles;

	void setupTiles();
};