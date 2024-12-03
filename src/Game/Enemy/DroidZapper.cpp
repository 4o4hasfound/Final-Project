#include "Game/Enemy/DroidZapper.hpp"

static EnemyConfig enemyConfig{
	100.0,
	20.0,
	350.0,

	3,
	vec2{ 58.0, 41.0f },
	vec2{ 15.5f, 27.5f },
	AABB{ 
		{9, 15},
		{22, 40}
	} - vec2{ 15.5f, 27.5f }
};

DroidZapperEnemy::DroidZapperEnemy()
	: Enemy(enemyConfig)
	, m_audio("assets/grassSound.mp3")
	, m_runset("assets/Droid Zapper/run.png", enemyConfig.size)
	, m_idleset("assets/Droid Zapper/wake.png", enemyConfig.size)
	, m_atkset("assets/Droid Zapper/attack.png", enemyConfig.size)
	, m_runAnimation({ m_runset[0][0], m_runset[1][0], m_runset[2][0], m_runset[3][0], m_runset[4][0], m_runset[5][0] }, 1.0 / 12)
	, m_idleAnimation({ m_idleset[0][0], m_idleset[1][0], m_idleset[2][0], m_idleset[3][0], m_idleset[4][0], m_idleset[5][0] }, 1.0 / 12)
	, m_atkAnimation({ m_atkset[0][0], m_atkset[1][0], m_atkset[2][0], m_atkset[3][0], m_atkset[4][0], m_atkset[5][0], m_atkset[6][0], m_atkset[7][0], m_atkset[8][0], m_atkset[9][0] }, 1.0 / 12){

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

	if (sign(velocity.x)) {
		status.direction = sign(velocity.x);
	}

	// Normalize velocity vector
	if (velocity.x || velocity.y) {
		velocity = normalize(velocity) * config.speed;
	}

	// Handle audio
	if (!status.moving) {
		velocity = vec2(0);
		m_audio.stop();
	}
	else {
		if (!m_audio.playing()) {
			// Speed up a little bit
			float sound = std::min(1.0, std::pow(std::max((500.0f-distance(position, status.playerPosition)) / 500.0f, 0.0f), 2));
			//Logger::Log<Debug>(sound);
			m_audio.play(1.3, sound);
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
