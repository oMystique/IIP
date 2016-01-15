#include "world.h"
#define _USE_MATH_DEFINES
#include <math.h>


FloatRect GetSpriteRect(const Sprite sprite) {
	return FloatRect(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}


float GetRotation(Vector2f mousePos, Vector2f playerPos) {
	float dX = mousePos.x - playerPos.x;
	float dY = mousePos.y - playerPos.y;
	return float((atan2(dY, dX)) * GET_CIRCLE_HALF / M_PI);
}


bool IntersectsRects(FloatRect objectRect, FloatRect subjectRect) {
	return objectRect.intersects(subjectRect);
}


void CalculateShootTime(float &time, Weapon &playerWeapon) {
	if (playerWeapon.shootEnemyFlag) {
		if (playerWeapon.shootEnemyTimer < DEFAULT_ENEMY_SHOOT_SPEED) {
			playerWeapon.shootEnemyTimer += time;
		}
		else {
			playerWeapon.shootEnemyFlag = false;
		}
	}
}


void CheckPerfomMissionTarget(Player &player, Sprite &flagSprite, bool &missionTarget) {
	if (!missionTarget) {
		if (IntersectsRects(player.getRect(), GetSpriteRect(flagSprite))) {
			flagSprite.setScale(FLAG_MIN_SCALE, FLAG_MIN_SCALE);
			player.flag = true;
			missionTarget = true;
		}
	}
}


float GetDistance(FloatRect &subjectRect, FloatRect &objectRect) {
	return float(sqrt((objectRect.left - subjectRect.left)*(objectRect.left - subjectRect.left) + (objectRect.top - subjectRect.top)*(objectRect.top - subjectRect.top)));
}