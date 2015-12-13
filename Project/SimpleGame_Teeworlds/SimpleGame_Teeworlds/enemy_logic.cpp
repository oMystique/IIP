#include "enemy.h"

void Enemy::Move(float direction) {
	if (name == "easyEnemy") {
		dx = direction * DEFAULT_UNIT_SPEED * GET_HALF;
		vec = direction * ENEMY_VIEW_RANGE;
	}
}

void Enemy::checkCollisionWithMap(float dX, float dY) {
	for (int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) //проверяем пересечение игрока с объектом
		{
			if (dY > 0) {
				y = obj[i].rect.top - h;
				dy = 0;
				onGround = true;
			}
			if (dX > 0) {
				x = obj[i].rect.left - w;
				if (name == "easyEnemy") {
					dx = -DEFAULT_UNIT_SPEED;
				}
				EnemyAction = left;
			}
			else {
				x = obj[i].rect.left + obj[i].rect.width;
				if (name == "easyEnemy") {
					dx = DEFAULT_UNIT_SPEED;
				}
				EnemyAction = right;
			}
		}
	}
}
