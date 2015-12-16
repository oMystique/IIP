#pragma once
#include "interface.h"
#include "memory"

struct PlayerInit {
	enum {
		moveLeft,
		moveRight,
		jump,
		stay,
		down
	} action;
	bool flag; //TODO
	bool missionComplete; //TODO
	float armor;
	float weaponRotation;
	float currentFrame;
	/*int aX;
	int aY;*/
	Vector2f offset;
};