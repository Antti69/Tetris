#pragma once
#include <fstream>
#include "Font.h"
#include "Keyboard.h"


class GameSettings
{
public:
	GameSettings();
	void Save();
	void Draw(Graphics& gfx) const;
	float TranslateSpeed();
	void ProccesKeys(const Keyboard::Event e);
	int GetVerticalSpeed() const;

private:
	int VerticalSpeed;
	int deffault = 4;
	Font Setting = { "kuvat//Consolas13x24.bmp" };
};