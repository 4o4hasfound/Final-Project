#pragma once

#include "Game/Enemy/Enemy.hpp"

class DroidZapperEnemy : public Enemy {
public:
	DroidZapperEnemy();
	~DroidZapperEnemy() = default;

	virtual void draw(RenderWindow& window) const override;
	virtual void attack(Player* player) override;

protected:
	Audio m_audio;

	Tileset m_runset;
	Tileset m_idleset;
	Tileset m_atkset;

	Animation m_runAnimation;
	Animation m_idleAnimation;
	Animation m_atkAnimation;

	virtual void myUpdate(float dt) override;
};