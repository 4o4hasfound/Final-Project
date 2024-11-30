#pragma once
#include "Render/Texture.hpp"

class RenderWindow;

class Drawable {
	friend class RenderWindow;
public:
	// Draw to screen without accounting the viewport of the window
	virtual void draw(Texture* texture = nullptr) = 0;
protected:
	// Draw to screen while accounting the viewport of the window
	virtual void draw(const RenderWindow* window, Texture* texture = nullptr) = 0;
public:
	bool absolutePosition = false;
};