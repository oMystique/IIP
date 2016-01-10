#pragma once
#include "entity.h"

struct Bullet :public Entity {
	Bullet(Image &image, String name, Level lvl, FloatRect rect, Vector2f mouseCoord, float rotation);

	float currentFrame;
	float countFrames;
	float dmgFrame;
	Vector2f offset;

	void Update(float time);
	void DieAnimation(float time);
	void InitDie();
private:
	Vector2f temp;
};
