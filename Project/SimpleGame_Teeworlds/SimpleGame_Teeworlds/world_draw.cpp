#include "world.h"


void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	for (it = entities.begin(); it != entities.end(); it++) {
		window->draw((*it)->sprite);
	}
	window->draw(flagSprite);
	window->draw(playerWeapon->playerWeaponSprite);
	window->draw(player->sprite);
	lifebar->Update(player->health, player->armor, *window);
	window->draw(sightSprite);
}