#pragma once
#include <string>

#include "Engine/Audio.hpp"
#include "Engine/Keyboard.hpp"

#include "Render/Tileset.hpp"
#include "Render/Animation.hpp"
#include "Render/Shape.hpp"

#include "Physics/RigidBody.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

struct PlayerStatus {
	bool moving = 0;
	int direction = 1;
};

class Player: public RigidBody {
public:
	Player(const AABB& aabb);
	~Player() = default;

	void draw(RenderWindow& window);

	PlayerStatus status;
protected:
	Audio m_audio;

	Tileset m_walkset;

	Animation m_walkAnimation;
	Animation m_idleAnimation;

	virtual void myUpdate(float dt) override;
};