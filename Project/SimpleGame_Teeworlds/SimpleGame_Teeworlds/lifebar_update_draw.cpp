#include "lifebar.h"

void Lifebar::Update(float healthCount, float armorCount, RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	float healthCounter = COUNT_PLAYER_HEALTH;
	float armorCounter = COUNT_PLAYER_HEALTH;
	while (healthCounter != 0) {
		if (healthCount < healthCounter) {
			healthSprite.setTextureRect(LIFEBAR_NO_HP_RECT);
		}
		else {
			healthSprite.setTextureRect(LIFEBAR_HP_RECT);
		}
		if (armorCount < armorCounter) {
			armorSprite.setTextureRect(LIFEBAR_NO_ARM_RECT);
		}
		else {
			armorSprite.setTextureRect(LIFEBAR_ARM_RECT);
		}
		healthCounter -= BONUS_HEALTH;
		armorCounter -= BONUS_HEALTH;
		healthSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y);
		armorSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y + LIFEBAR_ARM_POS_CORRECTION);
		Draw(window);
	}
}

void Lifebar::Draw(RenderWindow &window) {
	window.draw(healthSprite);
	window.draw(armorSprite);
}