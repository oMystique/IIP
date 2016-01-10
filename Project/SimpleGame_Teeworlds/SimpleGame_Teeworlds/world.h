#pragma once
#include "world_init.h"


struct World: public WorldInit {
	void InitWorldObjects();
	void UpdateWorld(float time, Vector2f mousePos, View &view, RenderWindow &window);
	void DrawObjects(RenderWindow *window);
	void ShootEvent(Vector2f mousePos);
	void InteractObjects(float time);
	void DestroyWorldObjects();
private:
	void InitObjects();
	void InitImages();
	void InitTextures();
	void InitSounds();
	void InitSprites();
	float GetRotation(Vector2f mousePos, Vector2f playerPos);
};