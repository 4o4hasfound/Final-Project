#include "Game/Enemy/DroidZapper.hpp"

static EnemyConfig enemyConfig{
	1000.0,
	20.0,
	250.0,
	600,
	400,

	3,
	vec2{ 58.0, 41.0f },
	vec2{ 15.5f, 27.5f },
	AABB{ 
		{9, 15},
		{22, 40}
	} - vec2{ 15.5f, 27.5f }
};

DroidZapperEnemy::DroidZapperEnemy()
	: Enemy(enemyConfig) {

}

void DroidZapperEnemy::draw(RenderWindow& window) const {
	Rectangle rect(config.size * config.scale);
	vec2 delta;

	if (status.direction == 1) {
		delta = config.center * config.scale;
	}
	else {
		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
	}
	rect.position = position + rect.size * 0.5 - delta;
	rect.outlineColor = vec4(255, 0, 0, 255);
	rect.outlineThickness = 5.0f;
	if (status.direction == 1) {
		rect.flip.x = 0;
	}
	else {
		rect.flip.x = 1;
	}
	if (status.attacking) {
		window.draw(rect, m_atkAnimation.getFrame());
	}
	else if (status.moving) {
		window.draw(rect, m_runAnimation.getFrame());
	}
	else {
		window.draw(rect, m_idleAnimation.getFrame());
	}
	//getAABB().DebugDraw(window);
}

void DroidZapperEnemy::attack(Player* player) {
	if (status.state == Hunt && distance(position, player->position) <= 200) {
		status.attacking = true;
	}
	else {
		status.attacking = false;
	}
}

void DroidZapperEnemy::myUpdate(float dt) {
	//// Keyboard inputs
	//if (Keyboard::get(Keyboard::KEY_UP).pressed) {
	//	velocity.y = -1;
	//	walking = true;
	//}
	//else if (Keyboard::get(Keyboard::KEY_DOWN).pressed) {
	//	velocity.y = 1;
	//	walking = true;
	//}
	//else {
	//	velocity.y = 0;
	//}
	//if (Keyboard::get(Keyboard::KEY_LEFT).pressed) {
	//	velocity.x = -1;
	//	status.direction = -1;
	//	walking = true;
	//}
	//else if (Keyboard::get(Keyboard::KEY_RIGHT).pressed) {
	//	velocity.x = 1;
	//	status.direction = 1;
	//	walking = true;
	//}
	//else {
	//	velocity.x = 0;
	//}

	if (status.knockbackCD == 0) {
		if (sign(velocity.x)) {
			status.direction = sign(velocity.x);
		}

		// Normalize velocity vector
		if (velocity.x || velocity.y) {
			velocity = normalize(velocity) * config.speed;
		}

	}


	// Handle animation changes
	if (status.attacking) {
		m_runAnimation.reset();
		m_idleAnimation.reset();
	}
	else if (!status.moving) {
		m_runAnimation.reset();
	}
	else if (status.moving) {
		m_atkAnimation.reset();
	}

	if (status.attacking) {
		m_atkAnimation.update(dt, true);
	}
	else if (status.moving) {
		m_runAnimation.update(dt, true);
	}
	else {
		m_idleAnimation.update(dt, true);
	}

	//status.moving = walking;
}
