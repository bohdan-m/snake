#pragma once

#include "ui.h"

#include <deque>
#include <string>
#include <random>
#include <iostream>
#include <unordered_set>
#include <cstdlib>

struct Point
{
	int x = 0;
	int	y = 0;
};

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};


class Game
{
	void Start();
private:
	void Redraw();
	void NewTarget();
	void MoveSnake(Direction);

	std::deque<Point> snake;
	Point target;
	int frameWidth = 80;
	int frameHeight = 26;
};
