#include "enemy.h"


void EnemyShootAtPlayer(Level &lvl, Entity &enemy, Player &player, list<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage) {
	enemy.isFight = true;
	entities.push_back(new Bullet(bulletImage, "enemyBullet", lvl,
		FloatRect(enemy.rect.left, enemy.rect.top + 10, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(player.rect.left + ENEMY_SHOOT_CORRECTION.x, player.rect.top + ENEMY_SHOOT_CORRECTION.y),
		enemy.sprite.getRotation()));
	playerWeapon.shootEnemyFlag = true;
	playerWeapon.shootEnemyTimer = 0;
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

void FightRotateMediumEnemy(Entity &enemy, float const rotation) {
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
		enemy.health = 0;
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