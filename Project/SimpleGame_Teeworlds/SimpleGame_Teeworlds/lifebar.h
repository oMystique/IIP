#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {
	Lifebar(Image &image, Vector2f bounds);
	
	void Update(float const healthCount, float const armorCount, RenderWindow &window);
	void Draw(RenderWindow &window);
private:
	Sprite healthSprite;
	Sprite armorSprite;
};