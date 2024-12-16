#pragma once
#include <unordered_set>

#include "Game/Map/Map.hpp"

#include "Render/Animation.hpp"
#include "Render/Tileset.hpp"

class GrassMap : public Map {
	struct vec2_hash {
		std::size_t operator()(const vec2& v) const {
			return std::hash<float>{}(v.x) ^ std::hash<float>{}(v.y);
		}
	};
public:
	GrassMap(const vec2& size);
	virtual ~GrassMap() = default;

	virtual void update(const ViewPort& viewport) override;

	virtual void draw(RenderWindow& window) override;
	virtual void drawAABB(RenderWindow& window, RigidBody* body) override;

	virtual void resolveCollision(RigidBody* body) override;
	virtual void resolveCollision(RigidBody* body, RenderWindow& window);

	virtual bool intersect(const vec2& pos, const vec2& size) const override;
	virtual bool intersect(const AABB& aabb) const override;
	virtual bool intersect(const BoundingCircle& circle) const override;
	virtual bool intersect(const BoundingLine& line) const override;

	virtual bool intersect(const BoundingLine& line, RenderWindow& window) const override;

	virtual const Tiles* getCollisionTiles() const override;

	void setTile(const vec2& point, bool exist);
private:
	// Some value for procedural generation
	float m_waterThreshold = 0.45;
	float m_flowerThreshold = 0.35;
	float m_treeThreshold = 0.2;

	// Load textures and tileset
	Texture m_water = Texture("assets/Map/water.png");
	Texture m_land = Texture("assets/Map/grass.png");
	Texture m_flower = Texture("assets/Map/red_flower/Red_Flower_3.png");
	std::array<std::vector<Texture>, 5> m_flowers { {
		{
			Texture{"assets/Map/pink/Pink_Flower_1.png"},
			Texture{"assets/Map/pink/Pink_Flower_2.png"},
			Texture{"assets/Map/pink/Pink_Flower_3.png"}
		},
		{
			Texture{"assets/Map/purple/Purple_Flower_1.png"},
			Texture{"assets/Map/purple/Purple_Flower_2.png"},
			Texture{"assets/Map/purple/Purple_Flower_3.png"}
		},
		{
			Texture{"assets/Map/red_flower/Red_Flower_1.png"},
			Texture{"assets/Map/red_flower/Red_Flower_2.png"},
			Texture{"assets/Map/red_flower/Red_Flower_3.png"},
			Texture{"assets/Map/red_flower/Red_Flower_4.png"}
		},
		{
			Texture{"assets/Map/red_rose/Red_Rose_1.png"},
			Texture{"assets/Map/red_rose/Red_Rose_2.png"},
			Texture{"assets/Map/red_rose/Red_Rose_3.png"},
			Texture{"assets/Map/red_rose/Red_Rose_4.png"},
			Texture{"assets/Map/red_rose/Red_Rose_5.png"}
		}
		,
		{
			Texture{"assets/Map/yellow/1.png"},
			Texture{"assets/Map/yellow/2.png"},
			Texture{"assets/Map/yellow/3.png"},
			Texture{"assets/Map/yellow/4.png"}
		}
	} };
	Tileset m_earth = Tileset("assets/Map/TileSet_V1.png", vec2(32));
	Texture m_tree = Texture("assets/Map/tree.png");

	std::unordered_set<vec2, vec2_hash> m_additionalTrail;

	// Tiles
	Tiles m_waterTiles, m_landTiles, m_flowerTiles, m_treeTiles;

	void generateWaterLand(const ViewPort& viewport);
	void generateFlower(const ViewPort& viewport);
	void generateTree(const ViewPort& viewport);
	void drawWaterLand(RenderWindow& window);
	void drawFlower(RenderWindow& window);
	void drawTree(RenderWindow& window);

	// Determines what the water texture will be based on its neighbors
	Texture* getLandTexture(int x, int y);

	// Determines what aabbs will composite the bound of the water tile
	std::vector<AABB> getWaterBoundingBox(int x, int y) const;

	// Returns if an additional trail exist
	bool existAdditionTrail(int x, int y) const;
};