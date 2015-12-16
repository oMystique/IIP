#include "enemy.h"
#include <iostream>

Enemy::Enemy(Image &image, String name, Level lvl, FloatRect rect) : Entity(image, name, rect) {
	obj = lvl.GetObjects("stopEnemy"); //инициализируем.получаем нужные объекты для взаимодействия врага с картой
	fightTexture.loadFromFile("images/easyFight.png"); // TODO
	sprite.setPosition(rect.left, rect.top);
	isMove = true;
	isFight = false;
	currentFrame = 0;
	enemyDieBuffer.loadFromFile("sounds/catCrash.ogg");
	enemyDie.setBuffer(enemyDieBuffer);
	aX = 0;
	if (name == "easyEnemy") {
		sprite.setTextureRect(IntRect(aX, 0, EASY_ENEMY_RECT_BOUNDS.x, EASY_ENEMY_RECT_BOUNDS.y));
		EnemyAction = stay;
	}
	else if (name == "mediumEnemy") {
		sprite.setTextureRect(IntRect(0, 0, MEDIUM_ENEMY_RECT_BOUNDS.x, MEDIUM_ENEMY_RECT_BOUNDS.y));
		sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
	}
}
