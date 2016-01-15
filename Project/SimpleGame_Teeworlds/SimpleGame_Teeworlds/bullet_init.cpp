#include "bullet.h"

Bullet::Bullet(Image &image, String name, Level lvl, FloatRect rect, Vector2f mousePos, float rotation) :Entity(image, name, rect) {
	temp = mousePos;
	boost.x = rect.left;
	boost.y = rect.top;
	obj = lvl.GetObjects(SOLID_COLLISION);
	sprite.setPosition(rect.left, rect.top);
	speed = DEFAULT_BULLET_SPEED;
	sprite.setScale(BULLET_SCALE, BULLET_SCALE);
	if (name == PLAYER_BULLET) {
		sprite.setRotation(rotation + QUARTER_CIRCLE);
		sprite.setTextureRect(PLAYER_BULLET_RECT);
	}
	else if (name == ENEMY_BULLET) {
		sprite.setTextureRect(ENEMY_BULLET_RECT);
	}
}
