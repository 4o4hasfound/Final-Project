#include "Game/Map/GrassMap.hpp"

GrassMap::GrassMap(const vec2& size) {
	m_waterTiles.size = vec2(100);
	m_waterTiles.setGridSize(size * 2 / m_waterTiles.size);
	m_landTiles.size = vec2(100);
	m_landTiles.setGridSize(size * 2 / m_landTiles.size);
	m_flowerTiles.size = vec2(75);
	m_flowerTiles.setGridSize(size * 1.5 / m_flowerTiles.size);
	m_treeTiles.size = vec2(75);
	m_treeTiles.setGridSize(size * 1.5 / m_treeTiles.size);
}

void GrassMap::update(const ViewPort& viewport) {
	generateWaterLand(viewport);
	generateFlower(viewport);
	generateTree(viewport);
}

void GrassMap::draw(RenderWindow& window) {
	drawWaterLand(window);
	drawFlower(window);
	drawTree(window);
}

void GrassMap::resolveCollision(RigidBody* body) {
	Tiles& tiles = m_waterTiles;

	ivec2 lowerIndex = max(ivec2(
		(body->getAABB().lowerBound - tiles.position) / tiles.size - 1
	), ivec2(0));
	ivec2 upperIndex = min(ivec2(
		(body->getAABB().upperBound - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size()-1, m_waterTiles.grid.size()-1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
				if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& aabb : aabbs) {
				body->resolveCollision(aabb + position);
			}
		}
	}
}

void GrassMap::resolveCollision(RigidBody* body, RenderWindow& window) {
	Tiles& tiles = m_waterTiles;
	ivec2 lowerIndex = max(ivec2(
		(body->getAABB().lowerBound - tiles.position) / tiles.size - 1
	), 0);
	ivec2 upperIndex = min(ivec2(
		(body->getAABB().upperBound - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size() - 1, m_waterTiles.grid.size() - 1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
			if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& aabb : aabbs) {
				body->resolveCollision(aabb + position);
				//(aabb + position).DebugDraw(window);
			}
			//AABB aabb{
			//	position,
			//	position + tiles.size
			//};
		}
	}
}

bool GrassMap::intersect(const vec2& pos, const vec2& size) {
	AABB aabb{ pos - size * 0.5, pos + size * 0.5 };
	return intersect(aabb);
}

