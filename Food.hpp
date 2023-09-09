#pragma once
#include <iostream>

#include "Food.hpp"


class Food {
public:
	Food(std::pair<int, int> _position);

	void SetPosition(std::pair<int, int> _position);
	
	const char GetSymbol();
	std::pair<int, int> GetPosition();

private:
	const char symbol = '*';

	std::pair<int, int> position;
};