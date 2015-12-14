#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

//**********CONST_BLOCK**********\\

//PARAMETHERS_______________________:
static const float COUNT_PLAYER_HEALTH = 1000.f;
static const float BONUS_HEALTH = 100.f;

//SCALE_____________________________:
static const float WEAPON_SCALE = 0.3f;
static const float BULLET_SCALE = 0.2f;
static const float QUARTER_CIRCLE = 90.f;
static const float MEDIUM_ENEMY_SCALE = 0.15f;
static const float ENTITY_BASE_SCALE = 0.4f;
static const float FLAG_SCALE = 0.9f;
static const float SIGHT_SCALE = 0.8f;


//SPEED______________________________:
static const float GAME_SPEED = 800.f;
static const float DEFAULT_UNIT_SPEED = 0.1f;
static const float PLAYER_JUMP_SPEED = 0.6f;
static const float DEFAULT_ENEMY_SHOOT_SPEED = 2000.f;


//CORRECTION_________________________:
static const float FRAME_CORRECTION = 0.005f;
static const float SOUND_VOLUME = 40.f;
static const Vector2f LIFEBAR_POS_CORRECTION = { 2.3f, 176.f };


//OTHER______________________________:
static const float SHOOT_TIME = 6.f;
static const float GET_HALF = 2.f;
static const float STEP_BONUSES_ANIMATION = 0.01f;
static const float ENEMY_VIEW_RANGE = 450.f;
static const float GET_CIRCLE_HALF = 180.f;

//***********************************\\





/*std::weak_ptr<Application> paPP;
std::shared_ptr<Application> pSharedApp = std::make_shared<Application>();
std::unique_ptr<Application> pApp = std::make_unique<Application>();*/