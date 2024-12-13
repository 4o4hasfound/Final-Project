#pragma once

#include <functional>

#include "Engine/Mouse.hpp"

#include "Physics/AABB.hpp"

#include "Render/RenderWindow.hpp"
#include "Render/Drawable.hpp"
#include "Render/Shape.hpp"

class Button : public Rectangle {
public:
	Button(const vec2& _size = vec2(0), std::function<void(void)> _callback = nullptr);

	void update(float dt);
	void update(float dt, std::function<void(void)> _callback);
	
	void setSize(const vec2& _size);

	float enlargeFactor = 1.5f;
	std::function<void(void)> callback;

	bool hover = false;
	bool pressed = false;
	bool released = true;
	bool buttondown = false;
	bool buttonup = false;
	bool pressedAndReleased = false;
	bool pressOnButton = false;

	vec2 originalSize;
protected:
};