#pragma once

#include <vector>

#include "Render/Texture.hpp"

class Animation {
public:
	//Animation(const std::vector<std::string>& textures, float frameDuration);
	Animation(const std::vector<Texture>& textures, float frameDuration);
	~Animation() = default;

	// Return 1 if reached the end
	bool update(float dt);

	void reset();

	Texture* getFrame();

	int getFrameIndex() const;
	void setStartFrame(int start);
	void setEndFrame(int end);

	int getStartFrame() const { return m_start; }
	int getEndFrame() const { return m_end; }
	float getProgress() const { return m_progress; }
	float getFrameDuration() const { return m_frameDuration; }
private:
	int m_start = 0, m_end;
	float m_progress = 0.0;
	float m_frameDuration;

	int m_length;
	vec2 m_size;

	std::vector<Texture> m_textures;
};