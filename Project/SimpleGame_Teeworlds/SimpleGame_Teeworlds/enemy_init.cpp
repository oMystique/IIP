#include "enemy.h"
#include <iostream>

Enemy::Enemy(Image &image, String name, Level &lvl, float x, float y, int w, int h) : Entity(image, name, x, y, w, h) {
	obj = lvl.GetObjects("stopEnemy"); //инициализируем.получаем нужные объекты для взаимодействия врага с картой
	sprite.setPosition(x, y);
	isMove = true;
	currentFrame = 0;
	aX = 0;
	if (name == "easyEnemy") {
		sprite.setTextureRect(IntRect(aX, 0, 149, 103));
		dx = DEFAULT_UNIT_SPEED;
	}
	else if (name == "mediumEnemy") {
		sprite.setTextureRect(IntRect(0, 0, 244, 230));
		sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
	}
}
