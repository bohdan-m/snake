#include "game.h"

Game::Game()
{
	snake = { {frameWidth / 2, frameHeight / 2}, 
			  {frameWidth / 2 - 1, frameHeight / 2}, 
			  {frameWidth / 2 - 2, frameHeight / 2}
	};

	NewTarget();
}

bool Game::MoveSnake(Direction d)
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

	if (CheckNextMove(head))
	{
		snake.push_front(head);

		if (head == target)
		{
			NewTarget();
		}
		else 
		{
			snake.pop_back();
		}

		return true;
	}
	else
	{
		return false;
	}
}

//	Takes the next position of the snake's head 
//	and checks whether it hits the border or its body. 
//	If it does so returns false. Otherwise returns true.

bool Game::CheckNextMove(const Point& head)
{
	if (head.x == -1 || head.x == frameWidth  ||
		head.y == -1 || head.y == frameHeight)
	{
		return false;
	}

	if (std::find(begin(snake), end(snake), head) != end(snake))
	{
		return false;
	}
	
	return true;
}

void Game::GameOver()
{
	ui::Console::Clear();
	std::cout << "Game over!" << std::endl;
}

void Game::ReadUserInputAsync()
{
	ui::Console::Key userInput;

	while (true)
	{
		userInput = static_cast<ui::Console::Key>(ui::Console::GetChar());
		movementDirectionMutex.lock();
		
		switch (userInput)
		{
		case ui::Console::Key::Up:
			movementDirection = Direction::Up;
			break;
		case ui::Console::Key::Left:
			movementDirection = Direction::Left;
			break;
		case ui::Console::Key::Right:
			movementDirection = Direction::Right;
			break;
		case ui::Console::Key::Down:
			movementDirection = Direction::Down;
			break;
		}

		movementDirectionMutex.unlock();
	}
}

void Game::Start()
{
	std::future<void> userInputThread = std::async([this] {
		ReadUserInputAsync();
	});

	while (true)
	{
		Redraw();

		movementDirectionMutex.lock();
		if (!MoveSnake(movementDirection))
		{
			GameOver();
		}
		movementDirectionMutex.unlock();
	}
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
	Point new_target;

	do
	{
		new_target = { rand() % frameWidth, rand() % frameHeight };
	} while (!(std::find(begin(snake), end(snake), new_target) == end(snake)));
	
	target = new_target;
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
