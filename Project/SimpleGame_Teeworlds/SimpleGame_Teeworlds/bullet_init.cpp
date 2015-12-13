#include "bullet.h"

Bullet::Bullet(Image &image, String name, Level lvl, float x, float y, int w, int h, float mouseX, float mouseY, float rotation) :Entity(image, name, x, y, w, h) {
	tempX = mouseX;
	tempY = mouseY;
	dx = x;
	dy = y;
	obj = lvl.GetObjects("solid");
	sprite.setPosition(x, y);
	speed = DEFAULT_UNIT_SPEED;
	life = true;
	sprite.setScale(BULLET_SCALE, BULLET_SCALE);
	if (name == "Bullet") {
		sprite.setRotation(rotation + QUARTER_CIRCLE);
		sprite.setTextureRect(IntRect(339, 394, 27, 48));
	}
	else if (name == "enemyBullet") {
		sprite.setTextureRect(IntRect(321, 271, 60, 36));
	}
}