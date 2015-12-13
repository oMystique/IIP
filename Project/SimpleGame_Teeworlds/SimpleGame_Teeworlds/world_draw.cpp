#include "world.h"


void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	for (it = entities.begin(); it != entities.end(); it++) {
		window->draw((*it)->sprite);
	}
	window->draw(playerWeapon->playerWeaponSprite);
	window->draw(player->sprite);
	window->draw(sightSprite);
}