#include "weapon.h"

void Weapon::Animation(float time) {
	if (shootPlayerFlag) {
		playerWeaponSprite.setTextureRect(WEAPON_SHOOT_RECT);
		currentFrame += ANIMATION_TIME_BOOST*time;
		if (currentFrame > WEAPON_ANIMATION_FRAME) {
			playerWeaponSprite.setTextureRect(WEAPON_NO_SHOOT_RECT);
			currentFrame -= WEAPON_ANIMATION_FRAME;
			shootPlayerFlag = false;
		}
	}
}