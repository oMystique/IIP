#pragma once
#include "player_init.h"

struct Player: public Entity, PlayerInit  {
	Player(Image &image, String name, Level lvl, FloatRect rect);
	void Update(float time);
private:
	void ControlDirection();
	void Control(float &time);
	void CheckCollisionWithMap(float dX, float dY);
	void Animation(float time);
	void InitDie();
	void DieAnimation(float time);
};


void PlayerShootAtEnemy(Entity &bullet, Entity &enemy, Player &player, Sound &missSound);
void PlayerShoot(Vector2f mousePos, Weapon &playerWeapon, Sound &shoot, list<Entity*> &entities, Image &bulletImage, Level lvl, Sprite sightSprite);