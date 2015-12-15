#pragma once
#include "bullet.h"
#include "weapon.h"
#include <memory>

struct Enemy :public Entity {
public:
	enum {
		left,
		right,
		stay
	} EnemyAction;
	
	float currentFrame;
	int aX;
	Enemy(Image &image, String name, Level &lvl, float x, float y, int w, int h);

	Texture fightTexture; //TODO

	SoundBuffer enemyDieBuffer;
	Sound enemyDie;

	void Animation(float time);
	void Move(float direction);
	void checkCollisionWithMap(float dX, float dY);
	void Update(float time);
};