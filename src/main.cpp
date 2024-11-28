#include "Render/RenderWindow.hpp"
#include "Render/Shape.hpp"
#include "Render/Animation.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Physics/AABB.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"
#include "Math/Vector.hpp"

#include "Game/Map/GrassMap.hpp"

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
	GrassMap map(window.size());
	Clock t;
	while (window.running()) {
		window.pollEvents();
		window.clear();

		Keyboard::update();
		Mouse::update();

		float dt = t.reset();
		if (Keyboard::get(Keyboard::KEY_W).pressed) {
			window.viewport.position.y -= dt * 300;
		}
		if (Keyboard::get(Keyboard::KEY_S).pressed) {
			window.viewport.position.y += dt * 300;
		}
		if (Keyboard::get(Keyboard::KEY_A).pressed) {
			window.viewport.position.x -= dt * 300;
		}
		if (Keyboard::get(Keyboard::KEY_D).pressed) {
			window.viewport.position.x += dt * 300;
		}

		map.update(window.viewport);
		map.draw(window);

		window.flipDisplay();
	}

	Engine::terminate();
}