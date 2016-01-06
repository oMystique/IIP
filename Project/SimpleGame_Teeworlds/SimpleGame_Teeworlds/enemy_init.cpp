#include "enemy.h"


Enemy::Enemy(Image &image, String name, Level lvl, FloatRect rect) : Entity(image, name, rect) {
	obj = lvl.GetObjects("stopEnemy"); //инициализируем.получаем нужные объекты для взаимодействия врага с картой 
	sprite.setPosition(rect.left, rect.top);
	isMove = true;
	isFight = false;
	currentFrame = 0;
	offset = { 0.f, 0.f };
	enemyDieBuffer.loadFromFile("sounds/catCrash.ogg");
	enemyDie.setBuffer(enemyDieBuffer);
	countFrames = ANIMATION_FRAME;
	if (name == "easyEnemy") {
		sprite.setTextureRect(IntRect(0, 0, EASY_ENEMY_RECT_BOUNDS.x, EASY_ENEMY_RECT_BOUNDS.y));
		action = stay;
	}
	else if (name == "mediumEnemy") {
		sprite.setTextureRect(IntRect(0, 0, MEDIUM_ENEMY_RECT_BOUNDS.x, MEDIUM_ENEMY_RECT_BOUNDS.y));
		sprite.setScale(MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
		countFrames *= GET_THIRD;
		sprite.setOrigin(sprite.getTextureRect().width / GET_HALF, DEFAULT_UNIT_BOUNDS.y);
	}
	else if (name == "hardEnemy") {
		sprite.setTextureRect(IntRect(0, 0, 300, 148));
		sprite.setOrigin(sprite.getTextureRect().width / GET_HALF, DEFAULT_UNIT_BOUNDS.y);
		action = stay;
	}
}
