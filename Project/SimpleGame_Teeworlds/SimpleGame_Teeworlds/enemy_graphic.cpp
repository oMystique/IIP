#include "enemy.h"


void Enemy::Animation(float time) {
	if (isFight) {
		offset.y = sprite.getTextureRect().height;
	}
	else {
		offset.y = 0;
		if (name != "mediumEnemy") {
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
	sprite.setTextureRect(IntRect(offset.x, offset.y, sprite.getTextureRect().width, sprite.getTextureRect().height));
}