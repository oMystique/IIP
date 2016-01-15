#include "player.h"


void Player::InitDie() {
	texture.loadFromFile(DIE_BIG_TEXTURE_PATH);
	sprite.setTextureRect(IntRect(0, 0, 111, 118));
	sprite.setOrigin(111 / 2, 90);
	sprite.setRotation(0);
	offset = { 0.f, 0.f };
	sprite.setScale(GET_HALF, GET_HALF);
	name = DIE;
	currentFrame = 0;
}


void Player::Update(float time) {
	if (name == DIE && onGround) {
		action = stay;
		DieAnimation(time);
	}
	else {
		if (health < BONUS_HEALTH) {
			InitDie();
		}
		else {
			SetUnitColor(sprite, dmgFrame, isDamaged, time);
			Control(time);
		}
	}
	SetPlayerAction();
	rect.left += boost.x*time;
	CheckCollisionWithMap(boost.x, 0);
	rect.top += boost.y*time;
	CheckCollisionWithMap(0, boost.y);
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_THIRD);
	if (!isMove) {
		speed = 0;
	}
	boost.y = boost.y + PLAYER_BOOST_CORRECTION*time;
	parachute->Update(sprite.getPosition());
}