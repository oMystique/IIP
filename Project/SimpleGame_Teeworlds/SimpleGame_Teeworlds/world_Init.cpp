#include "world.h"
#include "entity.h"

void World::InitObjects() {
	lvl.LoadFromFile(to_string(numberLvl) + ".tmx");

	playerObj = lvl.GetObject(PLAYER_BAR);

	player = make_unique<Player>(heroImage, PLAYER_BAR, lvl, FloatRect(playerObj.rect.left, playerObj.rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y));
	playerWeapon = make_unique<Weapon>(weaponsImage, PLAYER_WEAPON, FloatRect(player->rect.left, player->rect.top, DEFAULT_WEAPON_BOUNDS.x, DEFAULT_WEAPON_BOUNDS.y));
	player->lifebar = make_unique<Lifebar>(bulletImage, Vector2f(float(PLAYER_LIFEBAR_HP_RECT.width), float(PLAYER_LIFEBAR_HP_RECT.height)), player->name);
	slowMotionBar = make_unique<Lifebar>(enemyLifeBar, Vector2f(0.f, 0.f), MOTION_BAR);
	view = make_unique<View>();


	easyEnemyObj = lvl.GetObjects(EASY_ENEMY);
	for (unsigned int i = 0; i < easyEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(easyEnemyImage, EASY_ENEMY, lvl, FloatRect(easyEnemyObj[i].rect.left, easyEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}
	easyEnemyObj.clear();

	mediumEnemyObj = lvl.GetObjects(MEDIUM_ENEMY);
	for (unsigned int i = 0; i < mediumEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(mediumEnemyImage, MEDIUM_ENEMY, lvl, FloatRect(mediumEnemyObj[i].rect.left, mediumEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}
	mediumEnemyObj.clear();

	hardEnemyObj = lvl.GetObjects(HARD_ENEMY); 

	for (unsigned int i = 0; i < hardEnemyObj.size(); i++) {
		entities.push_back(new Enemy(hardEnemyImage, HARD_ENEMY, lvl, FloatRect(hardEnemyObj[i].rect.left, hardEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x * GET_HALF, DEFAULT_UNIT_BOUNDS.y)));
	}
	hardEnemyObj.clear();

	countEnemies = entities.size();

	healthPointsObj = lvl.GetObjects(HEALTH_BONUS);
	for (unsigned int i = 0; i < healthPointsObj.size(); i++) {
		entities.push_back(new Bonuses(bulletImage, HEALTH_BONUS, FloatRect(healthPointsObj[i].rect.left, healthPointsObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}
	healthPointsObj.clear();

	armorPointsObj = lvl.GetObjects(ARMOR_BONUS);
	for (unsigned int i = 0; i < armorPointsObj.size(); i++) {
		entities.push_back(new Bonuses(bulletImage, ARMOR_BONUS, FloatRect(armorPointsObj[i].rect.left, armorPointsObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}
	armorPointsObj.clear();

	motionBonusObj = lvl.GetObjects(MOTION_BONUS);
	for (unsigned int i = 0; i < motionBonusObj.size(); i++) {
		entities.push_back(new Bonuses(motionBonusImage, MOTION_BONUS, FloatRect(motionBonusObj[i].rect.left, motionBonusObj[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y * GET_HALF)));
	}
	motionBonusObj.clear();

	flagObj = lvl.GetObject("flag");

	interfaceText = make_unique<InterfaceText>();

	InitLifeBarsForEnemy(entities, enemyLifeBar);

	slowMotion = false;
}

void World::InitImages() {
	heroImage.loadFromFile(PLAYER_IMAGE_PATH);
	easyEnemyImage.loadFromFile(EASY_ENEMY_IMAGE_PATH);
	mediumEnemyImage.loadFromFile(MEDIUM_ENEMY_IMAGE_PATH);
	bulletImage.loadFromFile(TEXTURE_COLLECTION_PATH);
	weaponsImage.loadFromFile(PLAYER_WEAPON_IMAGE_PATH);
	hardEnemyImage.loadFromFile(HARD_ENEMY_IMAGE_PATH);
	enemyLifeBar.loadFromFile(ENEMY_LIFEBAR_IMAGE_PATH);
	motionBonusImage.loadFromFile(MOTION_BONUS_IMAGE_PATH);
}

void World::InitTextures() {
	bgTexture.loadFromFile(BACKGROUND_TEXTURE_PATH);
	objectsTexture.loadFromFile(TEXTURE_COLLECTION_PATH);
}

void World::InitSprites() {
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / GET_HALF, bgSprite.getGlobalBounds().height / GET_HALF);
	bgSprite.setScale(BG_SPRITE_SCALE, BG_SPRITE_SCALE);

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
	shootBuffer.loadFromFile(SHOOT_SOUND_PATH);
	shoot.setBuffer(shootBuffer);
	shoot.setVolume(SOUND_VOLUME);

	kickHitBuffer.loadFromFile(DAMAGED_SOUND_PATH);
	kickHit.setBuffer(kickHitBuffer);
	kickHit.setVolume(SOUND_VOLUME);

	missSoundBuffer.loadFromFile(MISS_SOUND_PATH);
	missSound.setBuffer(missSoundBuffer);

	bgMusic.openFromFile("sounds/" + to_string(numberLvl) + ".ogg");
	bgMusic.play();
	bgMusic.setVolume(SOUND_VOLUME);
	bgMusic.setLoop(true);

	motionBuffer.loadFromFile(MOTION_SOUND_PATH);
	motionSound.setBuffer(motionBuffer);
}