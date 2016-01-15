#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {
	Lifebar(Image &image, Vector2f bounds, String Name);
	void SetParameterForMotion();
	bool IsBurnMotionParameter(float time);
	void Update(float const healthCount, float const armorCount, RenderWindow &window, Vector2f const pos);
private:
	String name;
	float currentFrame;
	Sprite healthSprite;
	Sprite armorSprite;

	void UpdatePlayerLifeBar(float const healthCount, float const armorCount, RenderWindow &window);
	void UpdateEnemyLifeBar(float const healthCount, Vector2f const pos);
	void UpdateSlowMotionBar(RenderWindow &window);
	void Draw(RenderWindow &window);
};

struct Entity;
void InitLifeBarsForEnemy(vector<Entity*> &entities, Image enemyLifeBar);