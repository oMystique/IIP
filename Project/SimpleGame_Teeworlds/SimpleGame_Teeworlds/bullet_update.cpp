#include "bullet.h"


void Bullet::DieAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > 0.6) {
		currentFrame -= 0.6;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > 600) {
		life = false;
	}
	sprite.setTextureRect(IntRect(offset.x, offset.y, sprite.getTextureRect().width, sprite.getTextureRect().height));
}

void Bullet::InitDie() {
	texture.loadFromFile("images/die.png");
	sprite.setTextureRect(IntRect(111, 0, 111, 117));
	sprite.setOrigin(85 / 2, 117 / 2);
	sprite.setRotation(0);
	sprite.setScale(0.2, 0.2);
	if (name == "Bullet") {
		sprite.setColor(Color::Blue);
	}
	else {
		sprite.setColor(Color::Red);
	}
	offset = { 111.f, 0.f };
	name = "die";
	onGround = false;
	currentFrame = 0;
	speed = 0;
}


void Bullet::Update(float time) {
	if (name == "die") {
		DieAnimation(time);
	}
	else if (health <= 0) {
		InitDie();
		return;
	}
	if (speed == DEFAULT_BULLET_SPEED) {
		speed = time;
	}
	float distance = sqrt((temp.x - boost.x)*(temp.x - boost.x) + (temp.y - boost.y)*(temp.y - boost.y));
	rect.left += (temp.x - boost.x) / distance * speed * GET_HALF;
	rect.top +=  (temp.y - boost.y) / distance * speed * GET_HALF;

	if (rect.left <= 0) rect.left = 1;
	if (rect.top <= 0) rect.top = 1;

	for (unsigned int i = 0; i < obj.size(); i++) {
		if (getRect().intersects(obj[i].rect)) {
			health = 0;
		}
	}
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_HALF);
}