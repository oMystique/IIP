#include "lifebar.h"

Lifebar::Lifebar(Image &image, Vector2f bounds) : Interface(image, bounds) {
	texture.loadFromImage(image);
	healthSprite.setTexture(texture);
	healthSprite.setTextureRect(LIFEBAR_HP_RECT);
	healthSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
	armorSprite.setTexture(texture);
	armorSprite.setTextureRect(LIFEBAR_ARM_RECT);
	armorSprite.setScale(LIFEBAR_ELEMENT_SCALE, LIFEBAR_ELEMENT_SCALE);
};