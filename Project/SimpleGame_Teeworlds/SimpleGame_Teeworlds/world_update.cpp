#include "world.h"

void UpdateCountEnemies(Entity &enemy, int &countEnemies) {
	if ((enemy.name == "diedEnemy")) {
		countEnemies -= 1;
	}
}

void UpdateSlowMotion(unique_ptr<Lifebar> &slowMotionBar, Music &bgMusic, Sound &motionSound, bool &slowMotion, float time) {
	if (slowMotion) {
		slowMotion = slowMotionBar->IsBurnMotionParameter(time);
		if (!motionSound.getStatus()) {
			motionSound.play();
		}
		bgMusic.setVolume(0);
	}
	else {
		motionSound.stop();
		bgMusic.setVolume(SOUND_VOLUME);
	}
}

void UpdateEntites(int &countEnemies, float const time, vector<Entity*> &entities) {
	vector<Entity*>::iterator it;
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
}

void World::UpdateWorld(float time, Vector2f mousePos, View &view, RenderWindow &window) {
	float rotation = GetRotation(mousePos, Vector2f(player->rect.left, player->rect.top));
	UpdateEntites(countEnemies, time, entities);
	player->Update(time);
	if (missionTarget) { 
		flagSprite.setPosition(player->rect.left + FLAG_SPRITE_POS_CORRECTION.x, player->rect.top - FLAG_SPRITE_POS_CORRECTION.y);
	}
	playerWeapon->Update(time, rotation,  Vector2f(player->rect.left, player->rect.top - GET_FOURTH), PLAYER_WEAPON);
	player->weaponRotation = rotation;
	view.setCenter(player->rect.left, player->rect.top);
	sightSprite.setPosition(mousePos);
	bgSprite.setPosition(player->rect.left, player->rect.top);
	UpdateSlowMotion(slowMotionBar, bgMusic, motionSound, slowMotion, time);
}