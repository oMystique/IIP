#include "world.h"


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


void World::InteractObjects(float time) {
	float distance = 0;
	CalculateShootTime(time, *playerWeapon);
	for (it = entities.begin(); it != entities.end(); it++) {
		for (at = entities.begin(); at != entities.end(); at++) {
			if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy")))) {
				if (((*it)->name == "easyEnemy") && (177 > player->weaponRotation) && (player->weaponRotation > 3)) {
					missSound.play();
					(*at)->speed = -(*at)->speed;
				}
				else {
					(*it)->health -= 20;
					(*at)->life = false;
				}
			}
		}
		if (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy") || ((*it)->name == "enemyBullet")) {
			if ((*it)->name == "mediumEnemy") {
				distance = sqrt((player->x - (*it)->x)*(player->x - (*it)->x) + (player->y - (*it)->y)*(player->y - (*it)->y));
			}
			if ((*it)->getRect().intersects(player->getRect())) {
				(*it)->isMove = false;
				if (!kickHit.getStatus()) {
					kickHit.play();
				}
				if ((*it)->name == "enemyBullet") {
					if (player->armor > 0) {
						player->health -= 50;
						player->armor -= 100;
					}
					else {
						player->health -= 100;
					}
					(*it)->life = false;
				}
				else {
					player->health -= 4;
					player->armor -= 7;
				}
			}
			else {
				(*it)->isMove = true;
				if ((((*it)->getEnemyView().intersects(player->getRect())) && ((*it)->name == "easyEnemy")) || ((ENEMY_VIEW_RANGE > distance) && ((*it)->name == "mediumEnemy"))) {
					if ((*it)->name == "mediumEnemy") {
						if (((*it)->sprite.getScale().x > 0) && ((*it)->sprite.getPosition().x > player->sprite.getPosition().x)) {
							(*it)->sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
						}
						else if (((*it)->sprite.getScale().x < 0) && ((*it)->sprite.getPosition().x < player->sprite.getPosition().x)) {
							(*it)->sprite.setScale(MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
						}
						if (playerWeapon->shootEnemyTimer > DEFAULT_ENEMY_SHOOT_SPEED / GET_HALF) {
							entities.push_back(new Bullet(bulletImage,"enemyBullet", lvl,
								(*it)->x, (*it)->y + 10, 24, 23,
								player->x + 11, player->y + 11,
								(*it)->sprite.getRotation()));
							playerWeapon->shootEnemyFlag = true;
							playerWeapon->shootEnemyTimer = 0;
							break;
						}
					}
					(*it)->sprite.setColor(Color::Red);
				}
				else {
					(*it)->sprite.setColor(Color::White);
				}
			}
		}
		else if (((*it)->name == "healthPoint") && ((*it)->getRect().intersects(player->getRect()) && (player->health < COUNT_PLAYER_HEALTH))) {
			player->health += BONUS_HEALTH;
			(*it)->life = false;
		}
	}
}


void World::Shoot(String subject, float mouseX, float mouseY) {
	if (subject == "player") {
		shoot.play();
		entities.push_back(new Bullet(bulletImage, "Bullet", lvl,
			playerWeapon->x + (playerWeapon->playerWeaponSprite.getGlobalBounds().width * playerWeapon->playerWeaponSprite.getScale().y), playerWeapon->y - 8, 24, 23,
			mouseX, mouseY + sightSprite.getGlobalBounds().height / 2, playerWeapon->playerWeaponSprite.getRotation()));
		playerWeapon->shootPlayerFlag = true;
	}
}