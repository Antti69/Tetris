#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Font.h"
#include "Board.h"
#include <sstream>


class ScoreTest
{
public:
	ScoreTest() = default;
	void Save(const Board& brd);
	void LoadAndDraw(Graphics& gfx);

private:
	int FirstScore;
	int SecondScore;
	int ThirdScore;
	int FirstLine;
	int SecondLine;
	int ThirdLine;
	Font HighScore = { "kuvat//Consolas13x24.bmp" };
};