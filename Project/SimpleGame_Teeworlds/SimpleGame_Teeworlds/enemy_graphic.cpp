#include "enemy.h"


void Enemy::Animation(float time) {
	currentFrame += FRAME_CORRECTION*time;
	if (currentFrame > 1) {
		currentFrame -= 1;
		aX += 149;
	}
	if (aX > 150) {
		aX = 0;
	}
	if (dx > 0) {
		sprite.setTextureRect(IntRect(aX, 0, 149, 103));
	}
	else {
		sprite.setTextureRect(IntRect(aX, 107, 149, 103));
	}
}