#include "enemy.h"

void Enemy::Update(float time) {
	switch (EnemyAction) {
	case right:
		Move(1.f);
		break;
	case left:
		Move(-1.f);
		break;
	}
	if (health <= 0) {
		life = false;
		return;
	}
	if (name == "easyEnemy") {
		Animation(time);
		if (isMove) {
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x, y + h / 3);
		}
	}
	else if (name == "mediumEnemy") {
		if (isMove) {
			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}
}