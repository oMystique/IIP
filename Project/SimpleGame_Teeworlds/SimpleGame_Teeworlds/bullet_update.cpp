#include "bullet.h"

void BulletTrackAnimation(RenderWindow &window, Entity &bullet, Sprite sprite) {
	float scale = rand() % 1;
	sprite.setTextureRect(IntRect(255, 34, 33, 29));
	sprite.setScale(scale, scale);
	sprite.setPosition(bullet.sprite.getPosition().x + rand() % 3, bullet.sprite.getPosition().y + rand() % 3);
	window.draw(sprite);
}

void Bullet::Update(float time) {
	float distance = sqrt((temp.x - boost.x)*(temp.x - boost.x) + (temp.y - boost.y)*(temp.y - boost.y));
	rect.left += speed * (temp.x - boost.x) / distance;
	rect.top += speed * (temp.y - boost.y) / distance;

	if (rect.left <= 0) rect.left = 1;
	if (rect.top <= 0) rect.top = 1;

	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			life = false;
		}
	}
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_HALF);
}