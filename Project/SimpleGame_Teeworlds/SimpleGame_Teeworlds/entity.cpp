#include "entity.h"


Entity::Entity(Image &image, String Name, FloatRect Rect) {
	rect = Rect;
	name = Name;
	speed = 0;
	health = BONUS_HEALTH;
	boost = { 0.f, 0.f };
	texture.loadFromImage(image);
	life = true;
	onGround = false;
	isMove = false;
	isDamaged = false;
	sprite.setTexture(texture);
	sprite.setOrigin(rect.width / GET_HALF, rect.height / GET_HALF);
	sprite.setScale(ENTITY_BASE_SCALE, ENTITY_BASE_SCALE);
	currentFrame = 0;
	countFrames = 0;
	dmgFrame = 0;
	offset = { 0.f, 0.f };
}

Entity::~Entity() {};

FloatRect Entity::getRect() {//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	return FloatRect(rect.left, rect.top, rect.width, rect.height);//��� �-��� ����� ��� �������� ������������ 
}


FloatRect Entity::getEnemyView() {//�-��� ��������� ���� ������ �����.
	return FloatRect(rect.left, rect.top, rect.width + vec, rect.height);// vec ������ ������� �����
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
