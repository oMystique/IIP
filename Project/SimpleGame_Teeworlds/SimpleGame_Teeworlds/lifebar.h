#pragma once
#include "interface.h"
#include <vector>

struct Lifebar: public Interface {
	Lifebar(Image &image, Vector2f bounds, String Name);
	
	String name;
	void Update(float const healthCount, float const armorCount, RenderWindow &window, Vector2f const pos);
	void Draw(RenderWindow &window);
private:
	void UpdatePlayerLifeBar(float const healthCount, float const armorCount, RenderWindow &window);
	void UpdateEnemyLifeBar(float const healthCount, Vector2f const pos);
	Sprite healthSprite;
	Sprite armorSprite;
};