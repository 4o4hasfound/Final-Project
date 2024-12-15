#include "Game/Skill/ExplosionSkill.hpp"

ExplosionSkill::ExplosionSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::Passive, "ExplosionSkill",
		Animation{
		"assets/Guns/RPG/explosion.png",
		vec2(32),
		std::vector<vec2>{
			{0, 2},
			{0, 3},
			{0, 4},
			{0, 5},
			{0, 6},
			{0, 7},
			{0, 8},
			{0, 9},
			{0, 10},
			{0, 11},
		},
		1.0 / 10
		}, player, world, window)
	, m_explosion(
		"assets/Guns/RPG/explosion.png",
		vec2(32),
		std::vector<vec2>{
			{0, 2},
			{ 0, 3 },
			{ 0, 4 },
			{ 0, 5 },
			{ 0, 6 },
			{ 0, 7 },
			{ 0, 8 },
			{ 0, 9 },
			{ 0, 10 },
			{ 0, 11 },
		},
	1.0 / 10
	) {

}

void ExplosionSkill::update(float dt) {
	m_clock -= dt;
	if (m_clock <= 0) {
		if (m_used) {
			if (level == 1) {
				m_clock = 40;
			}
			else if (level == 2) {
				m_clock = 38;
			}
			else if (level == 3) {
				m_clock = 36;
			}
			else if (level == 4) {
				m_clock = 33;
			}
			else {
				m_clock = 30;
			}
			m_used = 0;
		}
		else {
			m_used = 1;
			m_clock = 2;
			m_explosion.reset();

			BoundingCircle range(m_player->position, (800 + level * 50));
			std::vector<Enemy*> inRange = m_world->query<Enemy>(range, RigidBody::EnemyType);

			if (inRange.empty()) {
				m_used = 0;
				m_clock = 0;
				return;
			}
			m_explodePosition = vec2(std::numeric_limits<int>::max());
			for (Enemy* enemy : inRange) {
				if (distance(m_explodePosition, m_player->position) > distance(enemy->position, m_player->position)) {
					m_explodePosition = enemy->position;
				}
			}

			BoundingCircle circle(m_explodePosition, (500 + level * 25));
			std::vector<Enemy*> enemies = m_world->query<Enemy>(circle, RigidBody::EnemyType);

			for (Enemy* enemy : enemies) {
				const vec2 dir = enemy->position - m_explodePosition;
				if (enemy->hit(1000, normalize(dir) * 2500, m_player, m_world)) {
					++m_player->status.enemyCount;
				}
			}

			m_audio.play(1.0);
		}
	}

	if (m_used) {
		m_explosion.update(dt, false);
	}
	m_animation.update(dt, true);
}

void ExplosionSkill::render(RenderWindow& window) {
	if (m_used) {
		Rectangle rect(vec2(32, 32) * ((500 + level * 25) * 2 / 32));
		rect.position = m_explodePosition;
		window.draw(rect, m_explosion.getFrame());
	}
}

void ExplosionSkill::renderAnimation(const vec2& position, const vec2& size) {
	const Texture* texture = m_animation.getFrame();

	const vec2 textureSize = texture->size();

	float scale = std::min(size.x / textureSize.y, size.y / textureSize.
		y);

	Rectangle rect(texture->size() * scale);
	rect.position = position;
	rect.absolutePosition = true;
	m_window->draw(rect, texture);

	if (!m_used) {
		rect.color = vec4(58, 58, 58, 100);
		m_window->draw(rect);
	}

	Text text(&m_font);
	text.string = std::to_string(static_cast<int>(m_clock));
	text.position = position;
	text.size = 40;
	m_window->draw(text);
}
