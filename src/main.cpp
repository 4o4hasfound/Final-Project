#include "Render/RenderWindow.hpp"
#include "Render/Shape.hpp"
#include "Render/Animation.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"
#include "Engine/Audio.hpp"

#include "Physics/AABB.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"
#include "Physics/PhysicsWorld.hpp"

#include "Game/Player/Player.hpp"
#include "Game/Player/Mushroom.hpp"
#include "Game/Enemy/Enemy.hpp"
#include "Game/Enemy/DroidZapper.hpp"

#include "Math/Vector.hpp"

#include "Game/Map/GrassMap.hpp"

#include "Utils/Clock.hpp"
#include "Utils/Noise.hpp"

#include <cmath>
#include <unordered_set>

int main() {
	Engine::init();
	RenderWindow window(1920, 1080, "Game");
	PhysicsWorld world;
	window.viewport.size *= 0.75;
	GrassMap map(window.viewport.size);
	Clock dtClock;
	
	MushroomPlayer* player = world.createBody<MushroomPlayer>();
	//window.viewport.size *= 2;

	FreeList<Enemy*> enemies;

	while (window.running()) {
		Engine::update();

		window.pollEvents();
		window.clear();

		float dt = dtClock.reset();

		// Update world
		world.update(dt);

		for (Enemy* enemy : enemies) {
			enemy->pathFind(&map, player, window);
			enemy->attack(player);
		}

		// Update map and handle collision
		map.resolveCollision(player);

		for (Enemy* enemy : enemies) {
			map.resolveCollision(enemy);
		}

		// Update viewport position
		window.viewport.position = player->position - window.viewport.size * 0.5;

		map.update(window.viewport);

		const auto& tiles = map.getWaterTiles();
		// Generate enemy
		for (int i = 0; i < tiles.grid.size(); ++i) {
			for (int j = 0; j < tiles.grid[0].size(); ++j) {
				const vec2 position = vec2(j, i) * tiles.size + tiles.position;
				if (tiles.grid[i][j].exist) {
					continue;
				}
				if (position <= window.viewport.position || position >= window.viewport.position + window.viewport.size) {
					if (Random::getReal<float>(0, 1) < 0.005 && enemies.size() < 5) {
						DroidZapperEnemy* enemy = world.createBody<DroidZapperEnemy>();
						enemy->position = position;
						enemies.push(enemy);
					}
				}
			}
		}

		// Delete enemy
		for (auto itr = enemies.begin(), end = enemies.end(); itr != end; ++itr) {
			if ((*itr)->position <= tiles.position || (*itr)->position >= tiles.position + tiles.size * vec2(tiles.grid[0].size(), tiles.grid.size())) {
				world.removeBody(*itr);
				enemies.remove(itr);
			}
		}

		// Add additional trails
		if (Mouse::get(Mouse::LEFT).pressed) {
			vec2 position = Mouse::getPosition();
			position *= window.viewport.size / window.size();
			map.setTile(position + window.viewport.position, false);
		}

		map.draw(window);
		
		// Draw character
		player->draw(window);

		for (Enemy* enemy : enemies) {
			enemy->draw(window);
		}
		//map.resolveCollision(player, window);
		//map.resolveCollision(enemy, window);

		// Fps
		window.setTitle(std::to_string(1.0 / dt).c_str());

		// Display
		window.flipDisplay();
	}

	Engine::terminate();
}