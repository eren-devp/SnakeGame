#pragma once
#include <deque>
#include <string>

class Snake {
public:
	Snake(std::pair<int, int> _head);

	void Move();
	void Grow();
	void SetDirection(int _dir);
	void SetHead(std::pair<int, int> _head);

	// Symbol of the snake.
	const std::string* GetSymbol();

	// Length of the snake.
	int* GetLength();

	// Snake's head's position.
	std::pair<int, int>* GetHead();
	
	// Snake's body's positions. (head included)
	std::deque<std::pair<int, int>> GetSnake();

	// Snake's body's positions. (head excluded)
	std::deque<std::pair<int, int>> GetSnakeBody();

private:
	int* length;
	int* direction = new int(1);

	const std::string* symbol = new std::string("O");
	std::deque<std::pair<int, int>> snakePositions = {};
};