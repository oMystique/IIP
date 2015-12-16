#pragma once
#include "resource.h"
#include "level.h"

struct Entity {
public:
	vector<Object> obj;
	//float dx, dy, x, y, speed, moveTimer, vec;
	//int w, h, health;
	Vector2f boost; //dx, dy
	FloatRect rect;
	float speed;
	float moveTimer;
	float vec;
	float health;

	bool life, isMove, onGround, isFight;
	Texture texture;
	Sprite sprite;
	String name;

	//Entity(Image &image, String name, float x, float y, int w, int h);
	Entity(Image &image, String Name, FloatRect Rect);

	FloatRect getRect();
	FloatRect getEnemyView();

	virtual void Update(float time) = 0;

};