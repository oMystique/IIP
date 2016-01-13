#include "player.h"

void Player::InitDie() {
	texture.loadFromFile("images/unitDie.png");
	sprite.setTextureRect(IntRect(0, 0, 111, 118));
	sprite.setOrigin(111 / 2, 90);
	sprite.setRotation(0);
	offset = { 0.f, 0.f };
	sprite.setScale(3, 3);
	name = "die";
	currentFrame = 0;
}

void Player::Update(float time) {
	if (name == "die") {
		action = stay;
		DieAnimation(time);
	}
	else {
		if (health <= 0) {
			InitDie();
		}
		else {
			SetUnitColor(sprite, dmgFrame, isDamaged, time);
			Control(time);
		}
	}
	switch (action)
	{
	case moveRight: boost.x = speed; break;
	case moveLeft: boost.x = -speed; break;
	case jump: break;
	case stay: break;
	case down: boost.y = 0; break;
	}
	rect.left += boost.x*time;
	CheckCollisionWithMap(boost.x, 0);
	rect.top += boost.y*time;
	CheckCollisionWithMap(0, boost.y);
	sprite.setPosition(rect.left + rect.width / GET_HALF, rect.top + rect.height / GET_THIRD);
	if (!isMove) {
		speed = 0;
	}
	boost.y = boost.y + PLAYER_BOOST_CORRECTION*time;
	if (parachuteOpen) { //TODO
		parachuteSprite.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y); //^
		if (!parachuteOpenSound.getStatus()) {
			parachuteOpenSound.play();
		}
	} //^
	else {
		parachuteOpenSound.stop();
	}
}