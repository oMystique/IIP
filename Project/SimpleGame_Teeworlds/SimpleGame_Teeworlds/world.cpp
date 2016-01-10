#include "world.h"


void World::InitWorldObjects() {
	InitTextures();
	InitImages();
	InitSounds();
	InitObjects();
	InitSprites();
}

void World::DestroyWorldObjects() {
	list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end();) {
		Entity *b = *it;
		it = entities.erase(it);
		delete b;
	}
	entities.clear();
	easyEnemyObj.clear();
	mediumEnemyObj.clear();
	hardEnemyObj.clear();
	healthPointsObj.clear();
	armorPointsObj.clear();
	player.release();
}