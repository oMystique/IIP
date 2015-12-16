#include "weapon.h"


Weapon::Weapon(Image &image, String name, FloatRect rect) {
	weaponsTexture.loadFromImage(image);
	playerWeaponSprite.setScale(WEAPON_SCALE, WEAPON_SCALE);
	shootEnemyTimer = DEFAULT_ENEMY_SHOOT_SPEED;
	shootEnemyFlag = false;
	currentFrame = 0;
	shootPlayerFlag = false;

	if (name == "playerWeapon") {
		playerWeaponSprite.setTexture(weaponsTexture);
		playerWeaponSprite.setTextureRect(IntRect(0, 68, 265, 68));
		playerWeaponSprite.setPosition(rect.left, rect.top);
	}
}

