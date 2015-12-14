#pragma once
#include "interface.h"
#include "SFML\Audio.hpp"

struct Menu : public Interface {
	Menu(Image &image, int w, int h);

	Text newGame;
	Text aboutProgram;
	Text exit;
	bool isMenu;
	int menuNum;
	Music menuMusic;

	void Choose(RenderWindow &window);
	void GetChoose(RenderWindow &window);
	void DrawMenu(RenderWindow &window);
};