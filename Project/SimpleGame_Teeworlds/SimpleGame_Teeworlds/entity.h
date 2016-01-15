#pragma once
#include "level.h"
#include "lifebar.h"
#include <memory>
#include <list>

struct Entity {
public:
	Entity(Image &image, String Name, FloatRect Rect);

	vector<Object> obj;
	Vector2f boost;
	FloatRect rect;
	float speed;
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
	unique_ptr<Lifebar> lifebar = nullptr;
	float currentFrame;
	float countFrames;
	float dmgFrame;
	Vector2f offset;

	FloatRect getRect();
	FloatRect getEnemyView();

	virtual void Update(float time) = 0;
	virtual ~Entity();
};


void SetUnitColor(Sprite &sprite, float &dmgFrame, bool &isDamaged, float &time);
void IsUnitDamaged(float &time, bool &isDamaged, Sprite &sprite, float &dmgFrame);