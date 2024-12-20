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
		bool exist(int x, int y) const;

		// Checks if a point/aabb intersects with any existing tiles
		bool intersect(const vec2& point) const;
		bool intersect(const AABB& aabb) const;
		bool intersect(const vec2& point, const vec2& size) const;

		std::vector<Tile>& operator[](int index);
		const std::vector<Tile>& operator[](int index) const;
	};
public:
	Map() = default;
	virtual ~Map() = default;

	// Update the map, recalculate the whole map
	virtual void update(const ViewPort& viewport) = 0;
	
	// Render the map onto the screen
	virtual void draw(RenderWindow& window) = 0;

	// Render the aabb
	virtual void drawAABB(RenderWindow& window, RigidBody* body) = 0;

	// Resolve the collision for the body
	virtual void resolveCollision(RigidBody* body) = 0;

	virtual const Tiles* getCollisionTiles() const;

	// Returns if the aabb intersect with the map
	virtual bool intersect(const vec2& pos, const vec2& size) const = 0;
	virtual bool intersect(const AABB& aabb) const = 0;
	virtual bool intersect(const BoundingCircle& circle) const = 0;
	virtual bool intersect(const BoundingLine& line) const = 0;
	virtual bool intersect(const BoundingLine& line, RenderWindow& window) const = 0;
protected:
};