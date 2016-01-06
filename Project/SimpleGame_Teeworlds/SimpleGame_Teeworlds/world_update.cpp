#include "world.h"

void UpdateCountEnemies(Entity &enemy, int &countEnemies) {
	if ((enemy.name == "diedEnemy")) {
		countEnemies -= 1;
	}
}

void World::UpdateWorld(float time, Vector2f mousePos, View &view, RenderWindow &window) {
	float rotation = GetRotation(mousePos, Vector2f(player->rect.left, player->rect.top));
	for (it = entities.begin(); it != entities.end();) {
		Entity *b = *it;
		(*it)->Update(time);
		if (!b->life) {
			UpdateCountEnemies(**it, countEnemies);
			it = entities.erase(it);
			delete b;
		}
		else {
			it++;
		}
	}
	player->Update(time);
	if (missionTarget) { //TODO
		flagSprite.setPosition(player->rect.left + FLAG_SPRITE_POS_CORRECTION.x, player->rect.top - FLAG_SPRITE_POS_CORRECTION.y);
	}
	playerWeapon->Update(time, rotation,  Vector2f(player->rect.left, player->rect.top - GET_FOURTH), "playerWeapon");
	player->weaponRotation = rotation;
	view.setCenter(player->rect.left, player->rect.top);
	sightSprite.setPosition(mousePos);
	bgSprite.setPosition(player->rect.left, player->rect.top);
}