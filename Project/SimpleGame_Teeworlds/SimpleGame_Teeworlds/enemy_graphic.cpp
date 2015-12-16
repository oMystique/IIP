#include "enemy.h"


void Enemy::Animation(float time) {
	if (isFight) {
		sprite.setTexture(fightTexture);
	}
	else {
		sprite.setTexture(texture);
	}
	currentFrame += FRAME_CORRECTION*time;
	if (currentFrame > ANIMATION_FRAME) {
		currentFrame -= ANIMATION_FRAME;
		aX += EASY_ENEMY_RECT_BOUNDS.x;
	}
	if (aX > EASY_ENEMY_RECT_BOUNDS.x + 1) {
		aX = 0;
	}
	if (boost.x > 0) {
		sprite.setTextureRect(IntRect(aX, 0, EASY_ENEMY_RECT_BOUNDS.x, EASY_ENEMY_RECT_BOUNDS.y));
	}
	else {
		sprite.setTextureRect(IntRect(aX, 107, EASY_ENEMY_RECT_BOUNDS.x, EASY_ENEMY_RECT_BOUNDS.y));
	}
}