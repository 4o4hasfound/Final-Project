#include "Game/Skill/Skill.hpp"

Skill::Skill(const Animation& animation, Player* player, PhysicsWorld* world, RenderWindow* window)
	: m_animation(animation), m_player(player), m_world(world), m_window(window) {
}

void Skill::update() {

}

void Skill::render() {

}

void Skill::use() {

}

void Skill::updateAnimation(float dt) {
	m_animation.update(dt, true);
}

void Skill::renderAnimation(const vec2& position, const vec2& size) {
	Rectangle rect(size);
	rect.position = position;
	rect.absolutePosition = true;
	m_window->draw(rect, m_animation.getFrame());
}

const Texture* Skill::getAnimationFrame() const {
	return m_animation.getFrame();
}
