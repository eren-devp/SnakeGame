#include "Snake.hpp"

Snake::Snake(std::pair<int, int> _head)
{
	snakePositions = {_head};
}

void Snake::Move()
{
	std::pair<int, int>* head = new std::pair<int, int>(GetHead());
	if (direction == 0) {
		// Move up.
		SetHead(std::make_pair(head->first, head->second - 1));
	}
	else if (direction == 1) {
		// Move right.
		SetHead(std::make_pair(head->first + 1, head->second));
	}
	else if (direction == 2) {
		// Move down.
		SetHead(std::make_pair(head->first, head->second + 1));
	}
	else if (direction == 3) {
		// Move left.
		SetHead(std::make_pair(head->first - 1, head->second));
	}
}

void Snake::Grow()
{
	length = length + 1;
}

void Snake::SetDirection(int _dir)
{
	direction = _dir;
}

void Snake::SetHead(std::pair<int, int> _head)
{
	snakePositions.emplace_front(_head);
}

const char Snake::GetSymbol()
{
	return symbol;
}

std::pair<int, int> Snake::GetHead()
{
	return snakePositions.front();
}

std::deque<std::pair<int, int>> Snake::GetSnakeBody()
{
	std::deque<std::pair<int, int>> snakeBody(snakePositions.begin(), snakePositions.begin() + length);
	return snakeBody;
}

std::deque<std::pair<int, int>> Snake::GetSnakePositions()
{
	return snakePositions;
}
