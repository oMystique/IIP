#include "world.h"


FloatRect GetSpriteRect(Sprite sprite) {
	return FloatRect(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
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
	if ((enemy.name == "easyEnemy") && (player.weaponRotation < WEAPON_MISS_ROTATION.x) && (player.weaponRotation > WEAPON_MISS_ROTATION.y)) {
		missSound.play();
		bullet.speed *= -1;
		bullet.boost.x += -RANDOM_RANGE + rand() % int(RANDOM_RANGE);
	}
	else {
		enemy.health -= DAMAGE_WITH_PLAYER_WEAPON;
		bullet.life = false;
	}
}


void FightRotateMediumEnemy(Entity &enemy, Player &player) {
	if ((enemy.sprite.getScale().x > 0.f) && (enemy.sprite.getPosition().x > player.sprite.getPosition().x)) {
		enemy.sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
	}
	else if ((enemy.sprite.getScale().x < 0) && (enemy.sprite.getPosition().x < player.sprite.getPosition().x)) {
		enemy.sprite.setScale(MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
	}
}


void EnemyShootAtPlayer(Level &lvl, Entity &enemy, Player &player, list<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage) {
	entities.push_back(new Bullet(bulletImage, "enemyBullet", lvl,
		FloatRect(enemy.rect.left, enemy.rect.top + 10, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(player.rect.left + ENEMY_SHOOT_CORRECTION.x, player.rect.top + ENEMY_SHOOT_CORRECTION.y),
		enemy.sprite.getRotation()));
	playerWeapon.shootEnemyFlag = true;
	playerWeapon.shootEnemyTimer = 0;
}


void EnemyDamagedPlayer(Sound &kickHit, Entity &enemy, Player &player) {
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
		player.health -= 1;
		player.armor -= 2;
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
			if (IntersectsRects(subject->getRect(), object->getRect()) && ((object->name == "Bullet") && (((subject->name == "easyEnemy") || (subject->name == "mediumEnemy"))))) {
				PlayerShootAtEnemy(*object, *subject, *player, missSound);
			}
		}
		if ((subject->name == "easyEnemy") || (subject->name == "mediumEnemy") || (subject->name == "enemyBullet")) {
			if (subject->name == "mediumEnemy") {
				distance = GetDistance(*player, *subject);
			}
			if (IntersectsRects(subject->getRect(), player->getRect())) {
				EnemyDamagedPlayer(kickHit, *subject, *player);
			}
			else {
				subject->isMove = true;
				if (((IntersectsRects(subject->getEnemyView(), player->getRect())) && (subject->name == "easyEnemy")) || ((ENEMY_VIEW_RANGE > distance) && (subject->name == "mediumEnemy"))) {
					if (subject->name == "mediumEnemy") {
						FightRotateMediumEnemy(*subject, *player);
						if (playerWeapon->shootEnemyTimer > DEFAULT_ENEMY_SHOOT_SPEED / GET_HALF) {
							EnemyShootAtPlayer(lvl, *subject, *player, entities, *playerWeapon, bulletImage);
							break;
						}
					}
					subject->sprite.setColor(Color::Red);
				}
				else {
					subject->sprite.setColor(Color::White);
					subject->isFight = false;
				}
			}
		}
		else if ((subject->name == "healthPoint") && (subject->getRect().intersects(player->getRect()) && (player->health < COUNT_PLAYER_HEALTH))) {
			player->health += BONUS_HEALTH;
			subject->life = false;
		}

	}
}


void World::Shoot(String subject, Vector2f mousePos) {
	if (subject == "player") {
		shoot.play();
		entities.push_back(new Bullet(bulletImage, "Bullet", lvl,
			FloatRect(playerWeapon->rect.left + (playerWeapon->playerWeaponSprite.getGlobalBounds().width * playerWeapon->playerWeaponSprite.getScale().y), playerWeapon->rect.top - GET_FOURTH, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
			Vector2f(mousePos.x, mousePos.y + sightSprite.getGlobalBounds().height / GET_FOURTH),
			playerWeapon->playerWeaponSprite.getRotation()));
		playerWeapon->shootPlayerFlag = true;
	}
}