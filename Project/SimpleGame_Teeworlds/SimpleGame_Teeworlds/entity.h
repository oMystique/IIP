#pragma once
#include "resource.h"
#include "level.h"

struct Entity {
public:
	vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer, vec;
	int w, h, health;
	bool life, isMove, onGround, isFight;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String name, float x, float y, int w, int h);

	FloatRect getRect();
	FloatRect getEnemyView();

	virtual void Update(float time) = 0;

};