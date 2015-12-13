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
	bool flag;
	bool missionComplete;
	float currentFrame;
	int aX;
	int aY;
	float weaponRotation;
};