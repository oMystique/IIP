#pragma once
#include "resource.h"

struct Parachute {
	Parachute();

	bool parachuteOpen = false;
	Texture parachuteTexture;
	Sprite parachuteSprite;

	SoundBuffer parachuteOpenBuffer;
	Sound parachuteOpenSound;

	void Update(Vector2f pos);
};