#include "application.h"

void Application::Update(float time) {
	UpdateWorld(time, mousePos, view);
}


void Application::Render() {
	window->setView(view);
	window->clear();
	DrawObjects(window);
	window->display();
}