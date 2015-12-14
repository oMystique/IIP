#include "weapon.h"


Weapon::Weapon(Image &image, String name, float x, float y, int w, int h) {
	weaponsImage.loadFromFile("images/weapons.png");
	weaponsTexture.loadFromImage(weaponsImage);
	playerWeaponSprite.setScale(WEAPON_SCALE, WEAPON_SCALE);
	shootTimer = DEFAULT_ENEMY_SHOOT_SPEED;
	shootFlag = false;

	if (name == "playerWeapon") {
		playerWeaponSprite.setTexture(weaponsTexture);
		playerWeaponSprite.setTextureRect(IntRect(66, 194, 227, 60));
		playerWeaponSprite.setPosition(x, y);
	}
}

