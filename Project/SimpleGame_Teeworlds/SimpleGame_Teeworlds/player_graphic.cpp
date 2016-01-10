#include "player.h"

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

