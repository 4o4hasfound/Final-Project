#include "Render/RenderWindow.hpp"
#include "Render/Shape.hpp"
#include "Render/Animation.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Physics/AABB.hpp"
#include "Physics/BoundingVolumeHierarchy.hpp"
#include "Physics/PhysicsWorld.hpp"

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
	GrassMap map(window.size());
	Clock dtClock;

	// Load tileset
	Tileset walkset("assets/walk.png", vec2(32));
	// Create walking animation
	Animation walkAnimation({ walkset[2][0], walkset[2][1], walkset[2][2], walkset[2][3] }, 1.0 / 8);
	// Create idle animation
	Animation idleAnimation({ walkset[1][0], walkset[1][1] }, 1.0 / 3);
	
	// Create rigid body for character
	const AABB aabb = AABB(
		vec2(-2, 4),
		+vec2(2, 12)
	) * 4;
	RigidBody* camera = world.createBody(
		RigidBody::Dynamic,
		aabb
	);

	// Some flags
	int direction = 1;
	bool lastWalking = false;

	while (window.running()) {
		window.pollEvents();
		window.clear();

		Engine::update();

		float dt = dtClock.reset();
		bool walking = false;

		// Keyboard inputs
		if (Keyboard::get(Keyboard::KEY_W).pressed) {
			camera->velocity.y = -1;
			walking = true;
		}
		else if (Keyboard::get(Keyboard::KEY_S).pressed) {
			camera->velocity.y = 1;
			walking = true;
		}
		else {
			camera->velocity.y = 0;
		}
		if (Keyboard::get(Keyboard::KEY_A).pressed) {
			camera->velocity.x = -1;
			direction = -1;
			walking = true;
		}
		else if (Keyboard::get(Keyboard::KEY_D).pressed) {
			camera->velocity.x = 1;
			direction = 1;
			walking = true;
		}
		else {
			camera->velocity.x = 0;
		}
		if (!walking) {
			camera->velocity = vec2(0);
		}
		if (camera->velocity.x || camera->velocity.y) {
			camera->velocity = normalize(camera->velocity) * 400;
		}

		// Handle animation changes
		if (!walking && lastWalking) {
			walkAnimation.reset();
			idleAnimation.reset();
		}
		lastWalking = walking;

		// Update world
		world.update(dt);

		// Update map and handle collision
		map.resolveCollision(camera);
		// Update viewport position
		window.viewport.position = camera->position - window.viewport.size * 0.5;
		map.update(window.viewport);
		map.draw(window);
		
		// Draw character
		Rectangle middle(vec2(128, 128));
		middle.position = camera->position;
		middle.outlineColor = vec4(255, 0, 0, 255);
		middle.outlineThickness = 5.0f;
		if (direction == 1) {
			middle.flip.x = 0;
		}
		else {
			middle.flip.x = 1;
		}
		if (walking) {
			if (walkAnimation.update(dt)) {
				walkAnimation.reset();
			}
			window.draw(middle, walkAnimation.getFrame());
		}
		else {
			if (idleAnimation.update(dt)) {
				idleAnimation.reset();
			}
			window.draw(middle, idleAnimation.getFrame());
		}

		window.flipDisplay();
	}

	Engine::terminate();
}