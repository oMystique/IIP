#pragma once
#include "world_init.h"


struct World: public WorldInit {
	void InitWorldObjects();
	void UpdateWorld(float time, Vector2f mousePos, View &view, RenderWindow &window);
	void DrawObjects(RenderWindow *window);
	void PlayerShootEvent(Vector2f mousePos);
	void InteractObjects(float time);
	void DestroyWorldObjects();
private:
	void InitObjects();
	void InteractBetweenEntities(Entity &subject);
	void InteractBetweenPlayerAndEnemy(Entity &subject, float time, bool &isBreak);
	void PlayerPickUpBonuses(Entity &subject);
	void InitImages();
	void InitTextures();
	void InitSounds();
	void InitSprites();

};


float GetRotation(Vector2f mousePos, Vector2f playerPos);
FloatRect GetSpriteRect(const Sprite sprite);
float GetRotation(Vector2f mousePos, Vector2f playerPos);
bool IntersectsRects(FloatRect objectRect, FloatRect subjectRect);
void CalculateShootTime(float &time, Weapon &playerWeapon);
void CheckPerfomMissionTarget(Player &player, Sprite &flagSprite, bool &missionTarget);
float GetDistance(FloatRect &subjectRect, FloatRect &objectRect);
bool IsEnemy(String const name);