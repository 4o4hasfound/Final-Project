//#include "Game/Player/Mushroom.hpp"
//
////static PlayerConfig playerConfig{
////	100.0,
////	20.0,
////	1.0,
////
////	1.0,
////	vec2{ 15.5f, 27.5f },
////	vec2{ 14.0f, 26.0f }
////};
//static PlayerConfig playerConfig{
//	100.0,
//	20.0,
//	400.0,
//	
//	3.0,
//	vec2{ 32.0f, 32.0f },
//	vec2{ 15.5f, 18.5f },
//	AABB{ 
//		{10, 16},
//		{21, 31}
//	} - vec2{ 15.5f, 18.5f }
//};
//
//MushroomPlayer::MushroomPlayer()
//	: Player(playerConfig)
//	, m_audio("assets/grassSound.mp3")
//	, m_walkset("assets/walk.png", playerConfig.size)
//	, m_walkAnimation({ m_walkset[2][0], m_walkset[2][1], m_walkset[2][2], m_walkset[2][3] }, 1.0 / 8)
//	, m_idleAnimation({ m_walkset[1][0], m_walkset[1][1] }, 1.0 / 3) {
//}
//
//void MushroomPlayer::draw(RenderWindow& window) const {
//	Rectangle rect(config.size * config.scale);
//	vec2 delta;
//	if (status.direction == 1) {
//		delta = config.center * config.scale;
//	}
//	else {
//		delta = vec2(config.size.x - config.center.x, config.center.y) * config.scale;
//	}
//	rect.position = position + rect.size * 0.5 - delta;
//	rect.outlineColor = vec4(255, 0, 0, 255);
//	rect.outlineThickness = 5.0f;
//	if (status.direction == 1) {
//		rect.flip.x = 0;
//	}
//	else {
//		rect.flip.x = 1;
//	}
//	if (status.moving) {
//		window.draw(rect, m_walkAnimation.getFrame());
//	}
//	else {
//		window.draw(rect, m_idleAnimation.getFrame());
//	}
//	//getAABB().DebugDraw(window);
//}
//
//void MushroomPlayer::myUpdate(float dt) {
//	bool walking = false;
//
//	// Keyboard inputs
//	if (Keyboard::get(Keyboard::KEY_W).pressed) {
//		velocity.y = -1;
//		walking = true;
//	}
//	else if (Keyboard::get(Keyboard::KEY_S).pressed) {
//		velocity.y = 1;
//		walking = true;
//	}
//	else {
//		velocity.y = 0;
//	}
//	if (Keyboard::get(Keyboard::KEY_A).pressed) {
//		velocity.x = -1;
//		status.direction = -1;
//		walking = true;
//	}
//	else if (Keyboard::get(Keyboard::KEY_D).pressed) {
//		velocity.x = 1;
//		status.direction = 1;
//		walking = true;
//	}
//	else {
//		velocity.x = 0;
//	}
//
//	// Normalize velocity vector
//	if (velocity.x || velocity.y) {
//		velocity = normalize(velocity) * config.speed;
//	}
//
//	// Handle audio
//	if (!walking) {
//		velocity = vec2(0);
//		m_audio.stop();
//	}
//	else {
//		if (!m_audio.playing()) {
//			// Speed up a little bit
//			m_audio.play(1.3);
//		}
//	}
//
//	// Handle animation changes
//	if (!walking && status.moving) {
//		m_walkAnimation.reset();
//		m_idleAnimation.reset();
//		m_idleAnimation.advance();
//	}
//
//	if (walking) {
//		m_walkAnimation.update(dt, true);
//	}
//	else {
//		m_idleAnimation.update(dt, true);
//	}
//
//	status.moving = walking;
//}
