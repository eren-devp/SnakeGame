#pragma once
#include <iostream>
#include "Food.hpp"

class Food {
public:
	Food(std::pair<int, int> _position);

	void SetPosition(std::pair<int, int> _position);
	
	std::string* GetSymbol();
	std::pair<int, int>* GetPosition();

private:
	std::string* symbol = new std::string("*");

	std::pair<int, int>* position;
};