#include "Food.hpp"

Food::Food(std::pair<int, int> _position)
{
	position = _position;
}

void Food::SetPosition(std::pair<int, int> _position)
{
	position = _position;
}

const char Food::GetSymbol()
{
	return symbol;
}

std::pair<int, int> Food::GetPosition()
{
	return position;
}