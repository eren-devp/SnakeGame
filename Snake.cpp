#include "Snake.hpp"

Snake::Snake(std::pair<int, int> _head)
{
	delete length;

	snakePositions = { _head, std::make_pair(_head.first - 1, _head.second), std::make_pair(_head.first - 2, _head.second) };
	length = new int(snakePositions.size());
}

void Snake::Move()
{
	std::pair<int, int>* head = new std::pair<int, int>(*GetHead());
	if (*direction == 0) {
		// Move up.
		SetHead(std::make_pair(head->first, head->second - 1));
	}
	else if (*direction == 1) {
		// Move right.
		SetHead(std::make_pair(head->first + 1, head->second));
	}
	else if (*direction == 2) {
		// Move down.
		SetHead(std::make_pair(head->first, head->second + 1));
	}
	else if (*direction == 3) {
		// Move left.
		SetHead(std::make_pair(head->first - 1, head->second));
	}
}

void Snake::Grow()
{
	*length += 1;
}

void Snake::SetDirection(int _dir)
{
	if (*direction == 0 && _dir == 2)
		return;
	else if (*direction == 1 && _dir == 3)
		return;
	else if (*direction == 2 && _dir == 0)
		return;
	else if (*direction == 3 && _dir == 1)
		return;

	*direction = _dir;
}

void Snake::SetHead(std::pair<int, int> _head)
{
	snakePositions.emplace_front(_head);
}

std::string* Snake::GetSymbol()
{
	return symbol;
}

int* Snake::GetLength()
{
	return length;
}

std::pair<int, int>* Snake::GetHead()
{
	return &snakePositions.front();
}

std::deque<std::pair<int, int>> Snake::GetSnake()
{
	return std::deque<std::pair<int, int>>(snakePositions.begin(), snakePositions.begin() + *length);
}

std::deque<std::pair<int, int>> Snake::GetSnakeBody()
{
	return std::deque<std::pair<int, int>>(snakePositions.begin() + 1, snakePositions.begin() + *length);
}