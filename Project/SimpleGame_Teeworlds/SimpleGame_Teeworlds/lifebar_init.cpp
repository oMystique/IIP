#include "lifebar.h"
#include "entity.h"

Lifebar::Lifebar(Image &image, Vector2f bounds, String Name) : Interface(image, bounds) {
	texture.loadFromImage(image);
	name = Name;
	currentFrame = 0;
	if (name != "motionBar") {
		if (name == "player") {
			healthSprite.setTexture(texture);
			healthSprite.setTextureRect(PLAYER_LIFEBAR_HP_RECT);
			armorSprite.setTexture(texture);
			armorSprite.setTextureRect(PLAYER_LIFEBAR_ARM_RECT);
		}
		else if (name == "enemy") {
			healthSprite.setTexture(texture);
			healthSprite.setTextureRect(IntRect(4, 16, 114, 8)); //TODO: REF
			healthSprite.setOrigin(114 / GET_HALF, 8 / GET_HALF);
			armorSprite.setTexture(texture);
			armorSprite.setTextureRect(IntRect(0, 0, 120, 15)); //TODO: REF
			armorSprite.setOrigin(120 / GET_HALF, 15 / GET_HALF);
		}
		healthSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
		armorSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
	}
	else {
		healthSprite.setTexture(texture);
		healthSprite.setTextureRect(IntRect(4, 16, 0, 8)); //TODO: REF
		healthSprite.setOrigin(114 / GET_HALF, 8 / GET_HALF);
		armorSprite.setTexture(texture);
		armorSprite.setTextureRect(IntRect(0, 0, 120, 15)); //TODO: REF
		armorSprite.setOrigin(120 / GET_HALF, 15 / GET_HALF);
		healthSprite.setColor(Color::Yellow);
	}
};


void InitLifeBarsForEnemy(list<Entity*> &entities, Image enemyLifeBar) {
	for (Entity *&object : entities) {
		if (object->name == "easyEnemy" || object->name == "mediumEnemy" || object->name == "hardEnemy") {
			object->lifebar = make_unique<Lifebar>(enemyLifeBar, Vector2f(0.f, 0.f), "enemy");
		}
	}
}
