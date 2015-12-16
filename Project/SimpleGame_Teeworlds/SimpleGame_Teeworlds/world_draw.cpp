#include "world.h"


void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	for (Entity *&entity: entities) {
		window->draw(entity->sprite);
	}
	window->draw(flagSprite);
	window->draw(playerWeapon->playerWeaponSprite);
	window->draw(player->sprite);
	lifebar->Update(player->health, player->armor, *window);
	window->draw(sightSprite);
}