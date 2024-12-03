#pragma once

#include <vector>
#include <cmath>

#include "Debug/Log.hpp"

#include "Math/Vector.hpp"

#include "Physics/AABB.hpp"
#include "Physics/BoundingCircle.hpp"
#include "Physics/BoundingLine.hpp"
#include "Physics/RigidBody.hpp"

#include "Render/Shape.hpp"
#include "Render/RenderWindow.hpp"
#include "Render/Texture.hpp"

#include "Utils/Noise.hpp"

class Map {
public:
	Map() = default;
	virtual ~Map() = default;

	// Update the map, recalculate the whole map
	virtual void update(const ViewPort& viewport) = 0;
	
	// Render the map onto the screen
	virtual void draw(RenderWindow& window) = 0;

	// Resolve the collision for the body
	virtual void resolveCollision(RigidBody* body) = 0;

	// Returns if the aabb intersect with the map
	virtual bool intersect(const vec2& pos, const vec2& size) = 0;
	virtual bool intersect(const AABB& aabb) = 0;
	virtual bool intersect(const BoundingCircle& circle) = 0;
	virtual bool intersect(const BoundingLine& line) = 0;
	virtual bool intersect(const BoundingLine& line, RenderWindow& window) = 0;
protected:
	// Represents a single tile on the map
	struct Tile {
		bool exist = 0;
		float rotation = 0.0;
		Texture* texture = nullptr;
		vec2 offset = vec2(0);
	};
	// Represents a grid of tiles
	struct Tiles {
		vec2 position;
		vec2 size;
		std::vector<std::vector<Tile>> grid;

		// Resizes the grid to the specified size
		void setGridSize(const vec2& _size);

		// Checks if a tile exists at the specified grid coordinates
		bool exist(int x, int y);

		// Checks if a point/aabb intersects with any existing tiles
		bool intersect(const vec2& point);
		bool intersect(const AABB& aabb);
		bool intersect(const vec2& point, const vec2& size);

		std::vector<Tile>& operator[](int index);
		const std::vector<Tile>& operator[](int index) const;
	};
};