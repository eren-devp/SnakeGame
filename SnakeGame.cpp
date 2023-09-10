#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Snake.hpp"
#include "Food.hpp"

// std::string debugmsg = ""; // For debugging the game.

bool* alive = new bool(true);
bool* snakeDrawed = new bool(false);

const int fps = 60;
const int* width = new int(40);
const int* height = new int(20);
const int* goal = new int(100);
const DWORD* sleepTimePtr = new DWORD(1000 / fps);

Snake* snake;
Food* food;

void Setup() {
    delete snake;
    delete food;

    snake = new Snake(std::make_pair(*width / 2, *height / 2));
    food = new Food(std::make_pair(35, *height / 2));
}

void Draw() {
    // Drawing the top line.
    for (int i = 0; i <= (*width + 1); ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;

    // Drawing the mid lines.
    for (int y = 1; y <= *height; ++y) {
        for (int x = 0; x <= (*width + 1); ++x) {
            if (x == 0 || x == (*width + 1)) {
                std::cout << "#"; // Drawing the side lines.
            }
            else {
                *snakeDrawed = false;
                std::pair<int, int>* currentGrid = new std::pair<int, int>(x, y);

                // Drawing the snake.
                for (auto pair : snake->GetSnake()) {
                    if (*currentGrid == pair) {
                        *snakeDrawed = true;
                        std::cout << *snake->GetSymbol();
                    }
                }

                if (*snakeDrawed) // If the snake is drawn then skip the others.
                    continue;

                // Drawing the food.
                else if (*food->GetPosition() == *currentGrid) {
                    std::cout << *food->GetSymbol();
                }

                // Means empty grid.
                else {
                    std::cout << " ";
                }

                delete currentGrid;
            }
        }
        std::cout << std::endl;
    }

    // Drawing the bottom line.
    for (int i = 0; i <= (*width + 1); ++i) {
        std::cout << "#";
    }
    std::cout << std::endl;
}

void Logic() {
    system("cls"); // Cleaning the old frame.

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
    if (*snake->GetHead() == *food->GetPosition()) {
        // debugmsg += "grew - ";
        snake->Grow();

        bool* run = new bool(true);
        int* foodX = new int(1 + (rand() % static_cast<int>(*width)));
        int* foodY = new int(1 + (rand() % static_cast<int>(*height)));
        std::pair<int, int>* foodPair = new std::pair<int, int>(*foodX, *foodY);

        while (*run) {
            *foodX = 1 + (rand() % static_cast<int>(*width));
            *foodY = 1 + (rand() % static_cast<int>(*height));

            *foodPair = std::pair<int, int>(*foodX, *foodY);
            *run = false;

            // debugmsg += "runned - ";
            for (auto snakePair : snake->GetSnake()) {
                if (snakePair == *foodPair) {
                    *run = true;
                    // debugmsg += "tryin again - ";
                    break;
                }
            }
        }
        food->SetPosition(*foodPair);
        delete foodPair;
        delete foodX;
        delete foodY;
        delete run;
    }

    snake->Move();

    // Handling the border collisions. {killed the optimization here lol}
    if (snake->GetHead()->first < 1 || snake->GetHead()->first > *width || snake->GetHead()->second < 1 || snake->GetHead()->second > *height) {
        *alive = false;
        throw std::exception("You're out of range just like my arrays.");
    }

    // Handling the snake's eating itself.
    for (auto body : snake->GetSnakeBody()) {
        if (body == *snake->GetHead()) {
            *alive = false;
            throw std::exception("You ate yourself lmao.");
        }
    }

    // Handling the winning the game.
    if (*snake->GetLength() == *goal) {
        *alive = false;
        throw std::exception("You won!");
    }
}

// For development.
void Debug() {
    // system("cls");
    // std::cout << debugmsg << std::endl;
    std::cout << "SnakeBodyL: " << snake->GetSnake().size() << std::endl;
    std::cout << "SnakeHead: " << snake->GetHead()->first << " " << snake->GetHead()->second << std::endl;
}

int main()
{
    Setup();
    try {
        while (*alive) {
            Logic();
            // Debug();
            Draw();
            Sleep(*sleepTimePtr);
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    Sleep(3000);
}