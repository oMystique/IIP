#include "player.h"

void Player::Animation(float time) {
	currentFrame += 0.005*time;
	if (currentFrame > 1) {
		aX += 90;
		currentFrame -= 1;
	}
	if (aX > 179) {
		aX = 0;
	}
}