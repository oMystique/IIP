#include "enemy.h"

void Enemy::Update(float time) {
	switch (EnemyAction) {
	case right:
		Move(1.f);
		break;
	case left:
		Move(-1.f);
		break;
	case stay:
		Move(0.f);
		break;
	}
	if (health <= 0) {
		life = false;
		enemyDie.play();
		return;
	}
	if ((name == "easyEnemy") || (name == "hardEnemy")) {
		Animation(time);
		if (isMove) {
			rect.left += boost.x*time;
			checkCollisionWithMap(boost.x, 0);
			sprite.setPosition(rect.left + rect.width / GET_FOURTH, rect.top + rect.height / GET_THIRD);
			if (boost.x == 0) {
				EnemyAction = right;
			}
		}
	}
	else if (name == "mediumEnemy") {
		Animation(time);
		sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_HALF);
	}
}