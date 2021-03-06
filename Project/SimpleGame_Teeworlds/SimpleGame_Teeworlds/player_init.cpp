#include "player.h"

Player::Player(Image &image, String name, Level lvl, FloatRect rect) : Entity(image, name, rect) {
	sprite.setTextureRect(IntRect(0, 0, int(PLAYER_SPRITE_BOUND), int(PLAYER_SPRITE_BOUND)));
	sprite.setPosition(rect.left, rect.top);
	action = down;
	obj = lvl.GetAllObjects();
	health = COUNT_PLAYER_HEALTH;
	armor = COUNT_PLAYER_HEALTH;
	missionComplete = false; 
	flag = false; 

	parachute = make_unique<Parachute>();
}