#pragma once

#include "ui.h"

#include <set>
#include <mutex>
#include <deque>
#include <string>
#include <future>
#include <random>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_set>

struct Point
{
	int x = 0;
	int	y = 0;
};

bool operator==(const Point& lhs, const Point& rhs);

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};


class Game
{
public:
	Game();
	void Start();

private:
	void Redraw();
	void NewTarget();
	bool MoveSnake(Direction);
	bool CheckNextMove(const Point&);
	void GameOver();
	void ReadUserInputAsync();
	
	Point target;
	std::deque<Point> snake;
	std::mutex movementDirectionMutex;
	Direction movementDirection = Direction::Right;
	
	int frameWidth = 80;
	int frameHeight = 26;
};
