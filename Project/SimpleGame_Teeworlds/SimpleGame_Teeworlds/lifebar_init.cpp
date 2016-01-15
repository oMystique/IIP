#include "lifebar.h"
#include "entity.h"

Lifebar::Lifebar(Image &image, Vector2f bounds, String Name) : Interface(image, bounds) {
	texture.loadFromImage(image);
	name = Name;
	currentFrame = 0;
	if (name != MOTION_BAR) {
		if (name == PLAYER_BAR) {
			healthSprite.setTexture(texture);
			healthSprite.setTextureRect(PLAYER_LIFEBAR_HP_RECT);
			armorSprite.setTexture(texture);
			armorSprite.setTextureRect(PLAYER_LIFEBAR_ARM_RECT);
		}
		else if (name == ENEMY_BAR) {
			healthSprite.setTexture(texture);
			healthSprite.setTextureRect(IntRect(4, 16, 114, 8)); 
			healthSprite.setOrigin(114 / GET_HALF, 8 / GET_HALF);
			armorSprite.setTexture(texture);
			armorSprite.setTextureRect(IntRect(0, 0, 120, 15)); 
			armorSprite.setOrigin(120 / GET_HALF, 15 / GET_HALF);
		}
		healthSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
		armorSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
	}
	else {
		healthSprite.setTexture(texture);
		healthSprite.setTextureRect(IntRect(4, 16, 0, 8)); 
		healthSprite.setOrigin(114 / GET_HALF, 8 / GET_HALF);
		armorSprite.setTexture(texture);
		armorSprite.setTextureRect(IntRect(0, 0, 120, 15)); 
		armorSprite.setOrigin(120 / GET_HALF, 15 / GET_HALF);
	}
};


void InitLifeBarsForEnemy(vector<Entity*> &entities, Image enemyLifeBar) {
	for (Entity *object : entities) {
		if (object->name == EASY_ENEMY || object->name == MEDIUM_ENEMY || object->name == HARD_ENEMY) {
			object->lifebar = make_unique<Lifebar>(enemyLifeBar, Vector2f(0.f, 0.f), ENEMY_BAR);
		}
	}
}
