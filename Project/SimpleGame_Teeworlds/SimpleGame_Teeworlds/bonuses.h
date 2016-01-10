#pragma once
#include "player.h"

struct Bonuses : public Entity {
	Bonuses(Image &image, String name, FloatRect rect);
	void Move();
	float currentFrame;
	Vector2f offset;
	void Update(float time);
private:
	float startYPos;
	void DieAnimation(float time);
	void InitDie();
};