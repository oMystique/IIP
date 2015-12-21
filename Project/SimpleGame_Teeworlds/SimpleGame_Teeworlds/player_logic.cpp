#include "player.h"


void Player::Control(float &time) {
	ControlDirection();
	if (Keyboard::isKeyPressed(Keyboard::A)) {
			Animation(time);
			action = moveLeft;
			speed = 0.2;
		}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
			Animation(time);
			action = moveRight;
			speed = 0.2;
		}
	if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
			action = jump;
			boost.y = -PLAYER_JUMP_SPEED;
			onGround = false;
		}
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), int(PLAYER_SPRITE_BOUND), int(PLAYER_SPRITE_BOUND)));
}


void Player::CheckCollisionWithMap(float dX, float dY) {
	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			if (obj[i].name == "solid") {
				if (dY > 0) { rect.top = obj[i].rect.top - rect.height;  boost.y = 0; onGround = true; }
				if (dY < 0) { rect.top = obj[i].rect.top + obj[i].rect.height;   boost.y = 0; }
				if (dX > 0) { rect.left = obj[i].rect.left - rect.width; }
				if (dX < 0) { rect.left = obj[i].rect.left + obj[i].rect.width; }
			}
			else if ((obj[i].name == "finish") && (flag)) {
				missionComplete = true;
			}
		}
	}
}


void Player::ControlDirection() {
	if ((-QUARTER_CIRCLE <= weaponRotation) && (weaponRotation <= QUARTER_CIRCLE)) {
		offset.y = 0;
	}
	else {
		offset.y = PLAYER_SPRITE_BOUND;
	}
}
