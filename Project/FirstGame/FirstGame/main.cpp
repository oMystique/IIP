#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include <vector>
#include <list>

#include "TinyXML/tinyxml.h"

using namespace sf;
////////////////////////////////////����� �����-��������//////////////////////////
class Entity {
public:
	std::vector<Object> obj;//������ �������� �����
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

	FloatRect getRect() {//�-��� ��������� ��������������. ��� �����,������� (���,�����).
		return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
	}

	FloatRect getEnemyview() {//�-��� ��������� ���� ������ �����.
		return FloatRect(x, y, w + vec, h);// vec ������ ������� �����
	}

	virtual void update(float time) = 0; 
};
////////////////////////////////////////////////////����� ������////////////////////////

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;
	int playerScore;


	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; obj = lev.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(37, 0, 90, 90));
		}
	}

	void control() {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				state = left; speed = 0.1; sprite.setTextureRect(IntRect(37, 0, 90, 90)); //sprite.setScale(0.33, 0.33);
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				state = right; speed = 0.1; sprite.setTextureRect(IntRect(180, 0, 90, 90)); //sprite.setScale(0.33, 0.33);
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
				state = jump; dy = -0.6; onGround = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
			}
		}
	}

	void stateWeapon(bool stateNow) {
		if (stateNow) {
			sprite.setTextureRect(IntRect(37, 0, 90, 90));
		}
		else {
			sprite.setTextureRect(IntRect(180, 0, 90, 90));
		}
	}



	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	}

	void update(float time)
	{
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

class HealthPoints :public Entity {
public:
	HealthPoints(Image &image, String Name, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		if (name == "noHealth") {
			sprite.setTextureRect(IntRect(738, 2, W, H));
		}
		else if (name == "Health") {
			sprite.setTextureRect(IntRect(673, 2, W, H));
		}
	}

	void update(float time) {
		int dx = x;
		for (int counter = 0; counter <= 100; counter += 10) {
			dx -= 63;
			if (health <= counter) {
				name = "Health";
			}
			else {
				name = "noHealth";
			}
			sprite.setPosition(dx, y);
		}

	}
};

class Enemy :public Entity {
public:
	enum { left, right, stay } EnemyState;

	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("solid");//��������������.�������� ������ ������� ��� �������������� ����� � ������
		if (name == "easyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, 97, 107));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				//if (obj[i].name == "solid"){//���� ��������� ����������� (������ � ������ solid)
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); EnemyState = left; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); EnemyState = right; }
				//}
			}
	}

	void update(float time)
	{
		switch (EnemyState)
		{
		case right: vec = 110; break;// 300 ��������� ������� �����.
		case left: vec = -110; break;
		}
		if (name == "easyEnemy") {
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}
};

/*class Weapon :public Entity {
public:

};*/

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����
	float tempy, tempx;
	int distance = sqrt((tempx - x)*(tempy - x) + (tempy - y)*(tempy - y));

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir, float tempX, float tempY) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.1;
		w = h = 16;
		tempx = tempX;
		tempy = tempY;
		life = true;
		dx = x;
		dy = y;
		//���� ������������� � ������������
	}


	void update(float time)
	{
		x += speed * (tempx - dx);//���� �� ���� � ������� ������� �������
		y += speed * (tempy - dy) ;//���� �� ������ ��� ��

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
			if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			{
				life = false;// �� ���� �������
			}
		}
		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	}
};


