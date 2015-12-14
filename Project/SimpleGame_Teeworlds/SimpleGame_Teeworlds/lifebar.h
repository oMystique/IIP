#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {

	Lifebar(Image &image, int w, int h);
	
	void Update(float healthCount, RenderWindow &window);

	void Draw(RenderWindow &window);

	//vector<Sprite> sprites;
};