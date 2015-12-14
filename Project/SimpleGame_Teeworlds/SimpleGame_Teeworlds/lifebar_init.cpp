#include "lifebar.h"

Lifebar::Lifebar(Image &image, int w, int h) : Interface(image, w, h) {
	sprite.setTextureRect(IntRect(673, 2, 62, 62));
	sprite.setScale(0.4, 0.4);
};