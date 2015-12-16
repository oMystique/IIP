#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {
	//Lifebar(Image &image, int w, int h);
	Lifebar(Image &image, Vector2f bounds);
	
	void Update(float healthCount, float armorCount, RenderWindow &window);
	void Draw(RenderWindow &window);
private:
	Sprite healthSprite;
	Sprite armorSprite;
};