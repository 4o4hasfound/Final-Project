#pragma once

#include "Game/Map/Map.hpp"

#include "Render/Animation.hpp"
#include "Render/Tileset.hpp"

class GrassMap : public Map {
public:
	GrassMap(const vec2& size);
	virtual ~GrassMap() = default;

	virtual void update(ViewPort& position) override;
	virtual void draw(RenderWindow& window) override;

	virtual bool intersect() override;
private:
	float m_waterThreshold = 0.35;
	float m_flowerThreshold = 0.35;
	float m_treeThreshold = 0.2;
	Tiles m_waterTiles, m_landTiles, m_flowerTiles, m_treeTiles;
	Texture m_water = Texture("assets/water.png");
	Texture m_land = Texture("assets/grass.png");
	Texture m_flower = Texture("assets/red_flower/Red_Flower_3.png");
	std::array<std::vector<Texture>, 5> m_flowers { {
		{
			Texture{"assets/pink/Pink_Flower_1.png"},
			Texture{"assets/pink/Pink_Flower_2.png"},
			Texture{"assets/pink/Pink_Flower_3.png"}
		},
		{
			Texture{"assets/purple/Purple_Flower_1.png"},
			Texture{"assets/purple/Purple_Flower_2.png"},
			Texture{"assets/purple/Purple_Flower_3.png"}
		},
		{
			Texture{"assets/red_flower/Red_Flower_1.png"},
			Texture{"assets/red_flower/Red_Flower_2.png"},
			Texture{"assets/red_flower/Red_Flower_3.png"},
			Texture{"assets/red_flower/Red_Flower_4.png"}
		},
		{
			Texture{"assets/red_rose/Red_Rose_1.png"},
			Texture{"assets/red_rose/Red_Rose_2.png"},
			Texture{"assets/red_rose/Red_Rose_3.png"},
			Texture{"assets/red_rose/Red_Rose_4.png"},
			Texture{"assets/red_rose/Red_Rose_5.png"}
		}
		,
		{
			Texture{"assets/yellow/1.png"},
			Texture{"assets/yellow/2.png"},
			Texture{"assets/yellow/3.png"},
			Texture{"assets/yellow/4.png"}
		}
	} };
	Tileset m_earth = Tileset("assets/TileSet_V1.png", vec2(32));
	Texture m_tree = Texture("assets/tree.png");

	void generateWaterLand(const vec2& position);
	void generateFlower(const vec2& position);
	void generateTree(const vec2& position);
	void drawWaterLand(RenderWindow& window);
	void drawFlower(RenderWindow& window);
	void drawTree(RenderWindow& window);
	Texture* getLandTexture(int x, int y);
};