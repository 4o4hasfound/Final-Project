#include "Game/Map/GrassMap.hpp"

GrassMap::GrassMap(const vec2& size) {
	m_waterTiles.size = vec2(100);
	m_waterTiles.setGridSize(size / m_waterTiles.size + vec2(10));
	m_landTiles.size = vec2(100);
	m_landTiles.setGridSize(size / m_landTiles.size + vec2(10));
	m_flowerTiles.size = vec2(75);
	m_flowerTiles.setGridSize(size / m_flowerTiles.size + vec2(10));
	m_treeTiles.size = vec2(75);
	m_treeTiles.setGridSize(size / m_treeTiles.size + vec2(10));
}

void GrassMap::update(ViewPort& position) {
	generateWaterLand(position.position);
	generateFlower(position.position);
	generateTree(position.position);
}

void GrassMap::draw(RenderWindow& window) {
	drawWaterLand(window);
	drawFlower(window);
	drawTree(window);
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

			Noise::octaves = 12;
			Noise::lacunarity = 2;
			Noise::persistence = 0.5;
			float threshold = (Noise::get(pos) + 1) * 0.5;
			Noise::lacunarity = 2;
			Noise::octaves = 4;

			if (threshold < m_waterThreshold) {
				tile.exist = true;
				tile.texture = &m_water;
				tileLand.exist = false;
			}
			else {
				int landIndex = std::max(2, static_cast<int>(Noise::getUniform(pos * 3)));
				tile.exist = false;
				tileLand.exist = true;
				tileLand.texture = &m_earth[6][landIndex];
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
			Noise::lacunarity = 2.5;
			float threshold = (Noise::get(pos) + 1) * 0.5;
			Noise::lacunarity = 2;
			Noise::octaves = 4;
			tile.offset = vec2(Noise::get(pos)) * m_flowerTiles.size;

			if (threshold < m_flowerThreshold) {
				tile.exist = true;
				float value = std::max(0.0, Noise::getUniform(pos * 2) - 0.00001);
				std::vector<Texture>& flower = m_flowers[static_cast<int>(value * 5)];
				tile.texture = &flower[static_cast<int>(value * 20) % flower.size()];
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
			Noise::octaves = 4;
			tile.offset = vec2(Noise::get(pos)) * m_treeTiles.size;

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
				Texture* texture = getLandTexture(j, i);
				window.draw(rect, texture);
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
	Rectangle rect({150, 150});

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

Texture* GrassMap::getLandTexture(int x, int y) {
	bool right = m_landTiles.exist(x + 1, y);
	bool left = m_landTiles.exist(x - 1, y);
	bool up = m_landTiles.exist(x, y - 1);
	bool down = m_landTiles.exist(x, y + 1);

	bool rightup = m_landTiles.exist(x + 1, y - 1);
	bool rightdown = m_landTiles.exist(x + 1, y + 1);
	bool leftup = m_landTiles.exist(x - 1, y - 1);
	bool leftdown = m_landTiles.exist(x - 1, y + 1);
	if (right && left && up && down) {
		return &m_earth[12][6];
	}
	else if (right && !left && up && down) {
		return &m_earth[12][5];
	}
	else if (right && left && !up && down) {
		return &m_earth[12][4];
	}
	else if (!right && left && up && down) {
		return &m_earth[12][3];
	}
	else if (right && left && up && !down) {
		return &m_earth[12][2];
	}
	else if (left && down && rightup) {
		return &m_earth[12][1];
	}
	else if (left && down) {
		return &m_earth[12][0];
	}
	else if (right && down && leftup) {
		return &m_earth[11][7];
	}
	else if (right && down && !leftup) {
		return &m_earth[11][6];
	}
	else if (right && up && leftdown) {
		return &m_earth[11][5];
	}
	else if (right && up) {
		return &m_earth[11][4];
	}
	else if (left && up && rightdown) {
		return &m_earth[11][3];
	}
	else if (left && up && !rightdown) {
		return &m_earth[11][2];
	}
	else if (up && down) {
		return &m_earth[11][1];
	}
	else if (left && right) {
		return &m_earth[11][0];
	}
	else if (down && leftup && rightup) {
		return &m_earth[10][7];
	}
	else if (down && rightup) {
		return &m_earth[10][6];
	}
	else if (down && leftup) {
		return &m_earth[10][5];
	}
	else if (down) {
		return &m_earth[10][4];
	}
	else if (right && leftup && leftdown) {
		return &m_earth[10][3];
	}
	else if (right && leftup) {
		return &m_earth[10][2];
	}
	else if (right && leftdown) {
		return &m_earth[10][1];
	}
	else if (right) {
		return &m_earth[10][0];
	}
	else if (up && leftdown && rightdown) {
		return &m_earth[9][7];
	}
	else if (up && leftdown) {
		return &m_earth[9][6];
	}
	else if (up && rightdown) {
		return &m_earth[9][5];
	}
	else if (up) {
		return &m_earth[9][4];
	}
	else if (left && rightup && rightdown) {
		return &m_earth[9][3];
	}
	else if (left && rightdown) {
		return &m_earth[9][2];
	}
	else if (left && rightup) {
		return &m_earth[9][1];
	}
	else if (left) {
		return &m_earth[9][0];
	}
	else if (leftup && rightup && leftdown && rightdown) {
		return &m_earth[8][7];
	}
	else if (rightup && leftdown && rightdown) {
		return &m_earth[8][6];
	}
	else if (leftup && leftdown && rightdown) {
		return &m_earth[8][5];
	}
	else if (leftdown && rightdown) {
		return &m_earth[8][4];
	}
	else if (leftup && rightup && leftdown) {
		return &m_earth[8][3];
	}
	else if (rightup && leftdown) {
		return &m_earth[8][2];
	}
	else if (leftup && leftdown) {
		return &m_earth[8][1];
	}
	else if (leftdown) {
		return &m_earth[8][0];
	}
	else if (leftup && rightup && rightdown) {
		return &m_earth[7][7];
	}
	else if (rightup && rightdown) {
		return &m_earth[7][6];
	}
	else if (leftup && rightdown) {
		return &m_earth[7][5];
	}
	else if (rightdown) {
		return &m_earth[7][4];
	}
	else if (leftup && rightup) {
		return &m_earth[7][3];
	}
	else if (rightup) {
		return &m_earth[7][2];
	}
	else if (leftup) {
		return &m_earth[7][1];
	}
	return &m_earth[13][0];
}
