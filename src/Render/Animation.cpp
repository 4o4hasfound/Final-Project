#include "Render/Animation.hpp"

Animation::Animation(const std::vector<Texture>& textures, float frameDuration)
	: m_textures(textures)
	, m_length(textures.size())
	, m_frameDuration(frameDuration)
	, m_end(textures.size()) {
	assert(!m_textures.empty());

	m_size = m_textures[0].getSize();
}

Animation::Animation(const std::string& filename, const vec2& size, const std::vector<vec2>& index, float frameDuration)
	: m_length(index.size())
	, m_frameDuration(frameDuration)
	, m_end(index.size()) {
	assert(!index.empty());
	Tileset tileset(filename, size);

	for (vec2 ind : index) {
		m_textures.push_back(tileset[ind.y][ind.x]);
	}

	m_size = size;
}

bool Animation::update(float dt, bool loop) {
	m_progress += dt;
	if (m_progress >= m_frameDuration * m_end) {
		m_progress = m_frameDuration * (m_end)-0.01;

		if (loop) {
			reset();
		}
		return 1;
	}
	return 0;
}

bool Animation::advance(int i) {
	m_progress += m_frameDuration * i;
	if (m_progress >= m_frameDuration * m_end) {
		m_progress = m_frameDuration * (m_end)-0.01;
		return 1;
	}
	return 0;
}

void Animation::toBegin() {
	m_progress = std::max(0.0f, (m_start - 1) * m_frameDuration);
}

void Animation::toEnd() {
	m_progress = m_frameDuration * (m_end * 0.999999);
}

void Animation::reset() {
	m_progress = std::max(0.0f, (m_start - 1) * m_frameDuration);
}

const Texture* Animation::getFrame() const {
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
