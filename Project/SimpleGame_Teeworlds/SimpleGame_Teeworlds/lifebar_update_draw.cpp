#include "lifebar.h"

void Lifebar::UpdatePlayerLifeBar(float const healthCount, float const armorCount, RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	float healthCounter = COUNT_PLAYER_HEALTH;
	float armorCounter = COUNT_PLAYER_HEALTH;
	while (healthCounter != 0) {
		if (healthCount < healthCounter) {
			healthSprite.setTextureRect(PLAYER_LIFEBAR_NO_HP_RECT);
		}
		else {
			healthSprite.setTextureRect(PLAYER_LIFEBAR_HP_RECT);
		}
		if (armorCount < armorCounter) {
			armorSprite.setTextureRect(PLAYER_LIFEBAR_NO_ARM_RECT);
		}
		else {
			armorSprite.setTextureRect(PLAYER_LIFEBAR_ARM_RECT);
		}
		healthCounter -= BONUS_HEALTH;
		armorCounter -= BONUS_HEALTH;
		healthSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y);
		armorSprite.setPosition(center.x + healthCounter / LIFEBAR_POS_CORRECTION.x, center.y - LIFEBAR_POS_CORRECTION.y + LIFEBAR_ARM_POS_CORRECTION);
		Draw(window);
	}
}


void Lifebar::UpdateEnemyLifeBar(float const healthCount, Vector2f const pos) {
	healthSprite.setTextureRect(IntRect(healthSprite.getTextureRect().left, healthSprite.getTextureRect().top, healthCount + 14, healthSprite.getTextureRect().height));
	healthSprite.setPosition(pos.x + 15, pos.y - 23);
	armorSprite.setPosition(pos.x + 15, pos.y - 23);
}


void Lifebar::Update(float const healthCount, float const armorCount, RenderWindow &window, Vector2f pos) {
	if (name == "player") {
		UpdatePlayerLifeBar(healthCount, armorCount, window);
	}
	else if (name == "enemy") {
		UpdateEnemyLifeBar(healthCount, pos);
		Draw(window);
	}
}


void Lifebar::Draw(RenderWindow &window) {
	window.draw(healthSprite);
	window.draw(armorSprite);
}