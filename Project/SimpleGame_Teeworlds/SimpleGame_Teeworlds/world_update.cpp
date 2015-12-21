#include "world.h"

void UpdateText(Text &countEnemiesText, Text &missionTargetText, RenderWindow const &window, int const countEnemies, bool const missionTarget) {
	Vector2f center = window.getView().getCenter();
	if ((countEnemiesText.getColor() == (Color::Red) && (missionTargetText.getColor() == (Color::Red)))) {
		countEnemiesText.setString("TAKE FLAG AT THE END.");
		missionTargetText.setString("");
	}
	else {
		countEnemiesText.setString("Count enemies: " + to_string(countEnemies));
		if (countEnemies == 0) {
			countEnemiesText.setColor(Color::Red);
		}
		if (missionTarget) {
			missionTargetText.setString("Flag captured");
			missionTargetText.setColor(Color::Red);
		}
		else {
			missionTargetText.setString("Flag is not captured");
		}
	}
	missionTargetText.setPosition(center.x - MISSION_TEXT_CORRECTION.x, center.y - MISSION_TEXT_CORRECTION.y);
	countEnemiesText.setPosition(center.x - MISSION_TEXT_CORRECTION.x, center.y - COUNT_ENEMIES_TEXT_CORRECTION);
}

void UpdateCountEnemies(Entity &enemy, int &countEnemies) {
	if ((enemy.name == "hardEnemy") || (enemy.name == "easyEnemy") || (enemy.name == "mediumEnemy")) {
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
	UpdateText(countEnemiesText, missionTargetText, window, countEnemies, missionTarget);
	if (missionTarget) { //TODO
		flagSprite.setPosition(player->rect.left + FLAG_SPRITE_POS_CORRECTION.x, player->rect.top - FLAG_SPRITE_POS_CORRECTION.y);
	}
	playerWeapon->Update(time, rotation,  Vector2f(player->rect.left, player->rect.top - GET_FOURTH), "playerWeapon");
	player->weaponRotation = rotation;
	view.setCenter(player->rect.left, player->rect.top);
	sightSprite.setPosition(mousePos);
	bgSprite.setPosition(player->rect.left, player->rect.top);
}