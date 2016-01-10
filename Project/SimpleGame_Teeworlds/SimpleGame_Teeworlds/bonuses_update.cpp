#include "bonuses.h"

void DontMoveWhileDownload(float &boostY) {
	if (boostY == 0) {
		boostY = -STEP_BONUSES_ANIMATION;
	}
}


void Bonuses::DieAnimation(float time) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > 0.6) {
		currentFrame -= 0.6;
		offset.x += sprite.getTextureRect().width;
	}
	if (offset.x > 600) {
		life = false;
	}
	sprite.setTextureRect(IntRect(offset.x, offset.y, sprite.getTextureRect().width, sprite.getTextureRect().height));
}

void Bonuses::InitDie() {
	texture.loadFromFile("images/die.png");
	sprite.setTextureRect(IntRect(111, 0, 111, 117));
	sprite.setOrigin(85 / 2, 117 / 2);
	sprite.setRotation(0);
	sprite.setScale(0.4, 0.4);
	offset = { 111.f, 0.f };
	name = "die";
	onGround = false;
	currentFrame = 0;
	speed = 0;
}


void Bonuses::Move() {
	if (rect.top < startYPos - BOUND_BONUS_ANIMATION) {
		boost.y = STEP_BONUSES_ANIMATION;
	}
	else if (rect.top > startYPos + BOUND_BONUS_ANIMATION) {
		boost.y = -STEP_BONUSES_ANIMATION;
	}
}


void Bonuses::Update(float time) {
	rect.top += boost.y*time;
	if (name == "die") {
		DieAnimation(time);
	}
	else if (health <= 0) {
		InitDie();
		return;
	}
	if (rect.top < startYPos - BOUND_BONUS_ANIMATION) {
		boost.y = STEP_BONUSES_ANIMATION;
	}
	else if (rect.top > startYPos + BOUND_BONUS_ANIMATION) {
		boost.y = -STEP_BONUSES_ANIMATION;
	}
	sprite.setPosition(rect.left, rect.top);
	DontMoveWhileDownload(boost.y);
}