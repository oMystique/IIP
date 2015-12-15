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
	float currentFrame;
	int aX;
	int aY;
	float weaponRotation;
};