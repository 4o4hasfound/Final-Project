#include "Game/States/ChooseSkillState.hpp"

ChooseSkillState::ChooseSkillState(StateManager& manager, Player* player, PhysicsWorld* world, RenderWindow* window)
	: State(manager)
	, m_window(window)
	, m_world(world)
	, m_player(player) {
}

void ChooseSkillState::onEnter() {
	m_skills.push_back(std::move(std::make_unique<HealSkill>(m_player, m_world, m_window)));
}

void ChooseSkillState::onDestroy() {

}

void ChooseSkillState::onSuspend()
{
}

void ChooseSkillState::onWakeup() {

}

void ChooseSkillState::reset() {

}

void ChooseSkillState::update(RenderWindow& window, float dt) {
	for (auto& skill : m_skills) {
		skill->updateAnimation(dt);
	}
	if (AABB(vec2(500) - vec2(128, 128) * 0.5, vec2(500) + vec2(128, 128) * 0.5).intersect(Mouse::getPosition()) && Mouse::get(Mouse::LEFT).buttondown) {

		m_skills[0]->use();

		m_manager.popState(1);
	}
}

void ChooseSkillState::render(RenderWindow& window) {
	if (m_removed) {
		m_manager.nthState(0)->render(window);
		return;
	}
	m_manager.nthState(1)->render(window);
	Rectangle rect(window.size());
	rect.position = rect.size * 0.5;
	rect.color = vec4(0, 0, 0, 100);
	rect.absolutePosition = true;
	window.draw(rect);


	m_skills[0]->renderAnimation(vec2(500), vec2(128, 128));
}

bool ChooseSkillState::shouldClose()
{
	return false;
}
