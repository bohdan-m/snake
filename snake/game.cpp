#include "game.h"

void Game::MoveSnake(Direction d)
{
	Point head = snake.front();

	switch (d)
	{
	case Direction::Up:
		--head.y;
		break;
	case Direction::Down:
		++head.y;
		break;
	case Direction::Left:
		--head.x;
		break;
	case Direction::Right:
		++head.x;
		break;
	}

	snake.push_front(head);
	snake.pop_back();
}

void Game::Start()
{

}

void Game::Redraw()
{
	std::vector<std::string> frame(frameHeight, std::string(frameWidth, ' '));
	frame[target.y][target.x] = '+';

	for (const auto& p : snake) {
		frame[p.y][p.x] = '*';
	}

	ui::Console::Clear();

	for (const auto& row : frame) {
		std::cout << row << std::endl;
	}
}

void Game::NewTarget()
{
	target = { rand() % frameWidth, rand() % frameHeight };
}
