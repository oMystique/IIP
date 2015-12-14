#include "lifebar.h"

void Lifebar::Update(float healthCount, RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	float counter = COUNT_PLAYER_HEALTH;
	while (counter != 0) {
		if (healthCount < counter) {
			sprite.setTextureRect(IntRect(738, 2, 62, 62));
		}
		else {
			sprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
		counter -= BONUS_HEALTH;
		sprite.setPosition(center.x + counter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y);
		Draw(window);
	}
}

void Lifebar::Draw(RenderWindow &window) {
	window.draw(sprite);
}