#include "player.h"


void Player::DieAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > 0.6) {
		currentFrame -= 0.6;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > 1684) {
		life = false;
	}
	sprite.setTextureRect(IntRect(offset.x, offset.y, sprite.getTextureRect().width, sprite.getTextureRect().height));
}


void Player::Animation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > ANIMATION_FRAME) {
		offset.x += PLAYER_SPRITE_BOUND;
		currentFrame -= ANIMATION_FRAME;
	}
	if (offset.x > PLAYER_TEXTURE_RESOLUTION) {
		offset.x = 0;
	}
}

