#pragma once
#include "resource.h"

struct Interface {
	Interface(Image &image, Vector2f bounds);

	Texture texture;
	Sprite sprite;
	FloatRect rect;
	String name;

	void Update(float time);
};