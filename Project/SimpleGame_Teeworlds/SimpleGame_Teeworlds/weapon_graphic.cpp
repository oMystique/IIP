#include "weapon.h"

void Weapon::Animation(float time) {
	if (shootPlayerFlag) {
		playerWeaponSprite.setTextureRect(IntRect(0, 0, 265, 68));
		currentFrame += 0.005*time;
		if (currentFrame > 0.5) {
			playerWeaponSprite.setTextureRect(IntRect(0, 68, 265, 68));
			currentFrame -= 0.5;
			shootPlayerFlag = false;
		}
	}
}