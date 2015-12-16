#include "bonuses.h"

void DontMoveWhileDownload(float &boostY) {
	if (boostY == 0) {
		boostY = -STEP_BONUSES_ANIMATION;
	}
}

void Bonuses::Update(float time) {
	rect.top += boost.y*time;
	if (rect.top < startYPos - BOUND_BONUS_ANIMATION) {
		boost.y = STEP_BONUSES_ANIMATION;
	}
	else if (rect.top > startYPos + BOUND_BONUS_ANIMATION) {
		boost.y = -STEP_BONUSES_ANIMATION;
	}
	sprite.setPosition(rect.left, rect.top);
	DontMoveWhileDownload(boost.y);
}