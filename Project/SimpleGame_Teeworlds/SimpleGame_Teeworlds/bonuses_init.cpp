#include "bonuses.h"

Bonuses::Bonuses(Image &image, String name, FloatRect rect) :Entity(image, name, rect) {
	if (name == "healthPoint") {
		sprite.setTextureRect(BONUS_HP_RECT);
	}
	else if (name == "armorPoint") {
		sprite.setTextureRect(BONUS_ARM_RECT);
	}
	else if (name == "motionBonus") {
		sprite.scale(0.4, 0.4);
	}
	offset = { 0.f, 0.f };
	currentFrame = 0;
	boost.y = 0;
	startYPos = rect.top;
}