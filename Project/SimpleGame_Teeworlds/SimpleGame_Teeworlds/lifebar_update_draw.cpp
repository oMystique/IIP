#include "lifebar.h"
#include <iostream>

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


void Lifebar::SetParameterForMotion() {
	healthSprite.setTextureRect(IntRect(4, 16, 114, 8)); 
}

bool Lifebar::IsBurnMotionParameter(float time) {
	if (healthSprite.getTextureRect().width > 0) {
		currentFrame += ANIMATION_TIME_BOOST*time;
		healthSprite.setScale(BURN_MOTION_SPRITE_SCALE, BURN_MOTION_SPRITE_SCALE);
		armorSprite.setScale(BURN_MOTION_SPRITE_SCALE, BURN_MOTION_SPRITE_SCALE);
		if (currentFrame > ANIMATION_FRAME) {
			currentFrame -= ANIMATION_FRAME;
			healthSprite.setTextureRect(IntRect(healthSprite.getTextureRect().left, healthSprite.getTextureRect().top, int(healthSprite.getTextureRect().width * 0.95f), healthSprite.getTextureRect().height));
			healthSprite.setScale(1, 1);
			armorSprite.setScale(1, 1);
		}
		return true;
	}
	else {
		return false;
	}
}


void Lifebar::UpdateSlowMotionBar(RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	healthSprite.setTextureRect(IntRect(healthSprite.getTextureRect().left, healthSprite.getTextureRect().top, healthSprite.getTextureRect().width, healthSprite.getTextureRect().height));
	healthSprite.setPosition(center.x + 360.f, center.y + 190.f);
	armorSprite.setPosition(center.x + 360.f, center.y + 190.f);
}

void Lifebar::UpdateEnemyLifeBar(float const healthCount, Vector2f const pos) {
	healthSprite.setTextureRect(IntRect(healthSprite.getTextureRect().left, healthSprite.getTextureRect().top, int(healthCount + 14), healthSprite.getTextureRect().height));
	healthSprite.setPosition(pos.x + 15.f, pos.y - 23.f);
	armorSprite.setPosition(pos.x + 15.f, pos.y - 23.f);
}


void Lifebar::Update(float const healthCount, float const armorCount, RenderWindow &window, Vector2f pos) {
	if (name == PLAYER_BAR) {
		UpdatePlayerLifeBar(healthCount, armorCount, window);
	}
	else if (name == ENEMY_BAR) {
		UpdateEnemyLifeBar(healthCount, pos);
		Draw(window);
	}
	else if (name == MOTION_BAR) {
		UpdateSlowMotionBar(window);
		Draw(window);
	}
}


void Lifebar::Draw(RenderWindow &window) {
	window.draw(healthSprite);
	window.draw(armorSprite);
}