#pragma once
#include "player.h"

struct Weapon {
	Weapon(Image &image, String name, FloatRect rect);
	Image weaponsImage;
	//float x, y;
	float shootEnemyTimer;
	bool shootEnemyFlag;
	//int w, h;
	FloatRect rect;
	float currentFrame;
	bool shootPlayerFlag;

	Texture weaponsTexture;
	Sprite playerWeaponSprite;
	String name;

	void Update(float time, float rotation, Vector2f temp, String name);
	void Animation(float time);
};
