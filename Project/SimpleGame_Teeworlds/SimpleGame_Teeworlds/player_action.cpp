#include "player.h"
#include "weapon.h"
#include "bullet.h"

void Player::Control(float &time) {
	ControlDirection();
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		Animation(time);
		action = moveLeft;
		speed = 0.22;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		Animation(time);
		action = moveRight;
		speed = 0.22;
	}
	if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
		action = jump;
		boost.y = -PLAYER_JUMP_SPEED;
		onGround = false;
	}
	if ((Keyboard::isKeyPressed(Keyboard::E)) && (!onGround)) {
		action = jump;
		boost.y = PLAYER_JUMP_SPEED / 10;
		parachuteOpen = true;
	}
	else {
		parachuteOpen = false;
	}
	sprite.setTextureRect(IntRect(int(offset.x), int(offset.y), int(PLAYER_SPRITE_BOUND), int(PLAYER_SPRITE_BOUND)));
}


void PlayerShoot(Vector2f mousePos, Weapon &playerWeapon, Sound &shoot, list<Entity*> &entities, Image &bulletImage, Level lvl, Sprite sightSprite) {
	double x = playerWeapon.playerWeaponSprite.getPosition().x - 8.f;
	double y = playerWeapon.playerWeaponSprite.getPosition().y - 6.f;
	shoot.play();
	entities.push_back(new Bullet(bulletImage, "Bullet", lvl,
		FloatRect(x, y, BULLET_BOUNDS.x, BULLET_BOUNDS.y),
		Vector2f(mousePos.x, mousePos.y + sightSprite.getGlobalBounds().height / GET_FOURTH),
		playerWeapon.playerWeaponSprite.getRotation()));
	playerWeapon.shootPlayerFlag = true;
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
			bullet.health = 0;
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
			bullet.health = 0;
		}
	}
}