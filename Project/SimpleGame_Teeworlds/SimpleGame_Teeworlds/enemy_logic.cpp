#include "enemy.h"


void Enemy::Move(float direction) {
	if ((name == EASY_ENEMY) || ((name == HARD_ENEMY))) {
		if (sprite.getColor() == (Color::Red)) {
			boost.x = direction * DEFAULT_UNIT_SPEED * GET_FOURTH;
		}
		else {
			boost.x = direction * DEFAULT_UNIT_SPEED;
		}
		if (onGround) {
			boost.x = direction * HARD_ENEMY_BOOST_SPEED;
		}
		vec = direction * ENEMY_VIEW_RANGE;
	}
}


void Enemy::checkCollisionWithMap(float dX, float dY) {
	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			if (dY != 0) {
				boost.y = 0;
				rect.top = obj[i].rect.top - obj[i].rect.height;
				onGround = true;
			}
			if (dX > 0) {
				rect.left = obj[i].rect.left - rect.width;
				boost.x = -DEFAULT_UNIT_SPEED;
				action = moveLeft;
			}
			else if (dX < 0) {
				rect.left = obj[i].rect.left + obj[i].rect.width;
				boost.x = DEFAULT_UNIT_SPEED;
				action = moveRight;
			}
		}
	}
}
