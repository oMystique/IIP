#pragma once
#include "enemy.h"

struct Interface {
	Interface(Image &image, Vector2f bounds);

	Texture texture;
	Sprite sprite;
	/*float x;
	float y;
	int w;
	int h;*/
	FloatRect rect;
	String name;

	void Update(float time);
};