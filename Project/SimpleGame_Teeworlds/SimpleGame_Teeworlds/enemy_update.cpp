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
		enemyDie.play();
		return;
	}
	if (name == "easyEnemy") {
		Animation(time);
		if (isMove) {
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + w / 4, y + h / 3);
		}
	}
	else if (name == "mediumEnemy") {
		sprite.setPosition(x + w / 2, y + h / 2);
	}
}