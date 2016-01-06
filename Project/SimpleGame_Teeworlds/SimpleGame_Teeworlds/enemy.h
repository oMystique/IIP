#pragma once
#include "bullet.h"
#include "weapon.h"

struct Enemy :public Entity {
public:
	float currentFrame;
	float countFrames;
	float dmgFrame;
	Vector2f offset;

	Enemy(Image &image, String name, Level lvl, FloatRect rect);

	SoundBuffer enemyDieBuffer;
	Sound enemyDie;

	void Animation(float time);
	void Move(float direction);
	void checkCollisionWithMap(float dX, float dY);
	void Update(float time);
	void DieAnimation(float time);
	void InitDie();
};