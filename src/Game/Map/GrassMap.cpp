#include "Game/Map/GrassMap.hpp"

GrassMap::GrassMap(const vec2& size) {
	m_waterTiles.size = vec2(100);
	m_waterTiles.setGridSize(size / m_waterTiles.size + vec2(10));
	m_landTiles.size = vec2(100);
	m_landTiles.setGridSize(size / m_landTiles.size + vec2(10));
	m_flowerTiles.size = vec2(75);
	m_flowerTiles.setGridSize(size / m_flowerTiles.size + vec2(10));
	m_treeTiles.size = vec2(200);
	m_treeTiles.setGridSize(size / m_treeTiles.size + vec2(10));
}

void GrassMap::update(ViewPort& position) {
	generateWaterLand(position.position);
	generateFlower(position.position);
	generateTree(position.position);
}

void GrassMap::draw(RenderWindow& window) {
	drawWaterLand(window);
	drawTree(window);
	drawFlower(window);
}

bool GrassMap::intersect() {

	return false;
}

void GrassMap::generateWaterLand(const vec2& position) {
	m_waterTiles.position = position - m_waterTiles.size * 5;
	m_waterTiles.position /= m_waterTiles.size;
	m_waterTiles.position = vec2(
		std::floor(m_waterTiles.position.x),
		std::floor(m_waterTiles.position.y)
	) * m_waterTiles.size;
	m_landTiles.position = m_waterTiles.position;
	for (int i = 0; i < m_waterTiles.grid.size(); ++i) {
		for (int j = 0; j < m_waterTiles[0].size(); ++j) {
			Tile& tile = m_waterTiles[i][j];
			Tile& tileLand = m_landTiles[i][j];
			vec2 pos = vec2(j, i) * m_waterTiles.size + m_waterTiles.position;
			pos /= m_waterTiles.size;
			pos = vec2(
				std::floor(pos.x),
				std::floor(pos.y)
			) * m_waterTiles.size;

			Noise::octaves = 8;
			float threshold = (Noise::get(pos) + 1) * 0.5;
			Noise::octaves = 4;
			tile.rotation = tileLand.rotation = static_cast<int>(Noise::getUniform(pos * 2) * 4) * 0.5 * PI;

			if (threshold < m_waterThreshold) {
				tile.exist = true;
				tileLand.exist = false;
				tile.texture = &m_water;
			}
			else {
				tile.exist = false;
				tileLand.exist = true;
				tileLand.texture = &m_land;
			}
		}
	}
}

void GrassMap::generateFlower(const vec2& position) {
	m_flowerTiles.position = position - m_flowerTiles.size * 5;
	m_flowerTiles.position /= m_flowerTiles.size;
	m_flowerTiles.position = vec2(
		std::floor(m_flowerTiles.position.x),
		std::floor(m_flowerTiles.position.y)
	) * m_flowerTiles.size;

	for (int i = 0; i < m_flowerTiles.grid.size(); ++i) {
		for (int j = 0; j < m_flowerTiles[0].size(); ++j) {
			Tile& tile = m_flowerTiles[i][j];
			vec2 pos = vec2(j, i) * m_flowerTiles.size + m_flowerTiles.position;
			pos /= m_flowerTiles.size;
			pos = vec2(
				std::floor(pos.x),
				std::floor(pos.y)
			) * m_flowerTiles.size;

			Noise::octaves = 12;
			Noise::lacunarity = 2.3;
			float threshold = (Noise::get(pos) + 1) * 0.5;
			Noise::lacunarity = 2;
			//tile.rotation = static_cast<int>(Noise::getUniform(pos * 2) * 4) * 0.5 * PI;
			Noise::octaves = 4;
			tile.offset = vec2(Noise::get(pos)) * m_flowerTiles.size;

			if (threshold < m_flowerThreshold) {
				tile.exist = true;
				tile.texture = &m_flower;
			}
			else {
				tile.exist = false;
			}
		}
	}
}

void GrassMap::generateTree(const vec2& position) {
	m_treeTiles.position = position - m_treeTiles.size * 5;
	m_treeTiles.position /= m_treeTiles.size;
	m_treeTiles.position = vec2(
		std::floor(m_treeTiles.position.x),
		std::floor(m_treeTiles.position.y)
	) * m_treeTiles.size;

	for (int i = 0; i < m_treeTiles.grid.size(); ++i) {
		for (int j = 0; j < m_treeTiles[0].size(); ++j) {
			Tile& tile = m_treeTiles[i][j];
			vec2 pos = vec2(j, i) * m_treeTiles.size + m_treeTiles.position;
			pos /= m_treeTiles.size;
			pos = vec2(
				std::floor(pos.x),
				std::floor(pos.y)
			) * m_treeTiles.size;

			Noise::octaves = 10;
			Noise::lacunarity = 2.2;
			float threshold = (Noise::get(pos) + 1) * 0.5;
			Noise::lacunarity = 2;
			//tile.rotation = static_cast<int>(Noise::getUniform(pos * 2) * 4) * 0.5 * PI;
			//Noise::octaves = 4;
			//tile.offset = vec2(Noise::get(pos)) * m_treeTiles.size;

			if (threshold < m_treeThreshold) {
				tile.exist = true;
				tile.texture = &m_tree;
			}
			else {
				tile.exist = false;
			}
		}
	}
}

void GrassMap::drawWaterLand(RenderWindow& window) {
	Rectangle rect(m_waterTiles.size + 1);

	for (int i = 0; i < m_waterTiles.grid.size(); ++i) {
		for (int j = 0; j < m_waterTiles[0].size(); ++j) {
			rect.position = vec2(j, i) * m_waterTiles.size + m_waterTiles.position + m_waterTiles.size * 0.5;
			rect.rotation = m_waterTiles[i][j].rotation;
			if (m_waterTiles[i][j].exist) {
				window.draw(rect, m_waterTiles[i][j].texture);
			}
			else {
				window.draw(rect, m_landTiles[i][j].texture);
			}
		}
	}
}

void GrassMap::drawFlower(RenderWindow& window) {
	Rectangle rect(m_flowerTiles.size);

	for (int i = 0; i < m_flowerTiles.grid.size(); ++i) {
		for (int j = 0; j < m_flowerTiles[0].size(); ++j) {
			Tile& tile = m_flowerTiles[i][j];
			if (!tile.exist) {
				continue;
			}
			const vec2 pos = vec2(j, i) * m_flowerTiles.size + m_flowerTiles.position + tile.offset;
			rect.position = pos + rect.size * 0.5;
			if (m_waterTiles.intersect(pos, rect.size) || m_treeTiles.intersect(pos, rect.size)) {
				continue;
			}
			rect.rotation = tile.rotation;
			window.draw(rect, tile.texture);
		}
	}
}

void GrassMap::drawTree(RenderWindow& window) {
	Rectangle rect(m_treeTiles.size);

	for (int i = 0; i < m_treeTiles.grid.size(); ++i) {
		for (int j = 0; j < m_treeTiles[0].size(); ++j) {
			Tile& tile = m_treeTiles[i][j];
			if (!tile.exist) {
				continue;
			}
			const vec2 pos = vec2(j, i) * m_treeTiles.size + m_treeTiles.position + tile.offset;
			rect.position = pos + rect.size * 0.5;
			if (m_waterTiles.intersect(pos, rect.size)) {
				continue;
			}
			rect.rotation = tile.rotation;
			window.draw(rect, tile.texture);
		}
	}
}