bool GrassMap::intersect(const AABB& aabb) {
	Tiles& tiles = m_waterTiles;

	ivec2 lowerIndex = max(ivec2(
		(aabb.lowerBound - tiles.position) / tiles.size - 1
	), ivec2(0));
	ivec2 upperIndex = min(ivec2(
		(aabb.upperBound - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size() - 1, m_waterTiles.grid.size() - 1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
			if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& _aabb : aabbs) {
				if (aabb.intersect(_aabb + position)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool GrassMap::intersect(const BoundingCircle& circle) {
	Tiles& tiles = m_waterTiles;

	ivec2 lowerIndex = max(ivec2(
		(circle.position - circle.radius - tiles.position) / tiles.size - 1
	), ivec2(0));
	ivec2 upperIndex = min(ivec2(
		(circle.position + circle.radius - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size() - 1, m_waterTiles.grid.size() - 1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
			if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& _aabb : aabbs) {
				if (circle.intersect(_aabb + position)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool GrassMap::intersect(const BoundingLine& line) {
	Tiles& tiles = m_waterTiles;
	const AABB aabb = AABB::FromTwoPoints(line.start, line.end);

	ivec2 lowerIndex = max(ivec2(
		(aabb.lowerBound - tiles.position) / tiles.size - 1
	), ivec2(0));
	ivec2 upperIndex = min(ivec2(
		(aabb.upperBound - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size() - 1, m_waterTiles.grid.size() - 1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
			if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& _aabb : aabbs) {
				if (line.intersect(_aabb + position)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool GrassMap::intersect(const BoundingLine& line, RenderWindow& window) {
	Tiles& tiles = m_waterTiles;
	const AABB aabb = AABB::FromTwoPoints(line.start, line.end);
	aabb.DebugDraw(window);
	ivec2 lowerIndex = max(ivec2(
		(aabb.lowerBound - tiles.position) / tiles.size - 1
	), ivec2(0));
	ivec2 upperIndex = min(ivec2(
		(aabb.upperBound - tiles.position) / tiles.size + 1
	), ivec2(m_waterTiles.grid[0].size() - 1, m_waterTiles.grid.size() - 1));
	for (int i = lowerIndex.y; i <= upperIndex.y; ++i) {
		for (int j = lowerIndex.x; j <= upperIndex.x; ++j) {
			if (!tiles[i][j].exist || existAdditionTrail(j, i)) {
				continue;
			}
			const vec2 position = vec2(j, i) * tiles.size + tiles.position;
			std::vector<AABB> aabbs = getWaterBoundingBox(j, i);
			for (auto& _aabb : aabbs) {
				(_aabb + position).DebugDraw(window);
				if (line.intersect(_aabb + position)) {
					return true;
				}
			}
		}
	}

	return false;
}
const Map::Tiles& GrassMap::getWaterTiles() const {
	return m_waterTiles;
}
void GrassMap::setTile(const vec2& point, bool exist) {
	ivec2 index = ivec2((point - m_waterTiles.position) / m_waterTiles.size);
	if (index.y < 0 || index.x < 0 || index.y >= m_waterTiles.grid.size() || index.x >= m_waterTiles.grid[0].size()) {
		return;
	}
	m_additionalTrail.insert(vec2(index) * m_waterTiles.size + m_waterTiles.position);
}

void GrassMap::generateWaterLand(const ViewPort& viewport) {
	m_waterTiles.position = viewport.position - viewport.size * 0.5;
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

			int landIndex = std::max(2, static_cast<int>(Noise::getUniform(pos * 3)));
			if (threshold < m_waterThreshold) {
				tile.exist = true;
				tile.texture = &m_water;
				tileLand.exist = false;
			}
			else {
				tile.exist = false;
				tileLand.exist = true;
			}
			tileLand.texture = &m_earth[6][landIndex];
		}
	}
}

void GrassMap::generateFlower(const ViewPort& viewport) {
	m_flowerTiles.position = viewport.position - viewport.size * 0.25;
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

void GrassMap::generateTree(const ViewPort& viewport) {
	m_treeTiles.position = viewport.position - viewport.size * 0.25;
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
			const vec2 position = vec2(j, i) * m_waterTiles.size + m_waterTiles.position;
			rect.position = position + m_waterTiles.size * 0.5;
			rect.rotation = m_waterTiles[i][j].rotation;
			rect.outlineColor = vec4(255);
			rect.outlineThickness = 5;
			//window.draw(rect);
			rect.outlineThickness = 0;
			if (!m_waterTiles[i][j].exist || m_additionalTrail.count(position)) {
				window.draw(rect, m_landTiles[i][j].texture);
			}
			else {
				rect.outlineThickness = 5;
				//window.draw(rect);
				rect.outlineThickness = 0;
				Texture* texture = getLandTexture(j, i);
				window.draw(rect, texture);
			}
			//if (m_waterTiles[i][j].exist) {
			//	rect.outlineThickness = 5;
			//	//window.draw(rect);
			//	rect.outlineThickness = 0;
			//	Texture* texture = getLandTexture(j, i);
			//	window.draw(rect, texture);
			//}
			//else {
			//	window.draw(rect, m_landTiles[i][j].texture);
			//}
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
			rect.outlineColor = vec4(255);
			rect.outlineThickness = 5;
			//window.draw(rect);
			rect.outlineThickness = 0;
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
	bool right = m_landTiles.exist(x + 1, y) || existAdditionTrail(x + 1, y);
	bool left = m_landTiles.exist(x - 1, y) || existAdditionTrail(x - 1, y);
	bool up = m_landTiles.exist(x, y - 1) || existAdditionTrail(x, y - 1);
	bool down = m_landTiles.exist(x, y + 1) || existAdditionTrail(x, y + 1);

	bool rightup = m_landTiles.exist(x + 1, y - 1) || existAdditionTrail(x + 1, y - 1);
	bool rightdown = m_landTiles.exist(x + 1, y + 1) || existAdditionTrail(x + 1, y + 1);
	bool leftup = m_landTiles.exist(x - 1, y - 1) || existAdditionTrail(x - 1, y - 1);
	bool leftdown = m_landTiles.exist(x - 1, y + 1) || existAdditionTrail(x - 1, y + 1);
	if (right && left && up && down) {
		return &m_earth[12][6];
	}
	else if (right && up && down) {
		return &m_earth[12][5];
	}
	else if (right && left && down) {
		return &m_earth[12][4];
	}
	else if (left && up && down) {
		return &m_earth[12][3];
	}
	else if (right && left && up) {
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

std::vector<AABB> GrassMap::getWaterBoundingBox(int x, int y) {
	bool right = m_landTiles.exist(x + 1, y) || existAdditionTrail(x + 1, y);
	bool left = m_landTiles.exist(x - 1, y) || existAdditionTrail(x - 1, y);
	bool up = m_landTiles.exist(x, y - 1) || existAdditionTrail(x, y - 1);
	bool down = m_landTiles.exist(x, y + 1) || existAdditionTrail(x, y + 1);

	bool rightup = m_landTiles.exist(x + 1, y - 1) || existAdditionTrail(x + 1, y - 1);
	bool rightdown = m_landTiles.exist(x + 1, y + 1) || existAdditionTrail(x + 1, y + 1);
	bool leftup = m_landTiles.exist(x - 1, y - 1) || existAdditionTrail(x - 1, y - 1);
	bool leftdown = m_landTiles.exist(x - 1, y + 1) || existAdditionTrail(x - 1, y + 1);

	const float offset = 18;
	const vec2& size = m_waterTiles.size;

	const AABB leftAABB = { {0, offset}, {offset, size.y - offset} };
	const AABB rightAABB = { {size.x - offset, offset}, {size.x, size.y - offset} };
	const AABB upAABB = { {offset, 0}, {size.x - offset, offset} };
	const AABB downAABB = { {offset, size.y - offset}, {size.x - offset, size.y} };
	const AABB leftupAABB = { {0, 0}, {offset, offset} };
	const AABB leftdownAABB = { {0, size.y - offset}, {offset, size.y} };
	const AABB rightupAABB = { {size.x - offset, 0}, {size.x, offset} };
	const AABB rightdownAABB = { {size.x - offset, size.y - offset}, {size.x, size.y} };
	const AABB middleAABB = { {offset, offset}, {size.x - offset, size.y - offset} };

	if (right && left && up && down) {
		return { middleAABB };
	}
	else if (right && !left && up && down) {
		return {middleAABB, leftAABB};
	}
	else if (right && left && !up && down) {
		return { middleAABB, upAABB };
	}
	else if (!right && left && up && down) {
		return { middleAABB, rightAABB };
	}
	else if (right && left && up && !down) {
		return { middleAABB, downAABB };
	}
	else if (left && down && rightup) {
		return { middleAABB, upAABB, rightAABB };
	}
	else if (left && down) {
		return { middleAABB, rightAABB, upAABB, rightupAABB };
	}
	else if (right && down && leftup) {
		return { middleAABB, leftAABB, upAABB};
	}
	else if (right && down && !leftup) {
		return { middleAABB, leftAABB, upAABB, leftupAABB };
	}
	else if (right && up && leftdown) {
		return { middleAABB, leftAABB, downAABB };
	}
	else if (right && up) {
		return { middleAABB, leftAABB, downAABB, leftdownAABB };
	}
	else if (left && up && rightdown) {
		return { middleAABB, rightAABB, downAABB };
	}
	else if (left && up && !rightdown) {
		return { middleAABB, rightAABB, downAABB, rightdownAABB };
	}
	else if (up && down) {
		return { middleAABB, leftAABB, rightAABB };
	}
	else if (left && right) {
		return { middleAABB, upAABB, downAABB };
	}
	else if (down && leftup && rightup) {
		return { middleAABB, leftAABB, rightAABB, upAABB };
	}
	else if (down && rightup) {
		return { middleAABB, leftAABB, rightAABB, upAABB, leftupAABB };
	}
	else if (down && leftup) {
		return { middleAABB, leftAABB, rightAABB, upAABB, rightupAABB };
	}
	else if (down) {
		return { middleAABB, leftAABB, rightAABB, upAABB, leftupAABB, rightupAABB };
	}
	else if (right && leftup && leftdown) {
		return { middleAABB, leftAABB, upAABB, downAABB };
	}
	else if (right && leftup) {
		return { middleAABB, leftAABB, upAABB, downAABB, leftdownAABB };
	}
	else if (right && leftdown) {
		return { middleAABB, leftAABB, upAABB, downAABB, leftupAABB };
	}
	else if (right) {
		return { middleAABB, leftAABB, upAABB, downAABB, leftupAABB, leftdownAABB };
	}
	else if (up && leftdown && rightdown) {
		return { middleAABB, leftAABB, rightAABB, downAABB };
	}
	else if (up && leftdown) {
		return { middleAABB, leftAABB, rightAABB, downAABB, rightdownAABB };
	}
	else if (up && rightdown) {
		return { middleAABB, leftAABB, rightAABB, downAABB, leftdownAABB };
	}
	else if (up) {
		return { middleAABB, leftAABB, rightAABB, downAABB, leftdownAABB, rightdownAABB };
	}
	else if (left && rightup && rightdown) {
		return { middleAABB, rightAABB, upAABB, downAABB };
	}
	else if (left && rightdown) {
		return { middleAABB, rightAABB, upAABB, downAABB, rightupAABB };
	}
	else if (left && rightup) {
		return { middleAABB, rightAABB, upAABB, downAABB, rightdownAABB };
	}
	else if (left) {
		return { middleAABB, rightAABB, upAABB, downAABB, rightupAABB, rightdownAABB };

	}
	else if (leftup && rightup && leftdown && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB };
	}
	else if (rightup && leftdown && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftupAABB };
	}
	else if (leftup && leftdown && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, rightupAABB };
	}
	else if (leftdown && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftupAABB, rightupAABB };
	}
	else if (leftup && rightup && leftdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, rightdownAABB };
	}
	else if (rightup && leftdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftupAABB, rightdownAABB };
	}
	else if (leftup && leftdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, rightupAABB, rightdownAABB };
	}
	else if (leftdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, rightupAABB, rightdownAABB, leftupAABB };
	}
	else if (leftup && rightup && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB };
	}
	else if (rightup && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftupAABB, leftdownAABB };
	}
	else if (leftup && rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB, rightupAABB };
	}
	else if (rightdown) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB, leftupAABB, rightupAABB };
	}
	else if (leftup && rightup) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB, rightdownAABB };
	}
	else if (rightup) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB, rightdownAABB, leftupAABB };
	}
	else if (leftup) {
		return { middleAABB, leftAABB, rightAABB, upAABB, downAABB, leftdownAABB, rightdownAABB, rightupAABB };
	}
	return { AABB{ {0, 0}, size } };
}

bool GrassMap::existAdditionTrail(int x, int y) {
	const vec2 position = m_waterTiles.position + vec2(x, y) * m_waterTiles.size;
	return m_additionalTrail.count(position);
}
