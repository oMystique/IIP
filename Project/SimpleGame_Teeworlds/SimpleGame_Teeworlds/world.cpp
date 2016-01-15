#include "world.h"


void World::InitWorldObjects() {
	InitTextures();
	InitImages();
	InitSounds();
	InitObjects();
	InitSprites();
}

void World::DestroyWorldObjects() {
	vector<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end();) {
		Entity *b = *it;
		it = entities.erase(it);
		delete b;
	}
}