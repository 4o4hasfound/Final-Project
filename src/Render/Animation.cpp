#include "Render/Animation.hpp"

Animation::Animation(const std::vector<Texture>& textures, float frameDuration)
	: m_textures(textures)
	, m_length(textures.size())
	, m_frameDuration(frameDuration)
	, m_end(textures.size()) {
	assert(!m_textures.empty());

	m_size = m_textures[0].getSize();
}

bool Animation::update(float dt) {
	m_progress += dt;
	if (m_progress >= m_frameDuration * m_end) {
		m_progress = m_frameDuration * (m_end)-0.01;
		return 1;
	}
	return 0;
}

void Animation::reset() {
	m_progress = (m_start - 1) * m_frameDuration;
}

Texture* Animation::getFrame() {
	const int index = static_cast<int>(m_progress / m_frameDuration);
	return &m_textures[index];
}

int Animation::getFrameIndex() const {
	const int index = static_cast<int>(m_progress / m_frameDuration);
	return index;
}

void Animation::setStartFrame(int start) {
	m_start = start;
}

void Animation::setEndFrame(int end) {
	m_end = end;
}
