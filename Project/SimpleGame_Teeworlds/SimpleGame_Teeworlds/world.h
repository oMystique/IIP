#pragma once
#include "world_init.h"


struct World: public WorldInit {
	void InitWorldObjects();
	void UpdateWorld(float time, Vector2f mousePos, View &view, RenderWindow &window);
	void DrawObjects(RenderWindow *window);
	void Shoot(String subject, Vector2f mousePos);
	void InteractObjects(float time);
private:
	void InitImages();
	void InitTextures();
	void InitSounds();
	void InitObjects();
	void InitSprites();
	float GetRotation(Vector2f mousePos, Vector2f playerPos);
};