#include "Tileset.hpp"

Tileset::Tileset(const std::string& filename, const vec2& tilesize)
	: m_tileset(filename), m_tilesize(tilesize) {
	setupTiles();
}

Tileset::Tileset(const std::string& filename, float tilewidth, float tileheight)
	: m_tileset(filename), m_tilesize(tilewidth, tileheight) {
	setupTiles();
}

std::vector<Texture>& Tileset::operator[](int index) {
	return m_tiles[index];
}

void Tileset::setupTiles() {
	const ivec2 totalSize = ivec2(m_tileset.size() / m_tilesize);
	m_tiles.resize(totalSize.y);
	for (int i = 0; i < totalSize.y; ++i) {
		m_tiles[i].reserve(totalSize.x);
		for (int j = 0; j < totalSize.x; ++j) {
			m_tiles[i].emplace_back(al_create_sub_bitmap(
				m_tileset.getBitmap(),
				j * m_tilesize.x,
				i * m_tilesize.y,
				m_tilesize.x,
				m_tilesize.y
			));
		}
	}
}
