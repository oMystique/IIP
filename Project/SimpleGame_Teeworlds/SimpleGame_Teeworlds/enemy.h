#pragma once
#include "bullet.h"
#include "player.h"
#include <list>

struct Enemy :public Entity {
public:
	Enemy(Image &image, String name, Level lvl, FloatRect rect);
	void Update(float time);
private:
	SoundBuffer enemyDieBuffer;
	Sound enemyDie;

	void Animation(float time);
	void Move(float direction);
	void checkCollisionWithMap(float dX, float dY);
	void DieAnimation(float time);
	void InitDie();
};


void EnemyShootAtPlayer(Level &lvl, Entity &subject, Player &player, vector<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage);
void EnemyDamagedPlayer(Sound &kickHit, Entity &enemy, Player &player, float time);
void ActHardEnemy(Player &player, Entity &enemy, float const distance, Sound kickHit, float time);
void FightRotateMediumEnemy(Sprite &sprite, float const rotation);