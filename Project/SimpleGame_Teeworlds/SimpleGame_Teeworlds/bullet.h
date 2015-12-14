#pragma once
#include "entity.h"

struct Bullet :public Entity {
	Bullet(Image &image, String name, Level lvl, float x, float y, int w, int h, float mouseX, float mouseY, float rotation);
	void Update(float time);
private:
	float tempX, tempY;
};