#pragma once
#include "player_init.h"

struct Player: public Entity, PlayerInit  {
	Player(Image &image, String name, Level lvl, FloatRect rect);
	void Update(float time);
private:
	void ControlDirection();
	void Control(float &time);
	void CheckCollisionWithMap(float dX, float dY);
	void Animation(float time);
};