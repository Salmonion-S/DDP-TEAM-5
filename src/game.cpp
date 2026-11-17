#include "game.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

Game::Game() {
    screenWidth = 80;
    screenHeight = 20;
    running = true;
    gameOver = false;
    score = 0;
    frameDelayMs = 30; // ~33 FPS
}

void Game::init() {
    env.setScreenSize(screenWidth, screenHeight);
    env.setGroundY(screenHeight - 4);
    env.setSpeed(1);
    env.setSpawnDistance(15, 30);

    dino.setPosition(8, env.getGroundY() - (dino.getHeight() - 1));
    dino.setGroundY(env.getGroundY());
    dino.setState(DinoState::RUNNING);

    score = 0;
    gameOver = false;
    running = true;

#ifdef _WIN32
    hideCursor();
#else
    hideCursor();
#endif
}

void Game::run() {
    using clock = std::chrono::steady_clock;
    auto lastFrame = clock::now();

    while (running) {
        readInput();

        if (!gameOver) {
            update();
        }

        render();

        auto now = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrame).count();
        if (elapsed < frameDelayMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayMs - elapsed));
        }
        lastFrame = clock::now();
    }

    showCursor();
}

void Game::restart() {
    env.reset();
    dino.setPosition(8, env.getGroundY() - (dino.getHeight() - 1));
    dino.setGroundY(env.getGroundY());
    dino.setState(DinoState::RUNNING);
    score = 0;
    gameOver = false;
    running = true;
}

bool Game::isRunning() const {
    return running;
}

void Game::readInput() {
#ifdef _WIN32
    while (_kbhit()) {
        int key = _getch();
        if (key == 32) { // SPACE
            if (!gameOver) {
                dino.setState(DinoState::JUMPING);
            }
        } else if (key == 'r' || key == 'R') {
            restart();
        } else if (key == 27) { // ESC
            running = false;
        }
    }
#else
    while (true) {
        struct termios oldt;
        struct termios newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch == EOF) {
            break;
        }

        if (ch == 32) { // SPACE
            if (!gameOver) {
                dino.setState(DinoState::JUMPING);
            }
        } else if (ch == 'r' || ch == 'R') {
            restart();
        } else if (ch == 27) { // ESC
            running = false;
        }
    }
#endif
}

void Game::update() {
    dino.update();
    env.update();

    if (checkCollision()) {
        gameOver = true;
        return;
    }

    score = score + 1;
}

bool Game::checkCollision() const {
    int dx = dino.getX();
    int dy = dino.getY();
    int dw = dino.getWidth();
    int dh = dino.getHeight();

    for (int i = 0; i < env.getObstacleCount(); ++i) {
        const Obstacle& o = env.getObstacle(i);
        if (!o.active) {
            continue;
        }

        if (dx < o.x + o.width && dx + dw > o.x && dy < o.y + o.height && dy + dh > o.y) {
            return true;
        }
    }
    return false;
}

void Game::render() {
    static std::string buffer;
    buffer.assign(screenWidth * screenHeight, ' ');

    // helper local: tulis karakter ke buffer
    auto put = [&](int x, int y, char c) {
        if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
            buffer[y * screenWidth + x] = c;
        }
    };

    // awan
    const char** cloud = env.getCloudFrame();
    int c1 = env.getCloud1X();
    int c2 = env.getCloud2X();
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 5; ++c) {
            put(c1 + c, 2 + r, cloud[r][c]);
            put(c2 + c, 5 + r, cloud[r][c]);
        }
    }

    // obstacle
    const char** cactus = env.getCactusFrame();
    for (int i = 0; i < env.getObstacleCount(); ++i) {
        const Obstacle& o = env.getObstacle(i);
        if (!o.active) continue;
        for (int r = 0; r < o.height; ++r) {
            for (int c = 0; c < o.width; ++c) {
                put(o.x + c, o.y + r, cactus[r][c]);
            }
        }
    }

    // ground (pola berulang)
    for (int c = 0; c < screenWidth; ++c) {
        put(c, env.getGroundY(), env.getGroundChar(c));
    }

    // dino
    const char** dinoFrame = dino.getCurrentFrame();
    for (int r = 0; r < dino.getHeight(); ++r) {
        for (int c = 0; c < dino.getWidth(); ++c) {
            put(dino.getX() + c, dino.getY() + r, dinoFrame[r][c]);
        }
    }

    // render ke terminal (cursor ke awal, lalu tulis buffer)
    std::string out;
    out.reserve(screenWidth * screenHeight + 64);

#ifdef _WIN32
    // Windows console: gunakan ANSI escape sederhana
    out += "\033[H";
#else
    out += "\033[H";
#endif
    for (int r = 0; r < screenHeight; ++r) {
        out.append(buffer, r * screenWidth, screenWidth);
        out += "\r\n";
    }

    if (gameOver) {
        out += "GAME OVER - press R to restart, ESC to quit\r\n";
    } else {
        out += "Score: " + std::to_string(score) + "  (SPACE: jump, R: restart, ESC: quit)\r\n";
    }

    std::cout << out;
    std::cout.flush();
}

void Game::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J";
#endif
}

void Game::hideCursor() {
#ifdef _WIN32
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
#else
    std::cout << "\033[?25l";
#endif
}

void Game::showCursor() {
#ifdef _WIN32
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(out, &cursorInfo);
#else
    std::cout << "\033[?25h";
#endif
}
