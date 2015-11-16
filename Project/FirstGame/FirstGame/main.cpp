#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <thread>
#include <chrono>
#include "view.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>

#include "TinyXML/tinyxml.h"

using namespace sf;
////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer, vec;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setScale(0.36, 0.36);
	}

	FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	FloatRect getEnemyview() {//ф-ция получения поля зрения врага.
		return FloatRect(x, y, w + vec, h);// vec вектор взгляда врага
	}

	FloatRect getMediumEnemyView() {//ф-ция получения поля зрения врага.
		return FloatRect(x, y, w + vec, h + vec);// vec вектор взгляда врага
	}


	virtual void update(float time) = 0; 
};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;
	int playerScore;
	bool flag;
	bool missionComplete;
	float currentFrame;


	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; obj = lev.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(37, 0, 90, 90));
			currentFrame = 0;
			health = 1000;
			flag = false;
			missionComplete = false;
		}
	}

	void animation(float time)
	{
		if (state == right) { currentFrame += 0.005*time; if (currentFrame > 5) currentFrame -= 5; sprite.setTextureRect(IntRect(180 * int(currentFrame), 0, 90, 90)); }
		if (state == left) { currentFrame += 0.005*time; if (currentFrame > 5) currentFrame -= 5; sprite.setTextureRect(IntRect(37 * int(currentFrame), 0, 90, 90)); }
	}


	void control() {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				state = left; speed = 0.1; //sprite.setTextureRect(IntRect(37, 0, 90, 90)); //sprite.setScale(0.33, 0.33);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				state = right; speed = 0.1; //sprite.setTextureRect(IntRect(180, 0, 90, 90)); //sprite.setScale(0.33, 0.33);
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
				state = jump; dy = -0.6; onGround = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
			}
		}
	}

	bool stateWeapon(bool stateNow) {
		if (stateNow) {
			sprite.setTextureRect(IntRect(37, 0, 90, 90));
		}
		else {
			sprite.setTextureRect(IntRect(180, 0, 90, 90));
		}
		return stateNow;
	}



	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if ((obj[i].name == "finish") && (flag)) {
					missionComplete = true;
				}
			}
	}

	void update(float time)
	{
		animation(time);
		control();
		switch (state)
		{
		case right:dx = speed; break;
		case left:dx = -speed; break;
		case up: break;
		case down: dx = 0; break;
		case stay: break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);
		y += dy*time;
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		setPlayerCoordinateForView(x, y);
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;
	}
};

/*Texture noHealthTexture;
noHealthTexture.loadFromFile("images/weapons.png");

Sprite noHealthSprite;
noHealthSprite.setTexture(noHealthTexture);
noHealthSprite.setTextureRect(IntRect(738, 2, 61, 61));
noHealthSprite.setPosition(1150, 10);*/

class PickUpObj :public Entity {
public:
	int dx = 0.9;
	int dy = 0.9;
	PickUpObj(Image &image, String Name, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		if (name == "noHealth") {
			sprite.setTextureRect(IntRect(738, 2, 62, 62));
		}
		else if (name == "Health") {
			sprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
		else if (name == "healthPoint") {
			sprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
	}

	void update(float time) {
		if (name == "noHealth") {
			sprite.setTextureRect(IntRect(738, 2, 62, 62));
		}
		else if (name == "Health") {
			sprite.setTextureRect(IntRect(673, 2, 62, 62));
		}
		//x += dx * time;
		//y += dy * time;
		sprite.setPosition(x, y);
	}

};

class Enemy :public Entity {
public:
	enum { left, right, stay } EnemyState;
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("stopEnemy"); //инициализируем.получаем нужные объекты для взаимодействия врага с картой
		if (name == "easyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, 97, 107));
			sprite.scale(-1, 1);
			dx = -0.1;
		}
		else if (name == "mediumEnemy") {
			sprite.setTextureRect(IntRect(0, 0, 244, 230));
			sprite.setScale(-0.15, 0.15);
			//dx = -0.01;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) {x = obj[i].rect.left - w;  if (name == "easyEnemy") { dx = -0.1; } else { dx = -0.01; } sprite.scale(-1, 1); EnemyState = left;}
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; if (name == "easyEnemy") { dx = 0.1; } else { dx = 0.01; } sprite.scale(-1, 1); EnemyState = right; }
			}
	}

