#pragma once
#include "interface.h"
#include "SFML\Audio.hpp"

struct Menu : public Interface {
	Menu(Image &image, Vector2f bounds);
	int DrawMenu(RenderWindow &window);

private:
	Text newGame;
	Text chooseLevel;
	Text aboutProgram;
	Text exit;
	Texture aboutProgramTexture;
	Sprite aboutProgramSprite;
	Music menuMusic;
	Texture firstLvlPreviewTexture;
	Sprite firstLvlPreviewSprite;
	Texture secondLvlPreviewTexture;
	Sprite secondLvlPreviewSprite;
	Texture chooseLevelTexture;
	Sprite chooseLevelSprite;
	Texture thirdLvlPreviewTexture;
	Sprite thirdLvlPreviewSprite;
	Clock clock;
	float currentFrame;
	int currentImage;


	bool isMenu;
	bool isPreview;
	int menuNum;
	int numberLevel;

	void Choose(RenderWindow &window);
	void GetChoose(RenderWindow &window);
	void DrawLvlPreview(RenderWindow &window);
	void GetChooseLevel(RenderWindow &window);
	void ChooseLevel(RenderWindow &window);
	void PreviewAnimation(float time);
};