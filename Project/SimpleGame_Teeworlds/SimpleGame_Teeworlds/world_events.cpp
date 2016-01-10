#include "world.h"
#define _USE_MATH_DEFINES
#include <math.h>


FloatRect GetSpriteRect(Sprite sprite) {
	return FloatRect(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

float World::GetRotation(Vector2f mousePos, Vector2f playerPos) {
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


float GetDistance(Player &player, Entity &enemy) {
	return float(sqrt((player.rect.left - enemy.rect.left)*(player.rect.left - enemy.rect.left) + (player.rect.top - enemy.rect.top)*(player.rect.top - enemy.rect.top)));
}



void World::InteractObjects(float time) {
	float distance = 0;
	CalculateShootTime(time, *playerWeapon);
	CheckPerfomMissionTarget(*player, flagSprite, missionTarget);
	for (Entity *&subject : entities) {
		for (Entity *&object : entities) {
			if (IntersectsRects(subject->getRect(), object->getRect()) && ((object->name == "Bullet") && (((subject->name == "easyEnemy") || (subject->name == "mediumEnemy") || (subject->name == "hardEnemy"))))) {
				PlayerShootAtEnemy(*object, *subject, *player, missSound);
			}
		}
		if ((subject->name == "easyEnemy") || (subject->name == "mediumEnemy") || (subject->name == "enemyBullet") || (subject->name == "hardEnemy")) {
			if ((subject->name == "mediumEnemy") || (subject->name == "hardEnemy")) {
				distance = GetDistance(*player, *subject);
			}
			if (IntersectsRects(subject->getRect(), player->getRect()) || ((subject->name == "hardEnemy") && (distance <= ENEMY_VIEW_RANGE))) {
				if (subject->name == "hardEnemy") {
					ActHardEnemy(*player, *subject, distance, kickHit, time);
				}
				else {
					EnemyDamagedPlayer(kickHit, *subject, *player, time);
				}
			}
			else {
				subject->isMove = true;
				subject->onGround = false;
				if (((IntersectsRects(subject->getEnemyView(), player->getRect())) && (subject->name == "easyEnemy")) || ((ENEMY_VIEW_RANGE > distance) && (subject->name == "mediumEnemy"))) {
					if (subject->name == "mediumEnemy") {
						FightRotateMediumEnemy(*subject, GetRotation({ player->rect.left, player->rect.top }, { subject->rect.left, subject->rect.top }));
						if (playerWeapon->shootEnemyTimer > DEFAULT_ENEMY_SHOOT_SPEED / GET_HALF) {
							EnemyShootAtPlayer(lvl, *subject, *player, entities, *playerWeapon, bulletImage);
							break;
						}
					}
					if (subject->name == "easyEnemy") {
						subject->sprite.setColor(Color::Red);
					}
				}
				else {
					subject->sprite.setColor(Color::White);
					subject->sprite.setRotation(0);
					subject->isFight = false;
				}
			}
		}
		else if ((subject->name == "healthPoint") && (subject->getRect().intersects(player->getRect()) && (player->health < COUNT_PLAYER_HEALTH))) {
			player->health += BONUS_HEALTH;
			subject->health = 0;
		}
		else if ((subject->name == "armorPoint") && (subject->getRect().intersects(player->getRect()) && (player->armor < COUNT_PLAYER_HEALTH))) {
			player->armor += BONUS_HEALTH;
			subject->health = 0;
		}
		else if ((subject->name == "motionBonus") && (subject->getRect().intersects(player->getRect()))) {
			subject->health = 0;
			slowMotionBar->SetParameterForMotion();
		}
	}
}


void World::ShootEvent(Vector2f mousePos) {
	PlayerShoot(mousePos, *playerWeapon, shoot, entities, bulletImage, lvl, sightSprite);
}