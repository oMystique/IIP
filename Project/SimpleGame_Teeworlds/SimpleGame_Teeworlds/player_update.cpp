#include "player.h"


void Player::Update(float time) {
	Control(time);
	switch (action)
	{
	case moveRight: boost.x = speed; break;
	case moveLeft: boost.x = -speed; break;
	case jump: break;
	case stay: break;
	case down: boost.y = 0; break;
	}
	rect.left += boost.x*time;
	CheckCollisionWithMap(boost.x, 0);
	rect.top += boost.y*time;
	CheckCollisionWithMap(0, boost.y);
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_THIRD);
	if (health <= 0) {
		life = false;
	}
	if (!isMove) {
		speed = 0;
	}
	boost.y = boost.y + PLAYER_BOOST_CORRECTION*time;
}