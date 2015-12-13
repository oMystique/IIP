#include "player.h"


void Player::Update(float time) {
	Control(time);
	switch (action)
	{
	case moveRight: dx = speed; break;
	case moveLeft: dx = -speed; break;
	case jump: break;
	case stay: break;
	case down: dx = 0; break;
	}
	x += dx*time;
	CheckCollisionWithMap(dx, 0);
	y += dy*time;
	CheckCollisionWithMap(0, dy);
	sprite.setPosition(x + w / 2, y + h / 3);
	if (health <= 0) {
		life = false;
	}
	if (!isMove) {
		speed = 0;
	}
	dy = dy + 0.0015f*time;
}