	void update(float time)
	{
		switch (EnemyState)
		{
		case right: if (name == "easyEnemy") { dx = 0.18; vec = 450; } else { vec = 750; } break;// 300 дальность взгляда врага.
		case left: if (name == "easyEnemy") { dx = -0.18; vec = -450; } else { vec = -750; }break;
		}
		if (name == "easyEnemy") {
			if (isMove) {
				checkCollisionWithMap(dx, 0);
				x += dx*time;
				sprite.setPosition(x + w / 2, y + h / 2);
			}
			if (health <= 0) {
				life = false; 
			}
		}
		else if (name == "mediumEnemy") {
			if (isMove) {
				//checkCollisionWithMap(dx, 0);
				//x += dx*time;
				sprite.setPosition(x + w / 2, y + h / 2);
			}
			if (health <= 0) {
				life = false;
			}
		}
	}
};


class Bullet :public Entity {//класс пули
public:
	int direction; //направление пули
	float tempy, tempx;
	//int distance = sqrt((tempx - x)*(tempx - x) + (tempy - y)*(tempy - y));
	bool flash;

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir, float tempX, float tempY) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.1;
		w = h = 16;
		tempx = tempX;
		tempy = tempY;
		life = true;
		flash = false;
		dx = x;
		dy = y;
		sprite.setScale(0.2, 0.2);
		if (name == "Bullet") {
			sprite.setTextureRect(IntRect(339, 394, 27, 48));
			sprite.setRotation(90);
		}
		else if (name == "enemyBullet") {
			sprite.setTextureRect(IntRect(321, 271, 60, 36));
		}
		//выше инициализация в конструкторе
	}


	void update(float time)
	{
		x += speed * (tempx - dx); //идем по иксу с помощью вектора нормали
		y += speed * (tempy - dy) ; //идем по игреку так же

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}
		sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
	}
};



