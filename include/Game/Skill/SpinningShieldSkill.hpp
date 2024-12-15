#pragma once

#include "Game/Player/Player.hpp"
#include "Game/Skill/Skill.hpp"

#include "Game/Entity/FloatingShield.hpp"

class SpinningShieldSkill : public Skill {
public:
	SpinningShieldSkill(Player* player, PhysicsWorld* world, RenderWindow* window);
	~SpinningShieldSkill() = default;

	virtual void update(float dt) override;
	virtual void render(RenderWindow& window) override;

	float rotationSpeed = 1.0;
private:
	float m_rotation;
	std::vector<FloatingShieldEntity*> m_shields;
};