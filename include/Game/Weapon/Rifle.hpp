#pragma once

#include "Engine/Keyboard.hpp"
#include "Engine/Mouse.hpp"

#include "Game/Weapon/Weapon.hpp"
#include "Game/Player/Player.hpp"

#include "Render/Shape.hpp"
#include "Render/Texture.hpp"
#include "Render/Animation.hpp"
#include "Render/Tileset.hpp"

#include "Math/Vector.hpp"
#include "Math/Functions.hpp"

class Rifle : public Weapon {
public:
	Rifle(Player* player, RenderWindow* window);
	~Rifle() = default;

	virtual void update(float dt) override;
	virtual void draw(RenderWindow& window) override;
	virtual void attack(PhysicsWorld* world) override;

private:
	Player* m_player;
	RenderWindow* m_window;
	Tileset m_tileset;
	Animation m_animation;
	Audio m_audio{ "assets/Scar/sound.mp3" };
};