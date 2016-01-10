#pragma once
#include "bullet.h"
#include "player.h"
#include <list>

struct Enemy :public Entity {
public:
	float currentFrame;
	float countFrames;
	float dmgFrame;
	Vector2f offset;

	Enemy(Image &image, String name, Level lvl, FloatRect rect);

	SoundBuffer enemyDieBuffer;
	Sound enemyDie;

	void Animation(float time);
	void Move(float direction);
	void checkCollisionWithMap(float dX, float dY);
	void Update(float time);
	void DieAnimation(float time);
	void InitDie();
};


void EnemyShootAtPlayer(Level &lvl, Entity &enemy, Player &player, list<Entity*> &entities, Weapon &playerWeapon, Image &bulletImage);
void EnemyDamagedPlayer(Sound &kickHit, Entity &enemy, Player &player, float time);
bool ActHardEnemy(Player &player, Entity &enemy, float const distance, Sound kickHit, float time);
void FightRotateMediumEnemy(Entity &enemy, float const rotation);