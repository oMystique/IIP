#pragma once


#include "weapon.h"
#include "bonuses.h"
#include <list>
#include "enemy.h"
#include "bullet.h"
#include "interface_text.h"



struct WorldInit {
	Image heroImage;
	Image easyEnemyImage;
	Image mediumEnemyImage;
	Image hardEnemyImage;
	Image healthImage;
	Image bulletImage;
	Image weaponsImage;
	Image enemyLifeBar;
	Image motionBonusImage;

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

	SoundBuffer motionBuffer;
	Sound motionSound;

	Music bgMusic;

	Level lvl;
	int numberLvl;

	Object playerObj;
	Object flagObj;

	vector<Object> easyEnemyObj;
	vector<Object> mediumEnemyObj;
	vector<Object> hardEnemyObj;
	vector<Object> healthPointsObj;
	vector<Object> armorPointsObj;
	vector<Object> motionBonusObj;

	list<Entity*>  entities;

	unique_ptr<Player> player = nullptr;
	unique_ptr<View> view = nullptr;
	unique_ptr<Weapon> playerWeapon = nullptr;
	unique_ptr<InterfaceText> interfaceText = nullptr;
	unique_ptr<Lifebar> slowMotionBar = nullptr;

	bool missionTarget; //TODO
	bool slowMotion;
	RectangleShape slowMotionRect;
	int countEnemies;
};