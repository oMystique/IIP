#include "world.h"


void DrawText(Text &missionTargetText, Text &countEnemiesText, RenderWindow &window) {
	window.draw(missionTargetText);
	window.draw(countEnemiesText);
}

void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	for (Entity *&entity: entities) {
		if (entity->sprite.getGlobalBounds().intersects(FloatRect(window->getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window->getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF, window->getSize().x, window->getSize().y))) {
			if (entity->name == "easyEnemy" || entity->name == "mediumEnemy" || entity->name == "hardEnemy") {
				int sign = ((entity->boost.x > 0) - (entity->boost.x < 0));
				entity->lifebar->Update(entity->health, 0.f, *window, { entity->rect.left + (25.f * -sign), entity->sprite.getGlobalBounds().top });
			}
			window->draw(entity->sprite);
		}
	}
	window->draw(flagSprite);
	window->draw(playerWeapon->playerWeaponSprite);
	if (player->parachuteOpen) {
		window->draw(player->parachuteSprite);
	}
	window->draw(player->sprite);
	player->lifebar->Update(player->health, player->armor, *window, { 0,0 }); 
	window->draw(sightSprite);
	interfaceText->UpdateText(*window, countEnemies, missionTarget);
}