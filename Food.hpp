#pragma once
#include <iostream>
#include "Food.hpp"

class Food {
public:
	Food(std::pair<int, int> _position);

	void SetPosition(std::pair<int, int> _position);
	
	const std::string* GetSymbol();
	std::pair<int, int>* GetPosition();

private:
	const std::string* symbol = new std::string("*");

	std::pair<int, int>* position;
};