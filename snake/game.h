#pragma once

#include "console.h"
#include "point.h"

#include <set>
#include <map>
#include <mutex>
#include <deque>
#include <string>
#include <future>
#include <random>
#include <cwchar>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_set>

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

Direction GetOppositeDirection(Direction);

class Game
{
public:
	Game(int screenWidth = 40, int screenHeight = 25);
	void Start();

private:
	void Redraw();
	void NewTarget();
	bool MoveSnake(Direction);
	bool CheckNextMove(const Point&);
	void GameOver();
	void ReadUserInputAsync();
	void SwitchToGameFont();
	void RestoreUserFont();
	
	int frameWidth;
	int frameHeight;
	std::vector<std::string> frameTemplate;
	bool isGameOver = false;
	Point target;
	std::deque<Point> snake;
	Direction movementDirection = Direction::Right;
	std::mutex access; // mutex for isGameOver and movementDirection members
	Console::FontInfo userFontInfo;
};
