#pragma once
#include "menu.h"
#include "world.h"

struct Application: public World {
	RenderWindow *window;
	View view;
	Clock clock;
	Vector2f mousePos;

	Application();
private:
	unique_ptr<Menu> menu;
	void InitMenu();
	void Run();
	void ProcessEvents();
	void Render();
	void Update(float time);
	void GetMouseCoords();

};