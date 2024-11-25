#pragma once
#include "Render/Texture.hpp"

class RenderWindow;

class Drawable {
	friend class RenderWindow;

protected:
	virtual void draw(Texture* texture = nullptr) = 0;
public:
	bool enableAbsolutePosition = false;
};