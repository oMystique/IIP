#include "additAnimation.h"

AdditionalAnimation::AdditionalAnimation() {
	texture.loadFromFile("images/weapons.png");
	sprite.setTexture(texture);
	currentFrame = 0;
	sprite.setTextureRect(IntRect(255, 34, 33, 29)); //TODO: REFACTORING.
}