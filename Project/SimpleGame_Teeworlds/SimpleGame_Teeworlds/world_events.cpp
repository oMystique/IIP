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


void PlayerShootAtEnemy(Entity &bullet, Entity &enemy, Player &player, Sound &missSound) {
	if (!enemy.isDamaged) {
		enemy.isDamaged = true;
	}
	if ((enemy.name == "easyEnemy") && (player.weaponRotation < WEAPON_MISS_ROTATION.x) && (player.weaponRotation > WEAPON_MISS_ROTATION.y)) {
		missSound.play();
		bullet.speed *= -1;
		bullet.boost.x += -RANDOM_RANGE + rand() % int(RANDOM_RANGE);
		bullet.boost.y += -RANDOM_RANGE + rand() % int(RANDOM_RANGE);
	}
	else {
		if (enemy.name != "hardEnemy") {
			enemy.health -= DAMAGE_WITH_PLAYER_WEAPON;
			bullet.life = false;
			if (enemy.sprite.getColor() != (Color::Red) && (enemy.sprite.getColor().a != 150) && (enemy.name == "easyEnemy")) {
				if (enemy.action == enemy.moveLeft) {
					enemy.action = enemy.moveRight;
				}
				else {
					enemy.action = enemy.moveLeft;
				}
			}
		}
		else {
			enemy.health -= DAMAGE_WITH_PLAYER_WEAPON / GET_HALF;
			bullet.life = false;
		}
	}
}


void FightRotateMediumEnemy(Entity &enemy, Player &player, float const rotation) {
	enemy.sprite.setRotation(rotation);
	if ((-QUARTER_CIRCLE <= rotation) && (rotation <= QUARTER_CIRCLE)) {
		if (enemy.sprite.getScale().y < 0) {
			enemy.sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
		}
	}
	else {
		if (enemy.sprite.getScale().y > 0) {
			enemy.sprite.setScale(-MEDIUM_ENEMY_SCALE, -MEDIUM_ENEMY_SCALE);
		}
	}

}


void EnemyShootAtPlayer(Level &lvl, Entity &enemy, Player &player, list<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage) {
	enemy.isFight = true;
	entities.push_back(new Bullet(bulletImage, "enemyBullet", lvl,
		FloatRect(enemy.rect.left, enemy.rect.top + 10, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(player.rect.left + ENEMY_SHOOT_CORRECTION.x, player.rect.top + ENEMY_SHOOT_CORRECTION.y),
		enemy.sprite.getRotation()));
	playerWeapon.shootEnemyFlag = true;
	playerWeapon.shootEnemyTimer = 0;
}


void EnemyDamagedPlayer(Sound &kickHit, Entity &enemy, Player &player, float time) {
	if (!player.isDamaged) {
		player.isDamaged = true;
	}
	enemy.isMove = false;
	if (!kickHit.getStatus()) {
		kickHit.play();
	}
	if (enemy.name == "enemyBullet") {
		if (player.armor > 0) {
			player.health -= DAMAGE_TO_PLAYER_WITH_WEAPON / GET_HALF;
			player.armor -= DAMAGE_TO_PLAYER_WITH_WEAPON;
		}
		else {
			player.health -= DAMAGE_TO_PLAYER_WITH_WEAPON;
		}
		enemy.life = false;
	}
	else {
		enemy.isFight = true;
		if (player.armor > 0) {
			player.health -= 0.3 * time;
			player.armor -= 0.6 * time; //TODO: REF;
		}
		else {
			player.health -= 0.5 * time;
		}
	}
}


float GetDistance(Player &player, Entity &enemy) {
	return float(sqrt((player.rect.left - enemy.rect.left)*(player.rect.left - enemy.rect.left) + (player.rect.top - enemy.rect.top)*(player.rect.top - enemy.rect.top)));
}


bool ActHardEnemy(Player &player, Entity &enemy, float const distance, Sound kickHit, float time) {
	if (distance > HARD_ENEMY_ACT_DISTANCE) {
		enemy.onGround = true;
		enemy.rect.top = player.rect.top;
		enemy.isFight = false;
		if (player.rect.left < enemy.rect.left) {
			enemy.action = enemy.moveLeft;
		}
		else {
			enemy.action = enemy.moveRight;
		}
		return false;
	}
	else {
		EnemyDamagedPlayer(kickHit, enemy, player, time);
		enemy.isMove = true;
		enemy.isFight = true;
		enemy.action = enemy.stay;
		return true;
	}
	
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
						FightRotateMediumEnemy(*subject, *player, GetRotation({ player->rect.left, player->rect.top }, { subject->rect.left, subject->rect.top }));
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
			subject->life = false;
		}
		else if ((subject->name == "armorPoint") && (subject->getRect().intersects(player->getRect()) && (player->armor < COUNT_PLAYER_HEALTH))) {
			player->armor += BONUS_HEALTH;
			subject->life = false;
		}

	}
}


void World::Shoot(String subject, Vector2f mousePos) {
	/*int sign = (playerWeapon->playerWeaponSprite.getScale().y > 0) - (playerWeapon->playerWeaponSprite.getScale().y < 0);
	double x = playerWeapon->playerWeaponSprite.getGlobalBounds().left + ((playerWeapon->playerWeaponSprite.getGlobalBounds().width / 10) * sign) * cos(player->weaponRotation * M_PI / 360 / 2);
	double y = playerWeapon->playerWeaponSprite.getGlobalBounds().top + ((playerWeapon->playerWeaponSprite.getGlobalBounds().width / 10) * sign) * sin(player->weaponRotation * M_PI / 360 / 2);*/
	double x = playerWeapon->playerWeaponSprite.getPosition().x - 8.f;
	double y = playerWeapon->playerWeaponSprite.getPosition().y - 6.f;
	shoot.play();
	entities.push_back(new Bullet(bulletImage, "Bullet", lvl,
		FloatRect(x, y, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(mousePos.x, mousePos.y + sightSprite.getGlobalBounds().height / GET_FOURTH),
		playerWeapon->playerWeaponSprite.getRotation()));
	playerWeapon->shootPlayerFlag = true;
}