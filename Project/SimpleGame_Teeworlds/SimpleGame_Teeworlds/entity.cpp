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
	isDamaged = false;
	sprite.setTexture(texture);
	sprite.setOrigin(rect.width / GET_HALF, rect.height / GET_HALF);
	sprite.setScale(ENTITY_BASE_SCALE, ENTITY_BASE_SCALE);
}

Entity::~Entity() {};

FloatRect Entity::getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(rect.left, rect.top, rect.width, rect.height);//эта ф-ция нужна для проверки столкновений 
}


FloatRect Entity::getEnemyView() {//ф-ция получения поля зрения врага.
	return FloatRect(rect.left, rect.top, rect.width + vec, rect.height);// vec вектор взгляда врага
}


void IsUnitDamaged(float &time, bool &isDamaged, Sprite &sprite, float &dmgFrame) {
	dmgFrame += ANIMATION_TIME_BOOST*time;
	if (dmgFrame > ANIMATION_FRAME) {
		isDamaged = false;
	}
}


void SetUnitColor(Sprite &sprite, float &dmgFrame, bool &isDamaged, float &time) {
	if (isDamaged) {
		sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 150));
		IsUnitDamaged(time, isDamaged, sprite, dmgFrame);
	}
	else {
		dmgFrame = 0;
		sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 255));
	}
}
