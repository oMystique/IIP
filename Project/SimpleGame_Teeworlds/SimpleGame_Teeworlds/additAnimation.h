#pragma once
#include "resource.h"

struct AdditionalAnimation {
	AdditionalAnimation();

	Texture texture;
	Sprite sprite;

	float currentFrame;

	void EnemyAnimation();
	void BulletAnimation();
	void PlayerAnimation();

	void Update(float time, Vector2f pos);
};