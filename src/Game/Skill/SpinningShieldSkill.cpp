#include "Game/Skill/SpinningShieldSkill.hpp"

SpinningShieldSkill::SpinningShieldSkill(Player* player, PhysicsWorld* world, RenderWindow* window)
	: Skill(Skill::Passive, "SpinningShield",
		Animation(
			{ {"assets/Skill/SpinningShield/shield.png"} },
			1.0f
		),
		player,
		world,
		window) {

}

void SpinningShieldSkill::update(float dt) {
	m_rotation += dt * rotationSpeed;
	m_rotation = std::fmodf(m_rotation, PI_TWO);

	if (level != m_shields.size()) {
		for (int i = m_shields.size(); i < level; ++i) {
			FloatingShieldEntity* shield = m_world->createBody<FloatingShieldEntity>(m_world, m_window);
			shield->player = m_player;
			m_shields.push_back(shield);
		}
	}
	const float delta = PI_TWO / level;
	for (int i = 0; i < m_shields.size(); ++i) {
		FloatingShieldEntity* shield = m_shields[i];
		shield->rotation = m_rotation + delta * i;
	}
}

void SpinningShieldSkill::render(RenderWindow& window) {

}
