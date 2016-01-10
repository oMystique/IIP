#include "enemy.h"


void Enemy::InitDie() {
	texture.loadFromFile("images/unitDie.png");
	sprite.setTextureRect(IntRect(0, 0, 111, 118));
	sprite.setOrigin(85 / 2, 117 / 2);
	sprite.setRotation(0);
	sprite.setScale(0.5, 0.5);
	offset = { 0.f, 0.f };
	name = "diedEnemy";
	onGround = false;
	currentFrame = 0;
}


void Enemy::Update(float time) {
	SetUnitColor(sprite, dmgFrame, isDamaged, time);
	switch (action) {
	case moveRight:
		Move(1.f);
		break;
	case moveLeft:
		Move(-1.f);
		break;
	case stay:
		Move(0.f);
		break;
	}
	if (name == "diedEnemy") {
		if (!onGround) {
			boost.y = DEFAULT_UNIT_SPEED;
			rect.top += boost.y*time;
			checkCollisionWithMap(0, boost.y);
			sprite.setPosition(rect.left, rect.top + rect.height / GET_HALF);
		}
		else {
			DieAnimation(time);
		}
	}
	else if (health <= 0) {
		enemyDie.play();
		InitDie();
		return;
	}
	if ((name == "easyEnemy") || (name == "hardEnemy")) {
		Animation(time);
		if (isMove) {
			rect.left += boost.x*time;
			if (!onGround) {
				checkCollisionWithMap(boost.x, 0);
			}
			sprite.setPosition(rect.left + rect.width / GET_FOURTH, rect.top + rect.height / GET_THIRD);
			if (boost.x == 0) {
				action = moveRight;
			}
		}
	}
	else if (name == "mediumEnemy") {
		Animation(time);
		sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_HALF);
	}
}