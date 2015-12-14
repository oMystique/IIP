#pragma once


#include "weapon.h"
#include "bonuses.h"
#include <list>
#include "lifebar.h"


struct WorldInit {
	Image heroImage;
	Image easyEnemyImage;
	Image mediumEnemyImage;
	Image healthImage;
	Image bulletImage;
	Image weaponsImage;

	Texture bgTexture;
	Sprite bgSprite;

	Texture flagTexture;
	Sprite flagSprite;

	Texture sightTexture;
	Sprite sightSprite;

	Texture objectsTexture;

	Texture healthTexture;
	Sprite healthSprite;

	SoundBuffer shootBuffer;
	Sound shoot;

	SoundBuffer kickHitBuffer;
	Sound kickHit;

	SoundBuffer enemyDieBuffer;
	Sound enemyDie;

	SoundBuffer missSoundBuffer;
	Sound missSound;

	Music bgMusic;

	Level lvl;

	Object playerObj;

	vector<Object> easyEnemyObj;
	vector<Object> mediumEnemyObj;
	vector<Object> healthPoints;
	Object flagObj;

	list<Entity*>  entities;
	list<Entity*>::iterator it;
	list<Entity*>::iterator at;

	unique_ptr<Player> player = nullptr;
	unique_ptr<View> view = nullptr;
	unique_ptr<Weapon> playerWeapon = nullptr;
	unique_ptr<Lifebar> lifebar = nullptr;
};