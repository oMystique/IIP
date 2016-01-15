#include "world.h"


void DrawText(Text &missionTargetText, Text &countEnemiesText, RenderWindow &window) {
	window.draw(missionTargetText);
	window.draw(countEnemiesText);
}

void DrawSlowMotion(RenderWindow &window, RectangleShape &rect) {
	Texture texture;
	Sprite sprite;
	texture.loadFromFile(DUST_FOG_TEXTURE_PATH);
	sprite.setTexture(texture);
	rect.setFillColor(Color(168, 168, 168, 110));
	rect.setSize(DEFAULT_WINDOW_SIZE);
	rect.setPosition(window.getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	sprite.setPosition(window.getView().getCenter().x - DEFAULT_WINDOW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_WINDOW_SIZE.y / GET_HALF);
	window.draw(rect);
	sprite.setColor(Color(138, 179, 226, 255));
	window.draw(sprite);
}

void DrawEntities(vector<Entity*> &entities, RenderWindow &window) {
	for (Entity *&entity : entities) {
		if (entity->sprite.getGlobalBounds().intersects(FloatRect(window.getView().getCenter().x - DEFAULT_VIEW_SIZE.x / GET_HALF, window.getView().getCenter().y - DEFAULT_VIEW_SIZE.y / GET_HALF, DEFAULT_VIEW_SIZE.x, DEFAULT_VIEW_SIZE.y))) {
			if (IsEnemy(entity->name)) {
				int sign = ((entity->boost.x > 0) - (entity->boost.x < 0));
				entity->lifebar->Update(entity->health, 0.f, window, { entity->rect.left + (25.f * -sign), entity->sprite.getGlobalBounds().top });
			}
			window.draw(entity->sprite);
		}
		else if (entity->name == PLAYER_BULLET) {
			entity->life = false;
		}
	}
}


void World::DrawObjects(RenderWindow *window) {
	window->draw(bgSprite);
	lvl.Draw(*window);
	DrawEntities(entities, *window);
	window->draw(flagSprite);
	if (player->health > BONUS_HEALTH) {
		window->draw(playerWeapon->playerWeaponSprite);
		if (player->parachute->parachuteOpen) {
			window->draw(player->parachute->parachuteSprite);
		}
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