int main()
{
	RenderWindow window(VideoMode(1180, 620), "FirstGame");
	view.reset(FloatRect(0, 0, 1180, 620));	

	Texture bgTexture;
	bgTexture.loadFromFile("images/fon-nebo.png");

	Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(IntRect(0, 0, 2500, 2500));
	bgSprite.setPosition(0, 0);
	bgSprite.setOrigin(2500 / 2, 2500 / 2);

	window.setMouseCursorVisible(false);

	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("new_map.tmx");

	Image heroImage;
	heroImage.loadFromFile("images/hero1.png");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/easyEnemy.png");
	easyEnemyImage.createMaskFromColor(Color(255, 255, 255));//����� ��� ���� �� ������ �����

	Image healthImage;
	healthImage.loadFromFile("images/weapons.png");

	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	std::vector<Object> e = lvl.GetObjects("easyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������

	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 36, 36);//�������� ���������� �������������� player �� ����� � ���������� ������ ������

	HealthPoints health(healthImage, "Health", p.x, p.y, 62, 62);//�������� ���������� �������������� player �� ����� � ���������� ������ ������

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(255, 255, 255));//����� ��� ���� �� ������ �����

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
	weaponSprite.setTextureRect(IntRect(66, 391, 215, 61));
	weaponSprite.setPosition(p.x + 16, p.y + 16);
	weaponSprite.setScale(0.25, 0.25);
	weaponSprite.setOrigin(215 / 2, 61 / 2);


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


	//Texture noHealthTexture;
	//noHealthTexture.loadFromFile("images/weapons.png");

	/*Sprite noHealthSprite;
	noHealthSprite.setTexture(noHealthTexture);
	noHealthSprite.setTextureRect(IntRect(673, 2, 62, 62));
	weaponSprite.setScale(0.25, 0.25);
	//noHealthSprite.setPosition(p.x - 100, p.y - 100);*/

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator at;

	for (int i = 0; i < e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(easyEnemyImage, "easyEnemy", lvl, e[i].rect.left, e[i].rect.top, 36, 36));//� ���������� � ������ ���� ����� ������ � �����

	Clock clock;
	while ((window.isOpen()) && (p.life == true))
	{
		float time = clock.getElapsedTime().asMicroseconds();
		int count = 0;
		clock.restart();
		time = time / 800;
		float dX = 0;
		float dY = 0;
		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
		dY = pos.y - p.y;//�� ��, ���������� y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
		//std::cout << rotation << "\n";//������� �� ������� � ���������
		weaponSprite.setRotation(rotation);//������������ ������ �� ��� �������
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space) {
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, weaponSprite.getPosition().x - 15, weaponSprite.getPosition().y - 10, 24, 23, rotation, pos.x, pos.y));
					//flashSprite.setPosition(weaponSprite.getPosition().x, weaponSprite.getPosition().y);
				}
				/*if (event.key.code == sf::Keyboard::Escape) {
					//MENU;
				}*/
			}
		}
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false) { it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		for (it = entities.begin(); it != entities.end(); it++) {
			for (at = entities.begin(); at != entities.end(); at++) {
				if ((*it)->getRect().intersects((*at)->getRect()) && (((*at)->name == "Bullet") && ((*it)->name == "easyEnemy"))) {
					(*it)->health -= 15;
					(*at)->life = false;
				}
				if ((*it)->getRect().intersects(p.getRect()) && ((*it)->name == "easyEnemy"))
				{
					p.health -= 30 ;
				}
			}
		}

		p.update(time);
		health.update(time);
		window.setView(view);
		window.clear();
		sightSprite.setPosition(pos.x - 24.5, pos.y - 24.5);
		bgSprite.setPosition(p.x, p.y);
		window.draw(bgSprite);
		lvl.Draw(window);

		if ((-90.0 <= rotation) && (rotation <= 90.0)) {
			weaponSprite.setPosition(p.x + 41, p.y + 28);
			p.stateWeapon(false);
		}
		else {
			weaponSprite.setPosition(p.x + 11, p.y + 28);
			p.stateWeapon(true);
		}

		for (it = entities.begin(); it != entities.end(); it++) {
			if ((*it)->name == "easyEnemy") {
				if ((*it)->dx < 0) {
					molotSprite.setPosition((*it)->x + 5, (*it)->y + 30);
				}
				else {
					molotSprite.setPosition((*it)->x + 45, (*it)->y + 30);
				}
				window.draw(molotSprite);
			}
			if ((*it)->getEnemyview().intersects(p.getRect())) {
				(*it)->sprite.setColor(Color::Red);
			}
			else {
				(*it)->sprite.setColor(Color::White);
			}
			window.draw((*it)->sprite);
		}
		window.draw(weaponSprite);
		window.draw(p.sprite);
		window.draw(sightSprite);
		//window.draw(flashSprite);
		_mm_pause;
		//flashSprite.setPosition(9999, 9999);
		window.display();
	}
	return 0;
}