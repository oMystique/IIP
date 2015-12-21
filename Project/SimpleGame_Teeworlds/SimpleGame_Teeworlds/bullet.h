#pragma once
#include "entity.h"

struct Bullet :public Entity {
	//Bullet(Image &image, String name, Level lvl, float x, float y, int w, int h, float mouseX, float mouseY, float rotation);
	Bullet(Image &image, String name, Level lvl, FloatRect rect, Vector2f mouseCoord, float rotation);
	void Update(float time);
	Sprite trackSprite;
private:
	Vector2f temp;
};


void BulletTrackAnimation(RenderWindow &window, Entity &bullet, Sprite sprite);