#pragma once

#include "world.h"
#include "menu.h"

struct Application: public World {
	RenderWindow *window;
	View view;
	Clock clock;
	float mouseX;
	float mouseY;

	Application();
	void Run();
private:
	void ProcessEvents();
	void Render();
	void Update(float time);
	void GetMouseCoords();
	void InitMenu();

	unique_ptr<Menu> menu;
};