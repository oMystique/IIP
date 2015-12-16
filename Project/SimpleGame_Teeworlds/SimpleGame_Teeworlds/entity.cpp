#include "entity.h"


Entity::Entity(Image &image, String Name, FloatRect Rect) {
	rect = Rect;
	name = Name;
	moveTimer = 0;
	speed = 0;
	health = 100.f;
	boost = { 0.f, 0.f };
	texture.loadFromImage(image);
	life = true;
	onGround = false;
	isMove = false;
	sprite.setTexture(texture);
	sprite.setOrigin(rect.width / GET_HALF, rect.height / GET_HALF);
	sprite.setScale(ENTITY_BASE_SCALE, ENTITY_BASE_SCALE);
}


FloatRect Entity::getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(rect.left, rect.top, rect.width, rect.height);//эта ф-ция нужна для проверки столкновений 
}


FloatRect Entity::getEnemyView() {//ф-ция получения поля зрения врага.
	return FloatRect(rect.left, rect.top, rect.width + vec, rect.height);// vec вектор взгляда врага
}
