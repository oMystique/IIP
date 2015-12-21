#include "bonuses.h"

Bonuses::Bonuses(Image &image, String name, FloatRect rect) :Entity(image, name, rect) {
	if (name == "healthPoint") {
		sprite.setTextureRect(BONUS_HP_RECT);
	}
	else if (name == "armorPoint") {
		sprite.setTextureRect(BONUS_ARM_RECT);
	}
	boost.y = 0;
	startYPos = rect.top;
}