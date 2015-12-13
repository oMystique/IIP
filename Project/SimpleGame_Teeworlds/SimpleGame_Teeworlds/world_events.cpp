#include "world.h"


void World::InteractObjects() {
	float distance = 0;
	for (it = entities.begin(); it != entities.end(); it++) {
		for (at = entities.begin(); at != entities.end(); at++) {
			if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy")))) {
				(*it)->health -= 13;
				(*at)->life = false;
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
					player->health -= 100;
					(*it)->life = false;
				}
				else {
					player->health -= 7;
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
						entities.push_back(new Bullet(bulletImage, "enemyBullet", lvl, (*it)->x, (*it)->y + 21, 24, 23, player->x + 11, player->y + 11, (*it)->sprite.getRotation()));
						break;
					}
					(*it)->sprite.setColor(Color::Red);
				}
				else {
					(*it)->sprite.setColor(Color::White);
				}
			}
		}
		else if (((*it)->name == "healthPoint") && ((*it)->getRect().intersects(player->getRect()) && (player->health < 1000))) {
			player->health += 100;
			(*it)->life = false;
		}
	}
}


void World::Shoot(String subject, float mouseX, float mouseY) {
	if (subject == "player") {
		shoot.play();
		entities.push_back(new Bullet(bulletImage, "Bullet", lvl, playerWeapon->x + playerWeapon->playerWeaponSprite.getGlobalBounds().width * playerWeapon->playerWeaponSprite.getScale().y, playerWeapon->y - 10, 24, 23, mouseX, mouseY + sightSprite.getGlobalBounds().height / 2, playerWeapon->playerWeaponSprite.getRotation()));
	}
}