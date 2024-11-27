#include "Render/RenderWindow.hpp"
#include "Render/Shape.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Physics/AABB.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"
#include "Math/Vector.hpp"

#include "Utils/Clock.hpp"
#include "Utils/Noise.hpp"

#include <cmath>
#include <unordered_set>

struct pair_hash {
	int operator()(const ivec2& p) const {
		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
	}
};

int main() {
	Engine::init();
	RenderWindow window(1920, 1080, "Game");

	al_set_new_display_flags(ALLEGRO_RESIZABLE); // No AA

	Texture grass("assets/grass.png");
	Texture water("assets/water.png");
	Texture tree("assets/tree.png");

	std::array<std::array<Texture, 3>, 5> flowers = { {
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
			Texture{"assets/red_flower/Red_Flower_3.png"}
		},
		{
			Texture{"assets/red_rose/Red_Rose_1.png"},
			Texture{"assets/red_rose/Red_Rose_2.png"},
			Texture{"assets/red_rose/Red_Rose_3.png"}
		}
		,
		{
			Texture{"assets/yellow/1.png"},
			Texture{"assets/yellow/2.png"},
			Texture{"assets/yellow/3.png"}
		}
	} };

	bool drag = false;
	vec2 delta;
	Clock t;
	while (window.running()) {
		window.clear();

		Keyboard::update();
		Mouse::update();

		float dt = t.reset();
		if (Keyboard::get(Keyboard::KEY_W).pressed) {
			window.viewport.position.y -= dt * 250;
		}
		if (Keyboard::get(Keyboard::KEY_S).pressed) {
			window.viewport.position.y += dt * 250;
		}
		if (Keyboard::get(Keyboard::KEY_A).pressed) {
			window.viewport.position.x -= dt * 250;
		}
		if (Keyboard::get(Keyboard::KEY_D).pressed) {
			window.viewport.position.x += dt * 250;
		}
		std::unordered_set<ivec2, pair_hash> s;
		float tileSize = 100;
		for (int i = -1; i <= window.size().y / tileSize + 2; ++i) {
			for (int j = -1; j <= window.size().x / tileSize + 2; ++j) {
				Rectangle rect({ tileSize + 1, tileSize + 1 });
				rect.position = (vec2(j, i) * tileSize + window.viewport.position) / tileSize;
				rect.position = vec2(
					std::round(std::floor(rect.position.x) * tileSize),
					std::round(std::floor(rect.position.y) * tileSize)
				);
				Noise::octaves = 11;
				Noise::persistence = 0.55;
				Noise::lacunarity = 2;
				float value = (Noise::get(rect.position) + 1) * 0.5;
				Noise::octaves = 4;
				const float valueU1 = Noise::getUniform(rect.position);
				rect.rotation = static_cast<int>((valueU1 - 0.000001) * 4) * 0.5 * PI;
				if (value < 0.65) {
					window.draw(rect, &grass);
				}
				else {
					s.insert(ivec2(rect.position / tileSize));
					window.draw(rect, &water);
				}
			}
		}
		int flowerTileSize = tileSize * 0.5;
		for (int i = -1 / flowerTileSize; i <= window.size().y / flowerTileSize + 5; ++i) {
			for (int j = -1 / flowerTileSize; j <= window.size().x / flowerTileSize + 5; ++j) {
				Rectangle rect({ 100, 100 });
				rect.position = (vec2(j, i) * flowerTileSize + window.viewport.position) / flowerTileSize;
				rect.position = vec2(
					std::round(std::floor(rect.position.x) * flowerTileSize),
					std::round(std::floor(rect.position.y) * flowerTileSize)
				);
				if (s.count(ivec2(rect.position / tileSize))) {
					continue;
				}
				Noise::octaves = 11;
				Noise::persistence = 0.55;
				Noise::lacunarity = 2.1;
				const float value = (Noise::get(rect.position) + 1) * 0.5;
				const float value1 = (Noise::get(rect.position*2) + 1) * 0.5;
				Noise::octaves = 2;
				const float valueU2 = Noise::getUniform(rect.position);
				rect.rotation = 0;
				rect.position += (valueU2 - 0.5) * flowerTileSize;
				if (value < 0.25) {
					auto& flower = flowers[static_cast<int>((valueU2 - 0.000001) * 5)];
					window.draw(rect, &flower[static_cast<int>((valueU2 - 0.000001) * 3)]);
				}
			}
		}
		flowerTileSize = tileSize;
		for (int i = -1; i <= window.size().y / flowerTileSize + 2; ++i) {
			for (int j = -1; j <= window.size().x / flowerTileSize + 2; ++j) {
				Rectangle rect({ 200, 200 });
				rect.position = (vec2(j, i) * flowerTileSize + window.viewport.position) / flowerTileSize;
				rect.position = vec2(
					std::round(std::floor(rect.position.x) * flowerTileSize),
					std::round(std::floor(rect.position.y) * flowerTileSize)
				);
				if (s.count(ivec2(rect.position / tileSize))) {
					continue;
				}
				Noise::octaves = 11;
				Noise::persistence = 0.55;
				Noise::lacunarity = 2;
				const float value = (Noise::get(rect.position) + 1) * 0.5;
				Noise::octaves = 2;
				const float valueU1 = Noise::getUniform(rect.position);
				rect.rotation = 0;
				rect.position += (valueU1 - 0.5) * flowerTileSize;
				if (value < 0.5 && value > 0.49) {
					window.draw(rect, &tree);
				}
			}
		}
		//Logger::Log<Debug>(t.duration());
		window.flipDisplay();
	}

	Engine::terminate();
}