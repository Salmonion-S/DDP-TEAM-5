#pragma once

#include "dino.h"
#include "environment.h"

// Game loop + rendering untuk Terminal Dino Game.
// Modul ini TIDAK mengubah modul Dino/Environment, hanya mengintegrasikannya.

class Game {
public:
    Game();

    void init();
    void run();
    void restart();
    bool isRunning() const;

private:
    void readInput();
    void update();
    void render();
    bool checkCollision() const;
    void clearScreen();
    void hideCursor();
    void showCursor();

    Dino dino;
    Environment env;

    int screenWidth;
    int screenHeight;

    bool running;
    bool gameOver;
    int score;
    int frameDelayMs;
};
