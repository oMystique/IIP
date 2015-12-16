#include "world.h"


void World::InitObjects() {
	lvl.LoadFromFile("new_map.tmx");

	playerObj = lvl.GetObject("player");

	player = make_unique<Player>(heroImage, "Player1", lvl, FloatRect(playerObj.rect.left, playerObj.rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y));
	playerWeapon = make_unique<Weapon>(weaponsImage, "playerWeapon", FloatRect(player->rect.left, player->rect.top, DEFAULT_WEAPON_BOUNDS.x, DEFAULT_WEAPON_BOUNDS.y));
	lifebar = make_unique<Lifebar>(healthImage, Vector2f(float(LIFEBAR_HP_RECT.width), float(LIFEBAR_HP_RECT.height)));
	view = make_unique<View>();

	easyEnemyObj = lvl.GetObjects("easyEnemy");
	for (unsigned int i = 0; i < easyEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(easyEnemyImage, "easyEnemy", lvl, FloatRect(easyEnemyObj[i].rect.left, easyEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}

	mediumEnemyObj = lvl.GetObjects("mediumEnemy");
	for (unsigned int i = 0; i < mediumEnemyObj.size(); i++) { 
		entities.push_back(new Enemy(mediumEnemyImage, "mediumEnemy", lvl, FloatRect(mediumEnemyObj[i].rect.left, mediumEnemyObj[i].rect.top, DEFAULT_UNIT_BOUNDS.x, DEFAULT_UNIT_BOUNDS.y)));
	}

	healthPoints = lvl.GetObjects("healthPoint");
	for (unsigned int i = 0; i < healthPoints.size(); i++) {
		entities.push_back(new Bonuses(healthImage, "healthPoint", FloatRect(healthPoints[i].rect.left, healthPoints[i].rect.top, DEFAULT_BONUSES_BOUNDS.x, DEFAULT_BONUSES_BOUNDS.y)));
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
	weaponsImage.loadFromFile("images/shotgun.png");
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
}