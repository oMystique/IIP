#include "bullet.h"

Bullet::Bullet(Image &image, String name, Level lvl, FloatRect rect, Vector2f mousePos, float rotation) :Entity(image, name, rect) {
	temp = mousePos;
	boost.x = rect.left;
	boost.y = rect.top;
	obj = lvl.GetObjects("solid");
	sprite.setPosition(rect.left, rect.top);
	speed = DEFAULT_UNIT_SPEED / GET_HALF;
	life = true;
	sprite.setScale(BULLET_SCALE, BULLET_SCALE);
	if (name == "Bullet") {
		sprite.setRotation(rotation + QUARTER_CIRCLE);
		sprite.setTextureRect(PLAYER_BULLET_RECT);
	}
	else if (name == "enemyBullet") {
		sprite.setTextureRect(ENEMY_BULLET_RECT);
	}
}
