#include "Render/Button.hpp"

Button::Button(const vec2& _size, std::function<void(void)> _callback)
	: Rectangle(_size)
	, originalSize(_size)
	, callback(_callback) {
	absolutePosition = true;
}

void Button::update(float dt) {
	bool lastPressed = pressed;
	bool lastReleased = released;

	hover = AABB(position - size * 0.5, position + size * 0.5).intersect(Mouse::getPosition());


	if (hover) {
		size = originalSize * enlargeFactor;

		pressed = Mouse::get(Mouse::LEFT).pressed;
		released = !pressed;
		buttondown = Mouse::get(Mouse::LEFT).buttondown && lastReleased;
		buttonup = Mouse::get(Mouse::LEFT).buttonup && lastPressed;

		if (buttondown && callback) {
			callback();
		}
	}
	else {
		size = originalSize;

		pressed = false;
		released = true;
		buttondown = false;
		buttonup = false;
	}

	if (buttondown) {
		pressOnButton = true;
	}

	if (pressedAndReleased) {
		pressedAndReleased = false;
	}
	else if (pressOnButton && buttonup) {
		pressedAndReleased = true;
	}

	if (Mouse::get(Mouse::LEFT).released) {
		pressOnButton = false;
	}
}

void Button::update(float dt, std::function<void(void)> _callback) {
	bool lastPressed = pressed;
	bool lastReleased = released;

	hover = AABB(position - size * 0.5, position + size * 0.5).intersect(Mouse::getPosition());


	if (hover) {
		size = originalSize * enlargeFactor;

		pressed = Mouse::get(Mouse::LEFT).pressed;
		released = !pressed;
		buttondown = Mouse::get(Mouse::LEFT).buttondown && lastReleased;
		buttonup = Mouse::get(Mouse::LEFT).buttonup && lastPressed;

		if (buttondown && _callback) {
			_callback();
		}
	}
	else {
		size = originalSize;

		pressed = false;
		released = true;
		buttondown = false;
		buttonup = false;
	}

	if (buttondown) {
		pressOnButton = true;
	}

	if (pressedAndReleased) {
		pressedAndReleased = false;
	}
	else if (pressOnButton && buttonup) {
		pressedAndReleased = true;
	}

	if (Mouse::get(Mouse::LEFT).released) {
		pressOnButton = false;
	}
}

void Button::setSize(const vec2& _size) {
	originalSize = _size;
}
