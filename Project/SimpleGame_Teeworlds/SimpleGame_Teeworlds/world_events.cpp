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


float GetDistance(Player &player, Entity &enemy) {
	return float(sqrt((player.x - enemy.x)*(player.x - enemy.x) + (player.y - enemy.y)*(player.y - enemy.y)));
}


void World::InteractObjects(float time) {
	float distance = 0;
	CalculateShootTime(time, *playerWeapon);

	//TODO
	if (!missionTarget) {
		if (FloatRect(flagSprite.getPosition().x, flagSprite.getPosition().y, 127, 240).intersects(player->getRect())) {
			missionTarget = true;
			flagSprite.setScale(0.3, 0.3);
			player->flag = true;
		}
	}


	for (it = entities.begin(); it != entities.end(); it++) {
		for (at = entities.begin(); at != entities.end(); at++) {
			if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy")))) {
				if (((*it)->name == "easyEnemy") && (177 > player->weaponRotation) && (player->weaponRotation > 3)) {
					missSound.play();
					(*at)->speed = -(*at)->speed;
					(*at)->dx += rand() % 500 - 500;
				}
				else {
					(*it)->health -= 20;
					(*at)->life = false;
				}
			}
		}
		if (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy") || ((*it)->name == "enemyBullet")) {
			if ((*it)->name == "mediumEnemy") {
				distance = GetDistance(*player, **it);
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
					(*it)->isFight = true;
					player->health -= 2;
					player->armor -= 5;
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
					(*it)->isFight = false;
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
			playerWeapon->x + (playerWeapon->playerWeaponSprite.getGlobalBounds().width * playerWeapon->playerWeaponSprite.getScale().y), playerWeapon->y - 4 , 24, 23,
			mouseX, mouseY + sightSprite.getGlobalBounds().height / 4, playerWeapon->playerWeaponSprite.getRotation()));
		playerWeapon->shootPlayerFlag = true;
	}
}