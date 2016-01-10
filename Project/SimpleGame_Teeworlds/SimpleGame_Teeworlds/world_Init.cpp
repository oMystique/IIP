#include "world.h"
#include "entity.h"
#include <vld.h>

void World::InitObjects() {
	lvl.LoadFromFile("new_map.tmx");

	playerObj = lvl.GetObject("player");

	player = make_unique<Player>(heroImage, "player", lvl, FloatRect(playerObj.rect.left, playerObj.rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y));
	playerWeapon = make_unique<Weapon>(weaponsImage, "playerWeapon", FloatRect(player->rect.left, player->rect.top, DEFAULT_WEAPON_BOUNDS.x, DEFAULT_WEAPON_BOUNDS.y));
	player->lifebar = make_unique<Lifebar>(bulletImage, Vector2f(float(PLAYER_LIFEBAR_HP_RECT.width), float(PLAYER_LIFEBAR_HP_RECT.height)), player->name);
	slowMotionBar = make_unique<Lifebar>(enemyLifeBar, Vector2f(0.f, 0.f), "motionBar");
	view = make_unique<View>();


	easyEnemyObj = lvl.GetObjects("easyEnemy");
	for (unsigned int i = 0; i < easyEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(easyEnemyImage, "easyEnemy", lvl, FloatRect(easyEnemyObj[i].rect.left, easyEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}

	mediumEnemyObj = lvl.GetObjects("mediumEnemy");
	for (unsigned int i = 0; i < mediumEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(mediumEnemyImage, "mediumEnemy", lvl, FloatRect(mediumEnemyObj[i].rect.left, mediumEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}

	hardEnemyObj = lvl.GetObjects("hardEnemy"); 

	for (unsigned int i = 0; i < hardEnemyObj.size(); i++) {
		entities.push_back(new Enemy(hardEnemyImage, "hardEnemy", lvl, FloatRect(hardEnemyObj[i].rect.left, hardEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x * GET_HALF, DEFAULT_UNIT_BOUNDS.y)));
	}

	countEnemies = entities.size();

	healthPointsObj = lvl.GetObjects("healthPoint");
	for (unsigned int i = 0; i < healthPointsObj.size(); i++) {
		entities.push_back(new Bonuses(bulletImage, "healthPoint", FloatRect(healthPointsObj[i].rect.left, healthPointsObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}

	armorPointsObj = lvl.GetObjects("armorPoint");
	for (unsigned int i = 0; i < armorPointsObj.size(); i++) {
		entities.push_back(new Bonuses(bulletImage, "armorPoint", FloatRect(armorPointsObj[i].rect.left, armorPointsObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}

	motionBonusObj = lvl.GetObjects("motionBonus");
	for (unsigned int i = 0; i < armorPointsObj.size(); i++) {
		entities.push_back(new Bonuses(motionBonusImage, "motionBonus", FloatRect(motionBonusObj[i].rect.left, motionBonusObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}



	flagObj = lvl.GetObject("flag");

	interfaceText = make_unique<InterfaceText>();

	InitLifeBarsForEnemy(entities, enemyLifeBar);

	slowMotion = false;
}


void World::InitImages() {
	heroImage.loadFromFile("images/anim_player.png");
	easyEnemyImage.loadFromFile("images/easy_enemy.png");
	mediumEnemyImage.loadFromFile("images/medium_enemy.png");
	bulletImage.loadFromFile("images/weapons.png");
	weaponsImage.loadFromFile("images/shotgun.png");
	hardEnemyImage.loadFromFile("images/fireman.png");
	enemyLifeBar.loadFromFile("images/enemyLife.png");
	motionBonusImage.loadFromFile("images/motionBonus.png");
}


void World::InitTextures() {
	bgTexture.loadFromFile("images/fon-nebo.png");
	objectsTexture.loadFromFile("images/weapons.png");
}


void World::InitSprites() {
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / GET_HALF, bgSprite.getGlobalBounds().height / GET_HALF);

	flagSprite.setTexture(objectsTexture);
	flagSprite.setTextureRect(FLAG_SPRITE_RECT);
	flagSprite.setPosition(flagObj.rect.left, flagObj.rect.top);
	flagSprite.setScale(FLAG_MAX_SCALE, FLAG_MAX_SCALE);
	missionTarget = false;

	sightSprite.setTexture(objectsTexture);
	sightSprite.setTextureRect(SIGHT_SPRITE_RECT);
	sightSprite.setScale(SIGHT_SCALE, SIGHT_SCALE);
}


void World::InitSounds() {
	shootBuffer.loadFromFile("sounds/shoot.ogg");
	shoot.setBuffer(shootBuffer);
	shoot.setVolume(SOUND_VOLUME);

	kickHitBuffer.loadFromFile("sounds/kickHit.ogg");
	kickHit.setBuffer(kickHitBuffer);
	kickHit.setVolume(SOUND_VOLUME);

	missSoundBuffer.loadFromFile("sounds/miss1.ogg");
	missSound.setBuffer(missSoundBuffer);

	bgMusic.openFromFile("sounds/fonMM.ogg");
	bgMusic.play();
	bgMusic.setVolume(SOUND_VOLUME);
	bgMusic.setLoop(true);

	motionBuffer.loadFromFile("sounds/motionSound.ogg");
	motionSound.setBuffer(motionBuffer);
}