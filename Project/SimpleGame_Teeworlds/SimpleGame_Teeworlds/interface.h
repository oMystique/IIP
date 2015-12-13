#pragma once
#include "enemy.h"

struct Interface {
	Texture texture;
	Sprite sprite;
	float x;
	float y;
	int w;
	int h;
	String name;

	Interface(Image &image, int w, int h);
	void Update(float time);
};