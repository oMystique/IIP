#include "interface.h"

PickUpObj::PickUpObj(Image &image, String name, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
	if (name == "noHealth") {
		sprite.setTextureRect(IntRect(738, 2, 62, 62));
	}
	else if (name == "Health") {
		sprite.setTextureRect(IntRect(673, 2, 62, 62));
	}
	else if (name == "healthPoint") {
		sprite.setTextureRect(IntRect(673, 2, 62, 62));
	}
}

void PickUpObj::Update(float time) {
	if (name == "noHealth") {
		sprite.setTextureRect(IntRect(738, 2, 62, 62));
	}
	else if (name == "Health") {
		sprite.setTextureRect(IntRect(673, 2, 62, 62));
	}
	sprite.setPosition(x, y);
}