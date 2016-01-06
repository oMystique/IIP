#pragma once
#include "resource.h"

struct InterfaceText {
	InterfaceText();

	Font font;
	Text countEnemiesText;
	Text missionTargetText;

	void UpdateText(RenderWindow &window, int const countEnemies, bool const missionTarget);
	void DrawText(RenderWindow &window);
};