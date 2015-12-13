#include "entity.h"


Entity::Entity(Image &image, String Name, float X, float Y, int W, int H) {
	x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
	speed = 0;
	health = 100;
	dx = 0;
	dy = 0;
	texture.loadFromImage(image);
	life = true; onGround = false; isMove = false;
	sprite.setTexture(texture);
	sprite.setOrigin(float(w) / GET_HALF, float(h) / GET_HALF);
	sprite.setScale(ENTITY_BASE_SCALE, ENTITY_BASE_SCALE);
}


FloatRect Entity::getRect() {//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	return FloatRect(x, y, float(w), float(h));//��� �-��� ����� ��� �������� ������������ 
}


FloatRect Entity::getEnemyView() {//�-��� ��������� ���� ������ �����.
	return FloatRect(x, y, float(w) + vec, float(h));// vec ������ ������� �����
}
