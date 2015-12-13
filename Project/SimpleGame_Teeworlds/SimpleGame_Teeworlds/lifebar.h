#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {

	Lifebar(Image &image, int w, int h);
	
	void Update(float healthCount);

	void Draw(RenderWindow &window);

	//vector<Sprite> sprites;
};