#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Snake.hpp"
#include "Food.hpp"
#include "SnakeGame.h"

std::string debugmsg = "";

bool* alive;

const int width = 40;
const int height = 20;
const int fps = 5;
const DWORD* sleepTime = new DWORD(1000 / fps);

Snake* snake;
Food* food;

void Setup() {
    delete alive;
    delete snake;
    delete food;

    alive = new bool(true);
    snake = new Snake(std::make_pair(width / 2, height / 2));
    food = new Food(std::make_pair(35, height / 2));
}

void Draw() {
    system("cls"); // Cleaning the former drawing.

    // Drawing the top line.
    for (int i = 0; i <= (width + 1); ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;

    // Drawing the mid lines.
    for (int y = 1; y <= height; ++y) {
        for (int x = 0; x <= (width + 1); ++x) {
            if (x == 0 || x == (width + 1)) {
                std::cout << "#"; // Drawing the side lines.
            }
            else {
                bool* snakeDrawed = new bool(false);
                std::pair<int, int>* currentGrid = new std::pair<int, int>(x, y);

                // Drawing the snake.
                for (auto pair : snake->GetSnakeBody()) {
                    if (*currentGrid == pair) {
                        *snakeDrawed = true;
                        std::cout << snake->GetSymbol();
                    }
                }

                if (*snakeDrawed) // If the snake is drawn then skip the others.
                    continue;

                // Drawing the food.
                else if (food->GetPosition() == *currentGrid) {
                    std::cout << food->GetSymbol();
                }

                // Means empty grid.
                else {
                    std::cout << " ";
                }

                delete currentGrid;
                delete snakeDrawed;
            }
        }
        std::cout << std::endl;
    }

    // Drawing the bottom line.
    for (int i = 0; i <= (width + 1); ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;
}

void Logic() {
    // Handling the keyboard inputs.
    if (_kbhit()) {
        switch (_getch())
        {
        case 'w':
            snake->SetDirection(0);
            break;

        case 'd':
            snake->SetDirection(1);
            break;

        case 's':
            snake->SetDirection(2);
            break;

        case 'a':
            snake->SetDirection(3);
            break;
        }
    }

    // Handling the eating.
    if (snake->GetHead() == food->GetPosition()) {
        debugmsg += "grew - ";
        snake->Grow();

        int* foodX = new int(0);
        int* foodY = new int(0);
        bool* run = new bool(true);

        std::pair<int, int> foodPair = std::make_pair(*foodX, *foodY);

        while (*run) {
            *foodX = 1 + (rand() % static_cast<int>(width));
            *foodY = 1 + (rand() % static_cast<int>(height));

            foodPair = std::pair<int, int>(*foodX, *foodY);
            *run = false;

            debugmsg += "runned - ";
            for (auto snakePair : snake->GetSnakeBody()) {
                if (snakePair == foodPair) {
                    *run = true;
                    debugmsg += "tryin again - ";
                    break;
                }
            }
        }
        food->SetPosition(foodPair);
        delete run;
        delete foodX;
        delete foodY;
    }

    snake->Move();
}

// For development.
void Debug() {
    // system("cls");
    std::cout << debugmsg << std::endl;
    std::cout << snake->GetSnakePositions().size() << std::endl;
    std::cout << "SnakeBodyL: " << snake->GetSnakeBody().size() << std::endl;
    std::cout << "Snake Length: " << snake->length << std::endl;
    std::cout << "SnakeHead: " << snake->GetHead().first << " " << snake->GetHead().second << std::endl;
}

int main()
{
    Setup();

    while (*alive) {
        Logic();
        Debug();
        Draw();
        Sleep(*sleepTime);
    }
}