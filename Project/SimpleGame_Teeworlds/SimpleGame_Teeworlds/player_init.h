#pragma once
#include "entity.h"
#include "memory"

struct PlayerInit {
	bool flag; //TODO
	bool missionComplete; //TODO
	float armor;
	float weaponRotation;
	float currentFrame;
	Texture parachuteTexture; //_
	Sprite parachuteSprite; //TODO: REF;
	bool parachuteOpen;
	Vector2f offset;
	float dmgFrame;
};