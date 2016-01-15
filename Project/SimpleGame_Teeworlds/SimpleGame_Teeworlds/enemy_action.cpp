#include "enemy.h"


void EnemyShootAtPlayer(Level &lvl, Entity &subject, Player &player, vector<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage) {
	subject.isFight = true;
	entities.push_back(new Bullet(bulletImage, ENEMY_BULLET, lvl,
		FloatRect(subject.rect.left, subject.rect.top + 10.f, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(player.rect.left + ENEMY_SHOOT_CORRECTION.x, player.rect.top + ENEMY_SHOOT_CORRECTION.y),
		subject.sprite.getRotation()));
	playerWeapon.shootEnemyFlag = true;
	playerWeapon.shootEnemyTimer = 0;
}


void ActHardEnemy(Player &player, Entity &enemy, float const distance, Sound kickHit, float time) {
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
	}
}

void FightRotateMediumEnemy(Sprite &sprite, float const rotation) {
	sprite.setRotation(rotation);
	if ((-QUARTER_CIRCLE <= rotation) && (rotation <= QUARTER_CIRCLE)) {
		if (sprite.getScale().y < 0) {
			sprite.setScale(-MEDIUM_ENEMY_SCALE, MEDIUM_ENEMY_SCALE);
		}
	}
	else {
		if (sprite.getScale().y > 0) {
			sprite.setScale(-MEDIUM_ENEMY_SCALE, -MEDIUM_ENEMY_SCALE);
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
	if (enemy.name == ENEMY_BULLET) {
		if (player.armor > BONUS_HEALTH) {
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
			player.health -= ENEMY_MELEE_DAMAGE * time;
			player.armor -= ENEMY_MELEE_DAMAGE * GET_HALF * time;
		}
		else {
			player.health -= ENEMY_MELEE_DAMAGE * GET_HALF * time;
		}
	}
}