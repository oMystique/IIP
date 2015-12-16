#include "weapon.h"

void Weapon::Update(float time, float rotation, Vector2f temp, String name) {
	Animation(time);
	if ((-QUARTER_CIRCLE <= rotation) && (rotation <= QUARTER_CIRCLE)) {
		rect.left = temp.x + WEAPON_CORRECTION_COORD_X.x;
		rect.top = temp.y + WEAPON_CORRECTION_COORD_Y;
		if (playerWeaponSprite.getScale().y < 0) {
			playerWeaponSprite.scale(1, -1);
		}
	}
	else {
		rect.left = temp.x + WEAPON_CORRECTION_COORD_X.y;
		rect.top = temp.y + WEAPON_CORRECTION_COORD_Y;
		if (playerWeaponSprite.getScale().y > 0) {
			playerWeaponSprite.scale(1, -1);
		}
	}
	playerWeaponSprite.setPosition(rect.left, rect.top);
	playerWeaponSprite.setRotation(rotation);
}