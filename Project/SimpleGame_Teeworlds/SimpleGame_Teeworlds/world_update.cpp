#include "world.h"
#define _USE_MATH_DEFINES
#include <math.h>

float GetRotation(Vector2f mousePos, Vector2f playerPos) {
	float dX = mousePos.x - playerPos.x; 
	float dY = mousePos.y - playerPos.y; 
	return float((atan2(dY, dX)) * GET_CIRCLE_HALF / M_PI); //получаем угол в радианах и переводим его в градусы
}


void World::UpdateWorld(float time, Vector2f mousePos, View &view) {
	float rotation = GetRotation(mousePos, Vector2f(player->rect.left, player->rect.top));
	for (it = entities.begin(); it != entities.end();) {
		Entity *b = *it;
		(*it)->Update(time);
		if (!b->life) {
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