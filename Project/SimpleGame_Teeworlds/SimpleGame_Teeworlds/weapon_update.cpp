#include "weapon.h"

void Weapon::Update(float time, float rotation, float tempX, float tempY, String name) {
	if ((-90.0 <= rotation) && (rotation <= 90.0)) {
		x = tempX + 32;
		y = tempY + 20;
		if (playerWeaponSprite.getScale().y < 0) {
			playerWeaponSprite.scale(1, -1);
		}
	}
	else {
		x = tempX + 25;
		y = tempY + 20;
		if (playerWeaponSprite.getScale().y > 0) {
			playerWeaponSprite.scale(1, -1);
		}
	}
	playerWeaponSprite.setPosition(x, y);
	playerWeaponSprite.setRotation(rotation);
}