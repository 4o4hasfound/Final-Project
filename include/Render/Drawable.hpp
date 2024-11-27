#pragma once
#include "Render/Texture.hpp"

class RenderWindow;

class Drawable {
	friend class RenderWindow;
public:
	virtual void draw(Texture* texture = nullptr) = 0;
protected:
	virtual void draw(const RenderWindow* window, Texture* texture = nullptr) = 0;
public:
	bool absolutePosition = false;
};