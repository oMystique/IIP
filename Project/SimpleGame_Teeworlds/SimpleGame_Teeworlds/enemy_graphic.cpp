#include "enemy.h"


void Enemy::Animation(float time) {
	if (isFight) {
		offset.y = float(sprite.getTextureRect().height);
	}
	else {
		offset.y = 0;
		if (name != MEDIUM_ENEMY) {
			if (boost.x < 0) {
				if (sprite.getScale().x < 0) {
					sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
				}
			}
			else {
				if (sprite.getScale().x > 0) {
					sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
				}
			}
		}
	}
	currentFrame += FRAME_CORRECTION*time;
	if (currentFrame > countFrames) {
		currentFrame -= countFrames;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > sprite.getTextureRect().width + 1) {
		offset.x = 0;
	}
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), sprite.getTextureRect().width, sprite.getTextureRect().height));
}



void Enemy::DieAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > 0.6f) {
		currentFrame -= 0.6f;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > 1684.f) {
		life = false;
	}
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), sprite.getTextureRect().width, sprite.getTextureRect().height));
}