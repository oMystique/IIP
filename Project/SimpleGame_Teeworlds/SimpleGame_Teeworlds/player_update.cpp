#include "player.h"

void IsDamaged(float &time, bool &isDamaged, Sprite &sprite, float &currentFrame) {
	currentFrame += ANIMATION_TIME_BOOST*time;
	if (currentFrame > ANIMATION_FRAME) {
		isDamaged = false;
	}
}


void Player::Update(float time) {
	if (!isDamaged) {
		dmgFrame = 0;
		sprite.setColor(Color::White);
	}
	else {
		IsDamaged(time, isDamaged, sprite, dmgFrame);
		sprite.setColor(Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, 150));
	}
	Control(time);
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
	if (health <= 0) {
		life = false;
		missionComplete = true;
	}
	if (!isMove) {
		speed = 0;
	}
	boost.y = boost.y + PLAYER_BOOST_CORRECTION*time;
	if (parachuteOpen) { //TODO
		parachuteSprite.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y); //^
	} //^
}