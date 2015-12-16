#include "bullet.h"


void Bullet::Update(float time) {
	rect.left += speed * (temp.x - boost.x);
	rect.top += speed * (temp.y - boost.y);

	if (rect.left <= 0) rect.left = 1;
	if (rect.top <= 0) rect.top = 1;

	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			life = false;
		}
	}
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_HALF);
}