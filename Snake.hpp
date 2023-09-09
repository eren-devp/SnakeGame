#pragma once
#include <deque>

class Snake {
public:
	Snake(std::pair<int, int> _head);

	void Move();
	void Grow();
	void SetDirection(int _dir);
	void SetHead(std::pair<int, int> _head);


	const char GetSymbol();
	std::pair<int, int> GetHead();
	std::deque<std::pair<int, int>> GetSnakeBody();
	std::deque<std::pair<int, int>> GetSnakePositions();

	int length = 1;
private:
	int direction = 1;
	const char symbol = 'O';

	std::deque<std::pair<int, int>> snakePositions = {};
};