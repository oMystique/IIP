#include "world.h"
#define _USE_MATH_DEFINES
#include <math.h>


void World::UpdateWorld(float time, float mouseX, float mouseY, View &view) {
	float dX = mouseX - player->x; //������ , ����������� ������, ������� ���������� ������ � ������
	float dY = mouseY - player->y; //�� ��, ���������� y
	float rotation = (atan2(dY, dX)) * GET_CIRCLE_HALF / M_PI; //�������� ���� � �������� � ��������� ��� � �������
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