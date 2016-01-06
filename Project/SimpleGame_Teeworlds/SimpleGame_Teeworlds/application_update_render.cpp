#include "application.h"

void Application::Update(float time) {
	world->UpdateWorld(time, mousePos, view, *window);
}


void Application::Render() {
	window->setView(view);
	window->clear();
	world->DrawObjects(window);
	window->display();
}