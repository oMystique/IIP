#pragma once

#include "string_consts.h"

//**********CONST_BLOCK**********\\

//PARAMETHERS_______________________:
static const Vector2f DEFAULT_WINDOW_SIZE = { 1280.f, 720.f };
static const Vector2f DEFAULT_VIEW_SIZE = { 880.f, 410.f };
static const float COUNT_PLAYER_HEALTH = 1000.f;
static const float BONUS_HEALTH = 100.f;
static const IntRect BONUS_HP_RECT = { 673, 2, 62, 62 };
static const IntRect BONUS_ARM_RECT = { 673, 64, 62, 62 };
static const float BOUND_BONUS_ANIMATION = 10.f;
static const IntRect PLAYER_BULLET_RECT = { 339, 394, 27, 48 };
static const IntRect ENEMY_BULLET_RECT = { 321, 271, 60, 36 };
static const float ANIMATION_FRAME = 0.7f;
static const Vector2i EASY_ENEMY_RECT_BOUNDS = { 149, 106 };
static const Vector2i MEDIUM_ENEMY_RECT_BOUNDS = { 301, 109 };
static const IntRect PLAYER_LIFEBAR_HP_RECT = { 673, 2, 62, 62 };
static const IntRect PLAYER_LIFEBAR_ARM_RECT = { 673, 64, 62, 62 };
static const IntRect PLAYER_LIFEBAR_NO_HP_RECT = { 738, 2, 62, 62 };
static const IntRect PLAYER_LIFEBAR_NO_ARM_RECT = { 738, 64, 62, 62 };
static const float PLAYER_SPRITE_BOUND = 90.f;
static const float PLAYER_TEXTURE_RESOLUTION = 179.f;
static const float WEAPON_ANIMATION_FRAME = 0.5f;
static const IntRect WEAPON_SHOOT_RECT = { 0, 0, 265, 68 }; 
static const IntRect WEAPON_NO_SHOOT_RECT = { 0, 68, 265, 68 };
static const IntRect PARACHUTE_SPRITE_RECT = { 0, 0, 300, 372 };
static const Vector2f WEAPON_MISS_ROTATION = { 177.f , 3.f };
static const float DAMAGE_WITH_PLAYER_WEAPON = 15.f;
static const float DAMAGE_TO_PLAYER_WITH_WEAPON = 100.f;
static const Vector2f BULLET_BOUNDS = { 24.f, 23.f };
static const Vector2f DEFAULT_BONUSES_BOUNDS = {44.f, 44.f};
static const Vector2f DEFAULT_UNIT_BOUNDS = { 36.f, 36.f };
static const Vector2f DEFAULT_WEAPON_BOUNDS = { 227.f, 60.f };
static const IntRect FLAG_SPRITE_RECT = { 387, 268, 127, 240 };
static const IntRect SIGHT_SPRITE_RECT = { 0, 0, 61, 61 };
static const float DEFAULT_BULLET_SPEED = 2.7f;
static const float HARD_ENEMY_ACT_DISTANCE = 65.f;
static const float ENEMY_MELEE_DAMAGE = 0.3f;


//SCALE_____________________________:
static const float WEAPON_SCALE = 0.3f;
static const float BULLET_SCALE = 0.2f;
static const float QUARTER_CIRCLE = 90.f;
static const float MEDIUM_ENEMY_SCALE = 0.3f;
static const float ENTITY_BASE_SCALE = 0.4f;
static const float FLAG_MAX_SCALE = 0.9f;
static const float SIGHT_SCALE = 0.6f;
static const float LIFEBAR_ELEMENT_SCALE = 0.4f;
static const float FLAG_MIN_SCALE = 0.3f;
static const float BG_SPRITE_SCALE = 0.47f;
static const float PARACHUTE_SCALE = 0.5f;
static const float BURN_MOTION_SPRITE_SCALE = 1.05f;

//SPEED______________________________:
static const float DEFAULT_GAME_SPEED = 800.f;
static const float SLOW_GAME_SPEED = 2000.f;
static const float DEFAULT_UNIT_SPEED = 0.1f;
static const float PLAYER_JUMP_SPEED = 0.6f;
static const float DEFAULT_ENEMY_SHOOT_SPEED = 2000.f;
static const float HARD_ENEMY_BOOST_SPEED = 0.1999f;


//CORRECTION_________________________:
static const Vector2f WEAPON_CORRECTION_COORD_X = { 32.f, 25.f };
static const float WEAPON_CORRECTION_COORD_Y = 20.f;
static const float FRAME_CORRECTION = 0.005f;
static const float SOUND_VOLUME = 20.f;
static const Vector2f LIFEBAR_POS_CORRECTION = { 2.3f, 196.f };
static const float LIFEBAR_ARM_POS_CORRECTION = 30.f;
static const float ANIMATION_TIME_BOOST = 0.005f;
static const float PLAYER_BOOST_CORRECTION = 0.0015f;
static const Vector2f ENEMY_SHOOT_CORRECTION = { 11.f, 11.f };
static const Vector2f FLAG_SPRITE_POS_CORRECTION = { 20.f, 50.f };
static const Vector2f MISSION_TEXT_CORRECTION = { 430.f, 180.f };
static const float COUNT_ENEMIES_TEXT_CORRECTION = 210.f;


//OTHER______________________________:
static const float SHOOT_TIME = 6.f;
static const float GET_HALF = 2.f;
static const float GET_FOURTH = 4.f;
static const float GET_THIRD = 3.f;
static const float STEP_BONUSES_ANIMATION = 0.01f;
static const float ENEMY_VIEW_RANGE = 440.f;
static const float GET_CIRCLE_HALF = 180.f;
static const float RANDOM_RANGE = 500.f;

//***********************************\\