#include "Game/Skill/Skill.hpp"

Skill::Skill(SkillType _type, const std::string& _name, const Animation& animation, Player* player, PhysicsWorld* world, RenderWindow* window)
	: type(_type), name(_name), m_animation(animation), m_player(player), m_world(world), m_window(window) {

}

void Skill::update(float dt) {

}

void Skill::render(RenderWindow& window) {

}

void Skill::active() {

}

void Skill::use() {

}

void Skill::updateAnimation(float dt) {
	m_animation.update(dt, true);
}

void Skill::renderAnimation(const vec2& position, const vec2& size) {
	const Texture* texture = m_animation.getFrame();

	const vec2 textureSize = texture->size();
	
	float scale = std::min(size.x / textureSize.y, size.y / textureSize.
		y);

	Rectangle rect(texture->size() * scale);
	rect.position = position;
	rect.absolutePosition = true;
	m_window->draw(rect, texture);
}

vec2 Skill::getAnimationSize() const {
	return m_animation.getFrame()->size();
}

const Texture* Skill::getAnimationFrame() const {
	return m_animation.getFrame();
}
