#include "Game/States/ChooseSkillState.hpp"

ChooseSkillState::ChooseSkillState(StateManager& manager, Player* player, PhysicsWorld* world, RenderWindow* window)
	: State(manager)
	, m_window(window)
	, m_world(world)
	, m_player(player) {
}

void ChooseSkillState::onEnter() {
	m_skills.push_back(std::move(std::make_unique<InvincibleShieldSkill>(m_player, m_world, m_window)));
	m_skills.push_back(std::move(std::make_unique<IncreaseLoadSpeedSkill>(m_player, m_world, m_window)));
	m_skills.push_back(std::move(std::make_unique<IncreaseShootSpeedSkill>(m_player, m_world, m_window)));
	m_buttons.emplace_back(vec2(120, 120));
	m_buttons.back().position = vec2(500);
	m_buttons.emplace_back(vec2(256, 256));
	m_buttons.back().position = vec2(800, 500);
	m_buttons.emplace_back(vec2(160, 64));
	m_buttons.back().position = vec2(1100, 500);
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
	for (int i = 0; i < m_skills.size(); ++i) {
		m_skills[i]->updateAnimation(dt);
		m_buttons[i].update(dt);
		
		if (m_buttons[i].pressedAndReleased) {
			m_skills[i]->use();
			m_player->status.skills.push_back(m_skills[i].get());
			goBack();
		}
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

	for (int i = 0; i < m_skills.size(); ++i) {
		window.draw(m_buttons[i], m_skills[i]->getAnimationFrame());
	}
}

bool ChooseSkillState::shouldClose()
{
	return false;
}

void ChooseSkillState::goBack() {
	m_manager.popState();
	m_removed = true;
}

std::string ChooseSkillState::getDescription(int i) {
	switch (i) {
	case 0:
		return "Invincible shield that defend you from all sorts of brutal attacks!";
	}
}
