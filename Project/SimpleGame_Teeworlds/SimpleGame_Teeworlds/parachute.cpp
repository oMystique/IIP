#include "parachute.h"

Parachute::Parachute() {
	parachuteOpen = false;
	parachuteTexture.loadFromFile(PARACHUTE_TEXTURE_PATH);
	parachuteSprite.setTexture(parachuteTexture); 
	parachuteSprite.setTextureRect(PARACHUTE_SPRITE_RECT);
	parachuteSprite.setOrigin(float(PARACHUTE_SPRITE_RECT.width) / GET_HALF, float(PARACHUTE_SPRITE_RECT.height));
	parachuteSprite.setScale(PARACHUTE_SCALE, PARACHUTE_SCALE);

	parachuteOpenBuffer.loadFromFile(PARACHUTE_SOUND_PATH);
	parachuteOpenSound.setBuffer(parachuteOpenBuffer);
}


void Parachute::Update(Vector2f const pos) {
	if (parachuteOpen) { 
		parachuteSprite.setPosition(pos.x + 10.f, pos.y); 
		if (!parachuteOpenSound.getStatus()) {
			parachuteOpenSound.play();
		}
	}
	else {
		parachuteOpenSound.stop();
	}
}