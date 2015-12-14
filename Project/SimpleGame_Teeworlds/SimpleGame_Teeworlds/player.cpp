#include "player.h"

Player::Player(Image &image, String name, Level lvl, float x, float y, int w, int h) : Entity(image, name, x, y, w, h) {
	sprite.setTextureRect(IntRect(0, 0, 90, 90));
	sprite.setPosition(x, y);
	action = stay;
	obj = lvl.GetAllObjects();
	currentFrame = 0;
	health = COUNT_PLAYER_HEALTH;
	armor = COUNT_PLAYER_HEALTH;
	flag = false;
	aX = 0;
	aY = 0;
	missionComplete = false;
}