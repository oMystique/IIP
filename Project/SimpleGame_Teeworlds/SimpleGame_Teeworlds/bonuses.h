#pragma once
#include "player.h"

struct Bonuses : public Entity {
	Bonuses(Image &image, String name, FloatRect rect);
	void Update(float time);
private:
	float startYPos;
};