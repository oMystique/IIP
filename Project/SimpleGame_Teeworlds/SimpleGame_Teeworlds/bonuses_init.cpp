#include "bonuses.h"

Bonuses::Bonuses(Image &image, String name, FloatRect rect) :Entity(image, name, rect) {
	if (name == HEALTH_BONUS) {
		sprite.setTextureRect(BONUS_HP_RECT);
	}
	else if (name == ARMOR_BONUS) {
		sprite.setTextureRect(BONUS_ARM_RECT);
	}
	else if (name == MOTION_BONUS) {
		sprite.scale(ENTITY_BASE_SCALE, ENTITY_BASE_SCALE);
	}
	boost.y = 0;
	startYPos = rect.top;
}