int main()
{
	RenderWindow window(VideoMode(1280, 720), "FirstGame. Ildarkin Alexey; PS-22.");
	view.reset(FloatRect(0, 0, 880, 370));	

	bool immortalFlag = false;
	bool missionTarget = false;
	bool scaleWeapon = true;
	bool scaleEnemyWeapon = false;
	bool startFight = false;

	Texture bgTexture;
	bgTexture.loadFromFile("images/fon-nebo.png");

	Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(IntRect(0, 0, 2500, 2500));
	bgSprite.setPosition(0, 0);
	bgSprite.setOrigin(2500 / 2, 2500 / 2);

	window.setMouseCursorVisible(false);

	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("new_map.tmx");

	Image heroImage;
	heroImage.loadFromFile("images/hero1.png");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/easyEnemy.png");
	easyEnemyImage.createMaskFromColor(Color(255, 255, 255));//маска для пули по белому цвету


	Image mediumEnemyImage;
	mediumEnemyImage.loadFromFile("images/mediumEnemy.png");
	mediumEnemyImage.createMaskFromColor(Color(255, 255, 255));//маска для пули по белому цвету

	Image healthImage;
	healthImage.loadFromFile("images/weapons.png");

	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	std::vector<Object> e = lvl.GetObjects("easyEnemy");//все объекты врага на tmx карте хранятся в этом векторе
	std::vector<Object> m = lvl.GetObjects("mediumEnemy");
	std::vector<Object> healthPoints = lvl.GetObjects("healthPoint");
	Object flag = lvl.GetObject("flag");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него

	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 36, 36);//передаем координаты прямоугольника player из карты в координаты нашего игрока

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/weapons.png");//загрузили картинку в объект изображения
	//BulletImage.createMaskFromColor(Color(255, 255, 255));//маска для пули по белому цвету

	Texture flagTexture;
	flagTexture.loadFromFile("images/weapons.png");

	Sprite flagSprite;
	flagSprite.setTexture(flagTexture);
	flagSprite.setTextureRect(IntRect(387, 268, 127, 240));
	flagSprite.setPosition(flag.rect.left, flag.rect.top);
	flagSprite.setScale(0.9, 0.9);


	Texture sightTexture;
	sightTexture.loadFromFile("images/weapons.png");

	Sprite sightSprite;
	sightSprite.setTexture(sightTexture);
	sightSprite.setTextureRect(IntRect(0, 0, 61, 61));
	sightSprite.setPosition(0, 0);
	sightSprite.setScale(0.8, 0.8);


	Texture weaponTexture;
	weaponTexture.loadFromFile("images/weapons.png");

	Sprite weaponSprite;
	weaponSprite.setTexture(weaponTexture);
	//weaponSprite.setTextureRect(IntRect(66, 391, 215, 61));
	weaponSprite.setTextureRect(IntRect(66, 194, 227, 60));
	weaponSprite.setPosition(p.x + 16, p.y + 16);
	weaponSprite.setScale(0.25, 0.25);
	//weaponSprite.setOrigin(215 / 2, 61 / 2);

	Sprite enemyWeaponSprite;
	enemyWeaponSprite.setTexture(weaponTexture);
	//weaponSprite.setTextureRect(IntRect(66, 391, 215, 61));
	enemyWeaponSprite.setTextureRect(IntRect(68, 130, 123, 63));
	enemyWeaponSprite.setScale(-0.3, 0.3);
	enemyWeaponSprite.setOrigin(123 / 2, 63 / 2);


	Texture molotTexture;
	molotTexture.loadFromFile("images/weapons.png");

	Sprite molotSprite;
	molotSprite.setTexture(molotTexture);
	molotSprite.setTextureRect(IntRect(63, 42, 130, 80));
	molotSprite.setScale(0.3, 0.3);
	molotSprite.setOrigin(130 / 2, 80 / 2);

	Texture flashTexture;
	flashTexture.loadFromFile("images/weapons.png");

	Sprite flashSprite;
	flashSprite.setTexture(flashTexture);
	flashSprite.setTextureRect(IntRect(633, 190, 78, 67));
	flashSprite.setOrigin(67 / 2, 78 / 2);


	Texture noHealthTexture;
	noHealthTexture.loadFromFile("images/weapons.png");

	Sprite noHealthSprite;
	noHealthSprite.setTexture(noHealthTexture);
	noHealthSprite.setTextureRect(IntRect(673, 2, 62, 62));
	weaponSprite.setScale(0.25, 0.25);

	SoundBuffer shootBuffer;//создаём буфер для звука
	shootBuffer.loadFromFile("sounds/shoot.ogg");//загружаем в него звук
	Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера
	shoot.setVolume(40);

	SoundBuffer kickHitBuffer;
	kickHitBuffer.loadFromFile("sounds/kickHit.ogg");//загружаем в него звук
	Sound kickHit(kickHitBuffer);//создаем звук и загружаем в него звук из буфера
	kickHit.setVolume(40);


	SoundBuffer enemyDieBuffer;
	enemyDieBuffer.loadFromFile("sounds/catCrash.ogg");//загружаем в него звук
	Sound enemyDie(enemyDieBuffer);//создаем звук и загружаем в него звук из буфера

	Music music;//создаем объект музыки
	music.openFromFile("sounds/fonMM.ogg");//загружаем файл
	music.play();//воспроизводим музыку
	music.setVolume(45);
	music.setLoop(true);

	std::list<Entity*>  entities;
	std::list<PickUpObj*> PUobjs;
	std::list<PickUpObj*>::iterator point;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator at;

	for (int i = 0; i < e.size(); i++) {//проходимся по элементам этого вектора(а именно по врагам) 
		entities.push_back(new Enemy(easyEnemyImage, "easyEnemy", lvl, e[i].rect.left, e[i].rect.top, 36, 36));//и закидываем в список всех наших врагов с карты
	}
	for (int i = 0; i < m.size(); i++) {//проходимся по элементам этого вектора(а именно по врагам) 
		entities.push_back(new Enemy(mediumEnemyImage, "mediumEnemy", lvl, m[i].rect.left, m[i].rect.top, 36, 36));
	}
	for (int i = 0; i < healthPoints.size(); i++) {//проходимся по элементам этого вектора(а именно по врагам) 
		entities.push_back(new PickUpObj(healthImage, "healthPoint", healthPoints[i].rect.left, healthPoints[i].rect.top, 44, 44));
	}
	int counter = 0;
	while (counter != 10) {
		PUobjs.push_back(new PickUpObj(healthImage, "Health", p.x, p.y - 300, 62, 62)); //передаем координаты прямоугольника player из карты в координаты нашего игрока
		counter += 1;
	}
	Clock clock;
	sf::Time delayTime = sf::seconds(0.01);
	int distance = 0;
	float currentFrame = 0;
	float shootTime = 6;
	float shootFlag = false;
	while ((window.isOpen()) && (p.life) && (!p.missionComplete))
	{
		float time = clock.getElapsedTime().asMicroseconds();
		int count = 0;
		clock.restart();
		time = time / 800;
		currentFrame += 0.05*time;
		if (shootFlag) {
			shootTime += 0.005*time;
		}
		float dX = 0;
		float dY = 0;
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		dX = pos.x - p.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
		dY = pos.y - p.y;//он же, координата y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
		float rotationEnemyWeapon = 30;
		//std::cout << rotation << "\n";//смотрим на градусы в консольке
		weaponSprite.setRotation(rotation);//поворачиваем спрайт на эти градусы
		Event event;
		if (currentFrame > 2) {
			flashSprite.setScale(0, 0);
			currentFrame -= 2;
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)) || ((event.type == Event::MouseButtonReleased) && (event.key.code == Mouse::Left))) {
				entities.push_back(new Bullet(BulletImage, "Bullet", lvl, weaponSprite.getPosition().x, weaponSprite.getPosition().y, 24, 23, rotation, pos.x, pos.y));
				shoot.play();
				flashSprite.setPosition(weaponSprite.getPosition().x, weaponSprite.getPosition().y);
				flashSprite.setScale(1.5, 1.5);
			}
			else if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape)) {
				if (!immortalFlag) { 
					immortalFlag = true; 
				}
				else {
					immortalFlag = false;
				}
			}
		}

		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->life == false) {
				if (b->name == "easyEnemy")
				{
					enemyDie.play();
				}
				else if (b->name == "mediumEnemy") {
					scaleEnemyWeapon = false; 
				}
				it = entities.erase(it); delete b; 
			}// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}


		for (it = entities.begin(); it != entities.end(); it++) {
			for (at = entities.begin(); at != entities.end(); at++) {
				if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy")))) {
					(*it)->health -= 13;
					(*at)->life = false;
				}
			}
			if (((*it)->name == "easyEnemy") || ((*it)->name == "mediumEnemy") || ((*it)->name == "enemyBullet")) {
				if ((*it)->name == "mediumEnemy") {
					distance = sqrt((p.x - (*it)->x)*(p.x - (*it)->x) + (p.y - (*it)->y)*(p.y - (*it)->y));
				}
				if ((*it)->getRect().intersects(p.getRect())) {
					(*it)->isMove = false;
					if (!kickHit.getStatus()) {
						kickHit.play();
					}
					if (!immortalFlag) 
					{

						if ((*it)->name == "enemyBullet") {
							p.health -= 100;
							(*it)->life = false;
						}
						else {
							p.health -= 7;
						}
					}
				} 
				else {
					(*it)->isMove = true;
					if ((((*it)->getEnemyview().intersects(p.getRect())) && ((*it)->name == "easyEnemy")) || ((distance < 430) && ((*it)->name == "mediumEnemy"))) {
						if ((*it)->name == "easyEnemy") {
							(*it)->dx = p.dx;
						}
						if ((*it)->name == "mediumEnemy") { 
							dX = p.x - (*it)->x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
							dY = p.y - (*it)->y;//он же, координата y
							rotationEnemyWeapon = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
							(*it)->isMove = false;
							if (shootTime > 4) {
								entities.push_back(new Bullet(BulletImage, "enemyBullet", lvl, (*it)->x, (*it)->y + 21, 24, 23, rotation, p.x + 11, p.y + 11));
								shootTime = 0;
								shootFlag = true;
								flashSprite.setPosition((*it)->x, (*it)->y + 21);
								flashSprite.setScale(1.5, 1.5);
								break;
							}
						}
						(*it)->sprite.setColor(Color::Red);
					}
					else {
						if ((*it)->name == "mediumEnemy") {
							(*it)->isMove = true;
						}
						(*it)->sprite.setColor(Color::White);
					}
				}
			}
			else if (((*it)->name == "healthPoint") && ((*it)->getRect().intersects(p.getRect()) && (p.health < 1000))) {
				p.health += 100;
				(*it)->life = false;
			}
		}
		//counter = Cpos.x + 600;
		//counter = p.x + 500;
		counter = view.getCenter().x + 400;
		int healthCounter = 1000;
		for (point = PUobjs.begin(); point != PUobjs.end(); point++) {
			if (p.health < healthCounter) {
				(*point)->name = "noHealth";
			}
			else {
				(*point)->name = "Health";
			}
			(*point)->x = counter;
			//(*point)->y = p.y - 220;
			(*point)->y = view.getCenter().y - 150;
			//(*point)->y = Cpos.y - 150;
			(*point)->update(time);
			counter -= 35;
			healthCounter -= 100;
		}

		p.update(time);
		window.setView(view);
		window.clear();
		sightSprite.setPosition(pos.x - 24.5, pos.y - 24.5);
		bgSprite.setPosition(p.x, p.y);
		window.draw(bgSprite);
		lvl.Draw(window);

		if (!missionTarget) {
			if (FloatRect(flagSprite.getPosition().x, flagSprite.getPosition().y, 127, 240).intersects(p.getRect())) {
				missionTarget = true;
				flagSprite.setScale(0.3, 0.3); 
				p.flag = true;
			}
		}
		else {
			flagSprite.setPosition(p.x + 20, p.y - 50);
		}
		if ((-90.0 <= rotation) && (rotation <= 90.0)) {
			weaponSprite.setPosition(p.x + 32, p.y + 20);
			if (!scaleWeapon) {
				weaponSprite.scale(1, -1);
				scaleWeapon = true;
			}
			p.stateWeapon(false);
		}
		else {
			weaponSprite.setPosition(p.x + 21, p.y + 20);
			if (scaleWeapon) {
				weaponSprite.scale(1, -1);
				scaleWeapon = false;
			}
			p.stateWeapon(true);
		}

		for (it = entities.begin(); it != entities.end(); it++) {
			if ((*it)->name == "easyEnemy") {
				if ((*it)->sprite.getScale().x < 0) {
					molotSprite.setPosition((*it)->x - 7, (*it)->y + 30);
					molotSprite.setRotation(210);
				}
				else {
					molotSprite.setPosition((*it)->x + 45, (*it)->y + 30);
					molotSprite.setRotation(-30);
				}
				window.draw(molotSprite);
			}
			if ((*it)->name == "mediumEnemy") {
				if ((*it)->sprite.getScale().x < 0) {
					enemyWeaponSprite.setPosition((*it)->x - 7, (*it)->y + 30);
					enemyWeaponSprite.setRotation(rotationEnemyWeapon);
				}
				else {
					enemyWeaponSprite.setPosition((*it)->x + 45, (*it)->y + 30);
					enemyWeaponSprite.setRotation(rotationEnemyWeapon);
				}
				if ((-90.0 <= rotationEnemyWeapon) && (rotationEnemyWeapon <= 90.0)) {
					if (!scaleEnemyWeapon) {
						enemyWeaponSprite.scale(1, -1);
						(*it)->sprite.scale(-1, 1);
						scaleEnemyWeapon = true;
					}
				}
				else {
					if (scaleEnemyWeapon) {
						enemyWeaponSprite.scale(1, -1);
						(*it)->sprite.scale(-1, 1);
						scaleEnemyWeapon = false;
					}
				}
				window.draw(enemyWeaponSprite);
			}
			window.draw((*it)->sprite);
		}
		window.draw(flagSprite);
		window.draw(weaponSprite);
		window.draw(p.sprite);
		window.draw(sightSprite);
		window.draw(flashSprite);
		for (point = PUobjs.begin(); point != PUobjs.end(); point++) {
			window.draw((*point)->sprite);
		}
		window.display();
	}
	return 0;
}