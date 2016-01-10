#include "world.h"


void DrawText(Text &missionTargetText, Text &countEnemiesText, RenderWindow &window) {
	window.draw(missionTargetText);
	window.draw(countEnemiesText);
}

void DrawSlowMotion(RenderWindow &window, RectangleShape &rect) {
	Texture txtr;
	Sprite sprt;
	txtr.loadFromFile("images/dust_fog.png");
	sprt.setTexture(txtr);
	rect.setFillColor(Color(168, 168, 168, 100));
	rect.setSize(DEFAULT_WINDOW_SIZE);
	rect.setPosition(window.getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	sprt.setPosition(window.getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	window.draw(rect);
	sprt.setColor(Color(138, 179, 226, 255));
	window.draw(sprt);
}

void DrawEntities(list<Entity*> &entities, RenderWindow &window) {
	for (Entity *&entity : entities) {
		if (entity->sprite.getGlobalBounds().intersects(FloatRect(window.getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF, window.getSize().x, window.getSize().y))) {
			if (entity->name == "easyEnemy" || entity->name == "mediumEnemy" || entity->name == "hardEnemy") {
				int sign = ((entity->boost.x > 0) - (entity->boost.x < 0));
				entity->lifebar->Update(entity->health, 0.f, window, { entity->rect.left + (25.f * -sign), entity->sprite.getGlobalBounds().top });
			}
			window.draw(entity->sprite);
		}
	}
}


void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	DrawEntities(entities, *window);
	window->draw(flagSprite);
	window->draw(playerWeapon->playerWeaponSprite);
	if (player->parachuteOpen) {
		window->draw(player->parachuteSprite);
	}
	window->draw(player->sprite);
	player->lifebar->Update(player->health, player->armor, *window, { 0,0 }); 
	window->draw(sightSprite);
	interfaceText->UpdateText(*window, countEnemies, missionTarget);
	if (slowMotion) {
		DrawSlowMotion(*window, slowMotionRect);
	}
	slowMotionBar->Update(NULL, NULL, *window, { NULL, NULL });
}