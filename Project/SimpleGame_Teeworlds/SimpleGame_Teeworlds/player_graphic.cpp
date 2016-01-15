#include "player.h"


void Player::DieAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > 0.6f) {
		currentFrame -= 0.6f;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > 1684.f) {
		life = false;
	}
	sprite.setColor(Color::White);
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), sprite.getTextureRect().width, sprite.getTextureRect().height));
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

