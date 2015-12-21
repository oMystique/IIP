#include "enemy.h"


void Enemy::Move(float direction) {
	if ((name == "easyEnemy") || ((name == "hardEnemy"))) {
		if (sprite.getColor() == (Color::Red)) {
			boost.x = direction * DEFAULT_UNIT_SPEED * GET_FOURTH;
		}
		else {
			boost.x = direction * DEFAULT_UNIT_SPEED;
		}
		vec = direction * ENEMY_VIEW_RANGE;
	}
}

void Enemy::checkCollisionWithMap(float dX, float dY) {
	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) //проверяем пересечение игрока с объектом
		{
			if (dX > 0) {
				rect.left = obj[i].rect.left - rect.width;
				boost.x = -DEFAULT_UNIT_SPEED;
				EnemyAction = left;
			}
			else {
				rect.left = obj[i].rect.left + obj[i].rect.width;
				boost.x = DEFAULT_UNIT_SPEED;
				EnemyAction = right;
			}
		}
	}
}
