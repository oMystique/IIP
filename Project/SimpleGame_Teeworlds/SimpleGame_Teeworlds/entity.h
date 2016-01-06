#pragma once
#include "level.h"
#include "lifebar.h"
#include <memory>

struct Entity {
public:
	vector<Object> obj;
	Vector2f boost;
	FloatRect rect;
	float speed;
	float moveTimer;
	float vec;
	float health;

	enum {
		moveLeft,
		moveRight,
		jump,
		stay,
		down
	} action;

	bool life;
	bool isMove;
	bool onGround;
	bool isFight;
	bool isDamaged;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String Name, FloatRect Rect);

	unique_ptr<Lifebar> lifebar;


	FloatRect getRect();
	FloatRect getEnemyView();

	virtual void Update(float time) = 0;
	virtual ~Entity();
};