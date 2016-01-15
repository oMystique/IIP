#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

static const String MOTION_BONUS = "motionBonus";
static const String ARMOR_BONUS = "armorPoint";
static const String HEALTH_BONUS = "healthPoint";

static const String DIE = "die";

static const String SOLID_COLLISION = "solid";
static const String PLAYER_BULLET = "Bullet";
static const String ENEMY_BULLET = "enemyBullet";

static const String DIE_SMALL_TEXTURE_PATH = "images/die.png";

static const String  MEDIUM_ENEMY = "mediumEnemy";
static const String  STOP_ENEMY_COLLISION = "stopEnemy";
static const String DIE_SOUND_PATH = "sounds/catCrash.ogg";
static const String EASY_ENEMY = "easyEnemy";
static const String HARD_ENEMY = "hardEnemy";

static const String PLAYER_BAR = "player";
static const String MOTION_BAR = "motionBar";
static const String ENEMY_BAR = "enemy";

static const String MENU_MUSIC_PATH = "sounds/menuMusic(avicii).ogg";

static const String INTERFACE_FONT_PATH = "font.ttf";

static const String TAKE_FLAG_AT_THE_END = "TAKE FLAG AT THE END.";
static const String COUNT_ENEMIES = "Count enemies ";
static const String FLAG_CAPTURED = "Flag captured";
static const String FLAG_NOT_CAPTURED = "Flag is not captured";

static const String PARACHUTE_TEXTURE_PATH = "images/parachute.png";
static const String PARACHUTE_SOUND_PATH = "sounds/openParachute.ogg";
static const String FINISH = "finish";

static const String DIE_BIG_TEXTURE_PATH = "images/unitDie.png";
static const String PLAYER_WEAPON = "playerWeapon";

static const String DUST_FOG_TEXTURE_PATH = "images/dust_fog.png";

static const String PLAYER_IMAGE_PATH = "images/anim_player.png";
static const String EASY_ENEMY_IMAGE_PATH = "images/easy_enemy.png";
static const String MEDIUM_ENEMY_IMAGE_PATH = "images/medium_enemy.png";
static const String TEXTURE_COLLECTION_PATH = "images/weapons.png";
static const String PLAYER_WEAPON_IMAGE_PATH = "images/shotgun.png";
static const String HARD_ENEMY_IMAGE_PATH = "images/fireman.png";
static const String ENEMY_LIFEBAR_IMAGE_PATH = "images/enemyLife.png";
static const String MOTION_BONUS_IMAGE_PATH = "images/motionBonus.png";
static const String BACKGROUND_TEXTURE_PATH = "images/fon-nebo.png";
static const String SHOOT_SOUND_PATH = "sounds/shoot.ogg";
static const String DAMAGED_SOUND_PATH = "sounds/kickHit.ogg";
static const String MISS_SOUND_PATH = "sounds/miss1.ogg";
static const String MOTION_SOUND_PATH = "sounds/motionSound.ogg";

static const String PRESS_R_TO_RESTART = "PRESS R TO RESTART";
static const String PRESS_PAUSE_TO_CONTINUE = "OR PRESS PAUSE TO CONTINUE";
static const String GAME_OVER = "   GAME OVER";
static const String GAME_STOPPED = "GAME STOPPED";
static const String BACKGROUND_MENU_IMAGE_PATH = "images/bgmenu.png";