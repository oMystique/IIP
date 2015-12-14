#include "world.h"
#define _USE_MATH_DEFINES
#include <math.h>

float GetRotation(float mouseX, float mouseY, float x, float y) {
	float dX = mouseX - x; 
	float dY = mouseY - y; 
	return (atan2(dY, dX)) * GET_CIRCLE_HALF / M_PI; //получаем угол в радианах и переводим его в градусы
}


void World::UpdateWorld(float time, float mouseX, float mouseY, View &view) {
	float rotation = GetRotation(mouseX, mouseY, player->x, player->y); 
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
	playerWeapon->Update(time, rotation, player->x, player->y, "playerWeapon");
	player->weaponRotation = rotation;
	view.setCenter(player->x, player->y);
	sightSprite.setPosition(mouseX, mouseY);
	bgSprite.setPosition(player->x, player->y);
}