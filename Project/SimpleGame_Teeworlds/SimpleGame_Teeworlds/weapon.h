#pragma once
#include "entity.h"

struct Weapon {
	Weapon(Image &image, String name, FloatRect rect);

	float shootEnemyTimer;
	bool shootEnemyFlag;
	bool shootPlayerFlag;
	Sprite playerWeaponSprite;

	void Update(float time, float rotation, Vector2f temp, String name);
private:
	Texture weaponsTexture;
	String name;
	float currentFrame;
	FloatRect rect;

	void Animation(float time);
};
