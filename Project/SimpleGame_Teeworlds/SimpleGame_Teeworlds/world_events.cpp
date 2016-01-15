#include "world.h"


void World::InteractBetweenEntities(Entity &subject) {
	for (Entity *&object : entities) {
		if (IntersectsRects(subject.getRect(), object->getRect()) && ((object->name == PLAYER_BULLET) && (((subject.name == EASY_ENEMY) || (subject.name == MEDIUM_ENEMY) || (subject.name == HARD_ENEMY))))) {
			PlayerShootAtEnemy(*object, subject, *player, missSound);
		}
	}
}


void World::InteractBetweenPlayerAndEnemy(Entity &subject, float time, bool &isBreak) {
	float distance = GetDistance(subject.getRect(), player->getRect());
	if (IntersectsRects(subject.getRect(), player->getRect())) {
		EnemyDamagedPlayer(kickHit, subject, *player, time);
	}
	else {
		subject.isMove = true;
	}
	if (distance <= ENEMY_VIEW_RANGE) {
		if (subject.name == HARD_ENEMY) {
			ActHardEnemy(*player, subject, distance, kickHit, time);
		}
		else if (subject.name == MEDIUM_ENEMY) {
			FightRotateMediumEnemy(subject.sprite, GetRotation({ player->rect.left, player->rect.top }, { subject.rect.left, subject.rect.top }));
			if (playerWeapon->shootEnemyTimer > DEFAULT_ENEMY_SHOOT_SPEED / GET_HALF) {
				EnemyShootAtPlayer(lvl, subject, *player, entities, *playerWeapon, bulletImage);
				isBreak = true;
			}
		}
		else if (subject.name == EASY_ENEMY && IntersectsRects(subject.getEnemyView(), player->getRect())) {
			subject.sprite.setColor(Color::Red);
		}
		else {
			subject.sprite.setColor(Color::White);
			subject.isFight = false;
		}
	}
	else {
		subject.sprite.setRotation(0);
		subject.isFight = false;
	}
}


bool IsEnemy(String const name) {
	return ((name == EASY_ENEMY) || (name == MEDIUM_ENEMY) || (name == HARD_ENEMY));
}


void World::PlayerPickUpBonuses(Entity &subject) {
	if ((subject.name == HEALTH_BONUS) && (player->health < COUNT_PLAYER_HEALTH)) {
		player->health += BONUS_HEALTH;
		subject.health = 0;
	}
	else if ((subject.name == ARMOR_BONUS) && (player->armor < COUNT_PLAYER_HEALTH)) {
		player->armor += BONUS_HEALTH;
		subject.health = 0;
	}
	else if (subject.name == MOTION_BONUS) {
		subject.health = 0;
		slowMotionBar->SetParameterForMotion();
	}
}


void World::InteractObjects(float time) {
	CalculateShootTime(time, *playerWeapon);
	CheckPerfomMissionTarget(*player, flagSprite, missionTarget);
	for (Entity *&subject : entities) {
		InteractBetweenEntities(*subject);
		if (IsEnemy(subject->name) || (subject->name == ENEMY_BULLET)) {
			bool isBreak = false;
			InteractBetweenPlayerAndEnemy(*subject, time, isBreak);
			if (isBreak) {
				break;
			}
		}
		else if (IntersectsRects(subject->getRect(), player->getRect())) {
			PlayerPickUpBonuses(*subject);
		}
	}
}


void World::PlayerShootEvent(Vector2f mousePos) {
	if (player->health > BONUS_HEALTH) {
		float x = playerWeapon->playerWeaponSprite.getPosition().x - 8.f;
		float y = playerWeapon->playerWeaponSprite.getPosition().y - 6.f;
		shoot.play();
		entities.push_back(new Bullet(bulletImage, PLAYER_BULLET, lvl,
			FloatRect(x, y, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
			Vector2f(mousePos.x, mousePos.y + sightSprite.getGlobalBounds().height / GET_FOURTH),
			playerWeapon->playerWeaponSprite.getRotation()));
		playerWeapon->shootPlayerFlag = true;
	}
}