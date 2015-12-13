#include "bonuses.h"

Bonuses::Bonuses(Image &image, String name, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
if (name == "healthPoint") {
		sprite.setTextureRect(IntRect(673, 2, 62, 62));
	}
dy = -STEP_BONUSES_ANIMATION;
startYPos = y;
}