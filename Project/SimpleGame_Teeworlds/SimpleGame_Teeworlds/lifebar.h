#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {
	Sprite healthSprite;
	Sprite armorSprite;

	Lifebar(Image &image, int w, int h);
	
	void Update(float healthCount, float armorCount, RenderWindow &window);

	void Draw(RenderWindow &window);
};