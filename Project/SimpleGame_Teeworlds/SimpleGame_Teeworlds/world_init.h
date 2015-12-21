#pragma once


#include "weapon.h"
#include "bonuses.h"
#include <list>
#include "additAnimation.h"
#include "lifebar.h"


struct WorldInit {
	Image heroImage;
	Image easyEnemyImage;
	Image mediumEnemyImage;
	Image hardEnemyImage;
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

	SoundBuffer missSoundBuffer;
	Sound missSound;

	Music bgMusic;

	Level lvl;

	Object playerObj;

	vector<Object> easyEnemyObj;
	vector<Object> mediumEnemyObj;
	vector<Object> hardEnemyObj;
	vector<Object> healthPointsObj;
	vector<Object> armorPointsObj;
	Object flagObj;

	list<Entity*>  entities;
	list<Entity*>::iterator it;

	unique_ptr<Player> player = nullptr;
	unique_ptr<View> view = nullptr;
	unique_ptr<Weapon> playerWeapon = nullptr;
	unique_ptr<Lifebar> lifebar = nullptr;

	bool missionTarget; //TODO
	int countEnemies;
	Font font;
	Text countEnemiesText;
	Text missionTargetText;
};