#include "lifebar.h"

Lifebar::Lifebar(Image &image, Vector2f bounds, String Name) : Interface(image, bounds) {
	texture.loadFromImage(image);
	name = Name;
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
};