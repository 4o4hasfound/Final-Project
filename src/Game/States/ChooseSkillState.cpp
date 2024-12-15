#include "Game/States/ChooseSkillState.hpp"

ChooseSkillState::ChooseSkillState(StateManager& manager, Player* player, PhysicsWorld* world, RenderWindow* window)
	: State(manager)
	, m_window(window)
	, m_world(world)
	, m_player(player)
	, m_text(&m_font) {
}

void ChooseSkillState::onEnter() {
	std::vector<int> sequence(13);
	std::iota(sequence.begin(), sequence.end(), 0);

	std::shuffle(sequence.begin(), sequence.end(), std::random_device());

	m_index.resize(3);
	for (int i = 0; i < 3; ++i) {
		m_skills.push_back(getSkill(sequence[i]));
		m_buttons.emplace_back(m_skills.back()->getAnimationSize() * 3);
		m_buttons.back().position = vec2(560 + 400 * i, 500);
		m_index[i] = sequence[i];
	}

	m_text.position = vec2(960, 700);
	m_text.size = 50;
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
			if (m_skills[i]->type != Skill::OneTimeUse) {
				addPlayerSkill(m_skills[i].release());
			}
			goBack();
			break;
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

		if (m_buttons[i].hover) {
			m_text.string = getDescription(m_index[i]);
			m_text.color = vec4(255);
			window.draw(m_text);
		}
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
		return "An invincible shield that appears for a few seconds at regular intervals";
	case 1:
		return "A flying shield that orbits the player, capable of blocking bullets";
	case 2:
		return "Periodically increases the player's damage";
	case 3:
		return "Increases the damage";
	case 4:
		return "Increases the load speed";
	case 5:
		return "Increases the shoot speed";
	case 6:
		return "Increases the max health";
	case 7:
		return "Increases the movement speed";
	case 8:
		return "Equip bullets that make your enemies froze!";
	case 9:
		return "Equip bullets that make your enemies explode!";
	case 10:
		return "A basic first aid kit that can help you heal";
	case 11:
		return "A premium first aid kit that can help you heal full health";
	case 12:
		return "Release a NUKE at an enemy's location";
	}
	return "";
}

std::unique_ptr<Skill> ChooseSkillState::getSkill(int i) {
	switch (i) {
	case 0:
		return std::make_unique<InvincibleShieldSkill>(m_player, m_world, m_window);
	case 1:
		return std::make_unique<SpinningShieldSkill>(m_player, m_world, m_window);
	case 2:
		return std::make_unique<AttackEnhancementSkill>(m_player, m_world, m_window);
	case 3:
		return std::make_unique<IncreaseAttackSkill>(m_player, m_world, m_window);
	case 4:
		return std::make_unique<IncreaseLoadSpeedSkill>(m_player, m_world, m_window);
	case 5:
		return std::make_unique<IncreaseShootSpeedSkill>(m_player, m_world, m_window);
	case 6:
		return std::make_unique<IncreaseHealthSkill>(m_player, m_world, m_window);
	case 7:
		return std::make_unique<IncreaseMovementSpeedSkill>(m_player, m_world, m_window);
	case 8:
		return std::make_unique<FreezingBulletSkill>(m_player, m_world, m_window);
	case 9:
		return std::make_unique<ExplosiveBulletSkill>(m_player, m_world, m_window);
	case 10:
		return std::make_unique<HealSkill>(m_player, m_world, m_window);
	case 11:
		return std::make_unique<PremiumHealSkill>(m_player, m_world, m_window);
	case 12:
		return std::make_unique<ExplosionSkill>(m_player, m_world, m_window);
	}
	return nullptr;
}

void ChooseSkillState::addPlayerSkill(Skill* skill) {
	bool inPlayerSkill = false;
	for (Skill* playerSkill : m_player->status.skills) {
		if (playerSkill->name == skill->name) {
			++playerSkill->level;
			inPlayerSkill = true;
		}
	}
	if (!inPlayerSkill) {
		m_player->status.skills.push_back(skill);
	}
}
