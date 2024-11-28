#include "Game/Map/Map.hpp"

void Map::Tiles::setGridSize(const vec2& _size) {
	grid.resize(std::ceil(_size.y));
	for (auto& row : grid) {
		row.resize(std::ceil(_size.x));
	}
}

bool Map::Tiles::exist(int x, int y) {
	return y >= 0 && x >= 0 && y < grid.size() && x < grid[0].size() && grid[y][x].exist;
}

bool Map::Tiles::intersect(const vec2& point) {
	ivec2 index = ivec2((point - position) / size);
	if (index.y < 0 || index.x < 0 || index.y >= grid.size() || index.x >= grid[0].size()) {
		return false;
	}
	return grid[index.y][index.x].exist;
}

bool Map::Tiles::intersect(const AABB& aabb) {
	ivec2 lowerIndex = ivec2((aabb.lowerBound - position) / size);
	ivec2 upperIndex = ivec2((aabb.upperBound - position) / size);

	for (int i = std::min(lowerIndex.y, upperIndex.y); i <= std::max(lowerIndex.y, upperIndex.y); ++i) {
		for (int j = std::min(lowerIndex.x, upperIndex.x); j <= std::max(lowerIndex.x, upperIndex.x); ++j) {
			if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) {
				continue;
			}
			if (grid[i][j].exist) {
				return true;
			}
		}
	}
	return false;
}

bool Map::Tiles::intersect(const vec2& point, const vec2& _size) {
	ivec2 lowerIndex = ivec2((point - position) / size);
	ivec2 upperIndex = ivec2((point + _size - position) / size);

	for (int i = std::min(lowerIndex.y, upperIndex.y); i <= std::max(lowerIndex.y, upperIndex.y); ++i) {
		for (int j = std::min(lowerIndex.x, upperIndex.x); j <= std::max(lowerIndex.x, upperIndex.x); ++j) {
			if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) {
				continue;
			}

			if (grid[i][j].exist) {
				return true;
			}
		}
	}
	return false;
}

std::vector<Map::Tile>& Map::Tiles::operator[](int index) {
	return grid[index];
}

const std::vector<Map::Tile>& Map::Tiles::operator[](int index) const {
	return grid[index];
}
