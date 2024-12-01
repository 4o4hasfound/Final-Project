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

#include "Game/Player.hpp"

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
	//window.viewport.size *= 2;
	GrassMap map(window.viewport.size);
	Clock dtClock;
	
	// Create player
	const AABB aabb = AABB(
		vec2(-5, 2),
		+vec2(5, 16)
	) * 3;
	Player* player = world.createBody<Player>(aabb);

	while (window.running()) {
		Engine::update();

		window.pollEvents();
		window.clear();

		float dt = dtClock.reset();

		// Update world
		world.update(dt);

		// Update map and handle collision
		map.resolveCollision(player);

		// Update viewport position
		window.viewport.position = player->position - window.viewport.size * 0.5;

		map.update(window.viewport);

		// Add additional trails
		if (Mouse::get(Mouse::LEFT).pressed) {
			map.setTile(Mouse::getPosition() + window.viewport.position, false);
		}

		map.draw(window);
		
		// Draw character
		player->draw(window);
		map.resolveCollision(player, window);

		// Fps
		window.setTitle(std::to_string(1.0 / dt).c_str());

		// Display
		window.flipDisplay();
	}

	Engine::terminate();
}