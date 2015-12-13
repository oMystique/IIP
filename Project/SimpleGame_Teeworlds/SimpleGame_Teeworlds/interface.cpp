#include "interface.h"

Interface::Interface(Image &image, int w, int h) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}