#pragma once

#include "Game/Map/Map.hpp"

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
	Texture m_tree = Texture("assets/tree.png");

	void generateWaterLand(const vec2& position);
	void generateFlower(const vec2& position);
	void generateTree(const vec2& position);
	void drawWaterLand(RenderWindow& window);
	void drawFlower(RenderWindow& window);
	void drawTree(RenderWindow& window);
};