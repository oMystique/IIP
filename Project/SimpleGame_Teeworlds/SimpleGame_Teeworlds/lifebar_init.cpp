#include "lifebar.h"

Lifebar::Lifebar(Image &image, int w, int h) : Interface(image, w, h) {
	texture.loadFromImage(image);
	healthSprite.setTexture(texture);
	healthSprite.setTextureRect(IntRect(673, 2, 62, 62));
	healthSprite.setScale(0.4, 0.4);
	armorSprite.setTexture(texture);
	armorSprite.setTextureRect(IntRect(673, 64, 62, 62));
	armorSprite.setScale(0.4, 0.4);
};