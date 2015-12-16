#pragma once
#include "interface.h"
#include "SFML\Audio.hpp"

struct Menu : public Interface {
	//Menu(Image &image, int w, int h);
	Menu(Image &image, Vector2f bounds);
	void DrawMenu(RenderWindow &window);

private:
	Text newGame;
	Text aboutProgram;
	Text exit;
	Music menuMusic;

	bool isMenu;
	int menuNum;

	void Choose(RenderWindow &window);
	void GetChoose(RenderWindow &window);
};