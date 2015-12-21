#pragma once
#include "resource.h"
#include "level.h"

struct Entity {
public:
	vector<Object> obj;
	Vector2f boost;
	FloatRect rect;
	float speed;
	float moveTimer;
	float vec;
	float health;

	bool life, isMove, onGround, isFight;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String Name, FloatRect Rect);

	FloatRect getRect();
	FloatRect getEnemyView();

	virtual void Update(float time) = 0;

};