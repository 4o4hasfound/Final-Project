#pragma once

#include <vector>

#include "Render/Texture.hpp"

class Animation {
public:
	Animation(const std::vector<Texture>& textures, float frameDuration);
	~Animation() = default;

	// Return 1 if reached the end
	bool update(float dt, bool loop = false);
	
	// Advance to next frame
	bool advance();

	void reset();

	// Returns the current playing frame
	const Texture* getFrame() const;

	int getFrameIndex() const;

	// Set the starting frame of the animatino
	void setStartFrame(int start);
	// Set the ending frame of the animatino
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