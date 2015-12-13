#pragma once
#include "enemy.h"

struct PickUpObj : public Entity {
public:
	PickUpObj(Image &image, String name, float x, float y, int w, int h);
	void Update(float time);
};