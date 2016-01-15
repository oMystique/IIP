#include "player.h"
#include "weapon.h"
#include "bullet.h"


void Player::SetPlayerAction() {
	switch (action) {
	case moveRight: boost.x = speed; break;
	case moveLeft: boost.x = -speed; break;
	case jump: break;
	case stay: break;
	case down: boost.y = 0; break;
	}
}


void Player::Control(float &time) {
	ControlDirection();
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		Animation(time);
		action = moveLeft;
		speed = 0.22f;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		Animation(time);
		action = moveRight;
		speed = 0.22f;
	}
	if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
		action = jump;
		boost.y = -PLAYER_JUMP_SPEED;
		onGround = false;
	}
	if ((Keyboard::isKeyPressed(Keyboard::E)) && (!onGround)) {
		action = jump;
		boost.y = PLAYER_JUMP_SPEED / 10;
		parachute->parachuteOpen = true;
	}
	else {
		parachute->parachuteOpen = false;
	}
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), int(PLAYER_SPRITE_BOUND), int(PLAYER_SPRITE_BOUND)));
}

void ChangeEnemyAction(Entity &enemy) {
	if (enemy.action == enemy.moveLeft) {
		enemy.action = enemy.moveRight;
	}
	else {
		enemy.action = enemy.moveLeft;
	}
}


void PlayerShootAtEnemy(Entity &bullet, Entity &enemy, Player &player, Sound &missSound) {
	if (!enemy.isDamaged) {
		enemy.isDamaged = true;
	}
	if ((enemy.name == EASY_ENEMY) && (player.weaponRotation < WEAPON_MISS_ROTATION.x) && (player.weaponRotation > WEAPON_MISS_ROTATION.y)) {
		missSound.play();
		bullet.speed *= -1;
		bullet.boost.x += -RANDOM_RANGE + rand() % int(RANDOM_RANGE);
		bullet.boost.y += -RANDOM_RANGE + rand() % int(RANDOM_RANGE);
	}
	else {
		if (enemy.name != HARD_ENEMY) {
			enemy.health -= DAMAGE_WITH_PLAYER_WEAPON;
			bullet.health = 0;
			if (enemy.sprite.getColor() != (Color::Red) && (enemy.sprite.getColor().a != 150) && (enemy.name == EASY_ENEMY)) {
				ChangeEnemyAction(enemy);
			}
		}
		else {
			enemy.health -= DAMAGE_WITH_PLAYER_WEAPON / GET_HALF;
			bullet.health = 0;
		}
	}
}
