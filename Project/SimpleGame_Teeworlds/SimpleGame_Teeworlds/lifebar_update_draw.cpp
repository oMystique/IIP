#include "lifebar.h"

void Lifebar::Update(float healthCount, float armorCount, RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	float healthCounter = COUNT_PLAYER_HEALTH;
	float armorCounter = COUNT_PLAYER_HEALTH;
	while (healthCounter != 0) {
		if (healthCount < healthCounter) {
			healthSprite.setTextureRect(IntRect(738, 2, 62, 62));
		}
		else {
			healthSprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
		if (armorCount < armorCounter) {
			armorSprite.setTextureRect(IntRect(738, 64, 62, 62));
		}
		else {
			armorSprite.setTextureRect(IntRect(673, 64, 62, 62));
		}
		healthCounter -= BONUS_HEALTH;
		armorCounter -= BONUS_HEALTH;
		healthSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y);
		armorSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y + 30);
		Draw(window);
	}
}

void Lifebar::Draw(RenderWindow &window) {
	window.draw(healthSprite);
	window.draw(armorSprite);
}