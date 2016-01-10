#pragma once
#include "interface.h"
#include <vector>
#include <list>

struct Lifebar: public Interface {
	Lifebar(Image &image, Vector2f bounds, String Name);
	
	String name;
	float currentFrame;
	void Update(float const healthCount, float const armorCount, RenderWindow &window, Vector2f const pos);
	bool BurnMotionParameter(float time);
	void Draw(RenderWindow &window);
	void SetParameterForMotion();
private:
	void UpdatePlayerLifeBar(float const healthCount, float const armorCount, RenderWindow &window);
	void UpdateEnemyLifeBar(float const healthCount, Vector2f const pos);
	void UpdateSlowMotionBar(RenderWindow &window);

	Sprite healthSprite;
	Sprite armorSprite;
};

struct Entity;
void InitLifeBarsForEnemy(list<Entity*> &entities, Image enemyLifeBar);