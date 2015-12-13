#include "player.h"


void Player::Control(float &time) {
	ControlDirection();
	if (Keyboard::isKeyPressed(Keyboard::A)) {
			Animation(time);
			action = moveLeft;
			speed = DEFAULT_UNIT_SPEED;
		}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
			Animation(time);
			action = moveRight;
			speed = DEFAULT_UNIT_SPEED;
		}
	if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
			action = jump;
			dy = -PLAYER_JUMP_SPEED;
			onGround = false;
		}
	sprite.setTextureRect(IntRect(aX, aY, 89, 89));
}


void Player::CheckCollisionWithMap(float dX, float dY) {
	for (int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			if (obj[i].name == "solid") {
				if (dY > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (dY < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (dX > 0) { x = obj[i].rect.left - w; }
				if (dX < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
			else if ((obj[i].name == "finish") && (flag)) {
				missionComplete = true;
			}
		}
	}
}


void Player::ControlDirection() {
	if ((-90.0f <= weaponRotation) && (weaponRotation <= 90.0f)) {
		aY = 0;
	}
	else {
		aY = 90;
	}
}
