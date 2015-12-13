#pragma once
#include "world_init.h"


struct World: public WorldInit {
	void InitWorldObjects();
	void UpdateWorld(float time, float mouseX, float mouseY, View &view);
	void DrawObjects(RenderWindow *window);
	void Shoot(String subject, float mouseX, float mouseY);
	void InteractObjects();
private:
	void InitImages();
	void InitTextures();
	void InitSounds();
	void InitObjects();
	void InitSprites();
};