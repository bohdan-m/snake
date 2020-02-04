#include "game.h"

Direction GetOppositeDirection(Direction d)
{
	switch (d)
	{
	case Direction::Up:
		return Direction::Down;
	case Direction::Down:
		return Direction::Up;
	case Direction::Left:
		return Direction::Right;
	case Direction::Right:
		return Direction::Left;
	default:
		return d;
	}
}

Game::Game(int screenWidth, int screenHeight) :
	frameWidth(screenWidth),
	frameHeight(screenHeight),
	frameTemplate(frameHeight, std::string(frameWidth, ' ')),
	userFontInfo(Console::GetFontInfo())
{
	// We draw the border in the frame template 
	// so that there is no need to do it in Redraw() each time

	for (int i = 1; i < frameWidth - 1; ++i) {
		frameTemplate[0][i]					= char(205);
		frameTemplate[frameHeight - 1][i]	= char(205);
	}

	for (int i = 1; i < frameHeight - 1; ++i) {
		frameTemplate[i][0]					= char(186);
		frameTemplate[i][frameWidth - 1]	= char(186);
	}

	frameTemplate[0][0]								= char(201);
	frameTemplate[0][frameWidth - 1]				= char(187);
	frameTemplate[frameHeight - 1][0]				= char(200);
	frameTemplate[frameHeight - 1][frameWidth - 1]	= char(188);

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
			score += 10;
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
	if (head.x == 0 || head.x == frameWidth - 1 ||
		head.y == 0 || head.y == frameHeight - 1)
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
	access.lock();
	isGameOver = true;
	access.unlock();
	Console::Clear();
	std::cout	<< "Game over!" << std::endl
				<< "Your score: " << score << std::endl
				<< "Press any key...";
}

void Game::ReadUserInputAsync()
{
	Console::Key userInput;

	while (true)
	{
		static std::map<Console::Key, Direction> keyToDirect = {
			{Console::Key::Up, Direction::Up},
			{Console::Key::Down, Direction::Down},
			{Console::Key::Left, Direction::Left},
			{Console::Key::Right, Direction::Right},
		};

		userInput = static_cast<Console::Key>(Console::GetChar());

		access.lock();

		if (isGameOver) {
			access.unlock();
			break;
		}

		if (keyToDirect.count(userInput) > 0) {
			if (GetOppositeDirection(movementDirection) != keyToDirect[userInput]) {
				movementDirection = keyToDirect[userInput];
			}
		}

		access.unlock();
	}
}

// The snake looks better when width of each character equals to its height.
// We use a specific font for that. When the game is over we switch back to the old font.


void Game::SwitchToGameFont()
{
	Console::FontInfo gameFont = userFontInfo;
	gameFont.FontFamily = 48;
	gameFont.dwFontSize = { 8, 8 };

	const wchar_t* faceName = L"Terminal";
	wcscpy_s(gameFont.FaceName, faceName);
	Console::SetFontInfo(gameFont);
}

void Game::RestoreUserFont()
{
	Console::SetFontInfo(userFontInfo);
}

void Game::Start()
{
	SwitchToGameFont();

	std::future<void> userInputThread = std::async([this] {
		ReadUserInputAsync();
	});

	while (true)
	{
		Redraw();

		access.lock();

		if (!MoveSnake(movementDirection))
		{
			access.unlock();
			break;
		}

		access.unlock();
	}

	RestoreUserFont();
	GameOver();
}

void Game::Redraw()
{
	auto frame = frameTemplate;
	frame[target.y][target.x] = '+';

	for (const auto& p : snake) {
		frame[p.y][p.x] = char(254);
	}

	Console::Clear();

	for (const auto& row : frame) {
		std::cout << row << '\n';
	}

	std::cout << "Score: " << score << std::endl;
}

void Game::NewTarget()
{
	Point new_target;

	do
	{
		new_target = { 
			1 + (rand() % (frameWidth - 2)), 
			1 + (rand() % (frameHeight - 2))
		};
	} while (!(std::find(begin(snake), end(snake), new_target) == end(snake)));
	
	target = new_target;
}
