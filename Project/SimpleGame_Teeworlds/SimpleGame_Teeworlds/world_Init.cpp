#include "world.h"


void World::InitObjects() {
	lvl.LoadFromFile("new_map.tmx");

	playerObj = lvl.GetObject("player");

	player = make_unique<Player>(heroImage, "Player1", lvl, playerObj.rect.left, playerObj.rect.top, 36, 36);
	playerWeapon = make_unique<Weapon>(weaponsImage, "playerWeapon", player->x, player->y, 227, 60);
	lifebar = make_unique<Lifebar>(healthImage, 62, 62);
	view = make_unique<View>();

	easyEnemyObj = lvl.GetObjects("easyEnemy");
	for (unsigned int i = 0; i < easyEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(easyEnemyImage, "easyEnemy", lvl, easyEnemyObj[i].rect.left, easyEnemyObj[i].rect.top, 36, 36));
	}

	mediumEnemyObj = lvl.GetObjects("mediumEnemy");
	for (unsigned int i = 0; i < mediumEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(mediumEnemyImage, "mediumEnemy", lvl, mediumEnemyObj[i].rect.left, mediumEnemyObj[i].rect.top, 36, 36));
	}

	healthPoints = lvl.GetObjects("healthPoint");
	for (unsigned int i = 0; i < healthPoints.size(); i++) {
		entities.push_back(new Bonuses(healthImage, "healthPoint", healthPoints[i].rect.left, healthPoints[i].rect.top, 44, 44));
	}

	flagObj = lvl.GetObject("flag");
}


void World::InitImages() {
	heroImage.loadFromFile("images/anim_player.png");
	easyEnemyImage.loadFromFile("images/easy_weapon_1.png");
	easyEnemyImage.createMaskFromColor(Color(255, 255, 255));
	mediumEnemyImage.loadFromFile("images/mediumEnemy.png");
	mediumEnemyImage.createMaskFromColor(Color(255, 255, 255));
	healthImage.loadFromFile("images/weapons.png");
	bulletImage.loadFromFile("images/weapons.png");
}


void World::InitTextures() {
	bgTexture.loadFromFile("images/fon-nebo.png");
	objectsTexture.loadFromFile("images/weapons.png");
}


void World::InitSprites() {
	bgSprite.setTexture(bgTexture);
	bgSprite.setOrigin(bgSprite.getGlobalBounds().width / GET_HALF, bgSprite.getGlobalBounds().height / GET_HALF);

	flagSprite.setTexture(objectsTexture);
	flagSprite.setTextureRect(IntRect(387, 268, 127, 240));
	flagSprite.setPosition(flagObj.rect.left, flagObj.rect.top);
	flagSprite.setScale(FLAG_SCALE, FLAG_SCALE);

	sightSprite.setTexture(objectsTexture);
	sightSprite.setTextureRect(IntRect(0, 0, 61, 61));
	sightSprite.setScale(SIGHT_SCALE, SIGHT_SCALE);
}


void World::InitSounds() {
	shootBuffer.loadFromFile("sounds/shoot.ogg");
	shoot.setBuffer(shootBuffer);
	shoot.setVolume(SOUND_VOLUME);

	kickHitBuffer.loadFromFile("sounds/kickHit.ogg");
	kickHit.setBuffer(kickHitBuffer);
	kickHit.setVolume(SOUND_VOLUME);

	enemyDieBuffer.loadFromFile("sounds/catCrash.ogg");
	enemyDie.setBuffer(enemyDieBuffer);

	bgMusic.openFromFile("sounds/fonMM.ogg");
	bgMusic.play();
	bgMusic.setVolume(SOUND_VOLUME);
	bgMusic.setLoop(true);
}