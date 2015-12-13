#include "bonuses.h"


void Bonuses::Update(float time) {
	y += dy*time;
	if (y < startYPos - 10) {
		dy = STEP_BONUSES_ANIMATION;
	}
	else if (y > startYPos + 10) {
		dy = -STEP_BONUSES_ANIMATION;
	}
	sprite.setPosition(x, y);
}