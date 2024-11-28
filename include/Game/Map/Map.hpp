#pragma once

#include <vector>
#include <cmath>

#include "Debug/Log.hpp"

#include "Math/Vector.hpp"

#include "Physics/AABB.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"
#include "Render/Texture.hpp"

#include "Utils/Noise.hpp"

class Map {
public:
	Map() = default;
	virtual ~Map() = default;

	virtual void update(ViewPort& position) = 0;
	virtual void draw(RenderWindow& window) = 0;

	virtual bool intersect() = 0;
protected:
	struct Tile {
		bool exist = 0;
		float rotation = 0.0;
		Texture* texture = nullptr;
		vec2 offset = vec2(0);
	};
	struct Tiles {
		vec2 position;
		vec2 size;
		std::vector<std::vector<Tile>> grid;

		void setGridSize(const vec2& _size);

		bool exist(int x, int y);

		bool intersect(const vec2& point);
		bool intersect(const AABB& aabb);
		bool intersect(const vec2& point, const vec2& size);

		std::vector<Tile>& operator[](int index);
		const std::vector<Tile>& operator[](int index) const;
	};
};