#pragma once
#include "memory"
#include "weapon.h"
#include "parachute.h"

struct PlayerInit {

	bool flag; 
	bool missionComplete; 
	float armor;
	float weaponRotation;

	unique_ptr<Parachute> parachute = nullptr;
};