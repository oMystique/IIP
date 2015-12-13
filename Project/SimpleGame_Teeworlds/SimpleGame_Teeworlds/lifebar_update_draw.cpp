#include "lifebar.h"

void Lifebar::Update(float healthCount) {
	float counter = 1000;
	while (counter != 0) {
		if (healthCount < counter) {
			sprite.setTextureRect(IntRect(738, 2, 62, 62));
		}
		else {
			sprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
	}
}

void Lifebar::Draw(RenderWindow &window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	//for (Sprite spr : sprites[10]) {
		sprite.setPosition(center.x + 10, center.y / 2 + 10);
		window.draw(sprite);
	//}
}