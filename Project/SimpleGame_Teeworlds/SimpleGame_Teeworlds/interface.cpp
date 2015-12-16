#include "interface.h"

Interface::Interface(Image &image, Vector2f rect) {
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}