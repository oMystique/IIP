#include "bullet.h"


void Bullet::Update(float time) {
	x += speed * (tempX - dx);
	y += speed * (tempY - dy);

	if (x <= 0) x = 1;
	if (y <= 0) y = 1;

	for (int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			life = false;
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}