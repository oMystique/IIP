#pragma once
#include "player.h"

struct Weapon {
	Weapon(Image &image, String name, float x, float y, int w, int h);
	Image weaponsImage;
	float x, y;
	float shootEnemyTimer;
	bool shootEnemyFlag;
	int w, h;

	float currentFrame;
	bool shootPlayerFlag;

	Texture weaponsTexture;
	Sprite playerWeaponSprite;
	String name;

	void Update(float time, float rotation, float tempX, float tempY, String name);
	void Animation(float time);
};
