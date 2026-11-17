#include "environment.h"
#include <cstdlib>

// Awan sederhana (2 baris)
static const char* CLOUD_FRAME[] = {
    "  _  ",
    " ( ) "
};

// Kaktus sederhana (3 baris)
static const char* CACTUS_FRAME[] = {
    " | ",
    "_|_",
    " | "
};

static const int CACTUS_WIDTH = 3;
static const int CACTUS_HEIGHT = 3;
static const int CLOUD_WIDTH = 5;
static const int CLOUD_HEIGHT = 2;

Environment::Environment() {
    screenWidth = 80;
    screenHeight = 20;
    groundY = 15;
    speed = 1;
    minGap = 15;
    maxGap = 30;
    distanceToNextSpawn = minGap;
    cloud1X = 10;
    cloud2X = 40;
    obstacleCount = 0;

    for (int i = 0; i < 8; ++i) {
        obstacles[i].active = false;
    }
}

void Environment::update() {
    moveClouds();
    moveObstacles();
    spawnObstacle();
}

void Environment::reset() {
    obstacleCount = 0;
    for (int i = 0; i < 8; ++i) {
        obstacles[i].active = false;
    }

    cloud1X = 10;
    cloud2X = 40;
    distanceToNextSpawn = minGap;
}

void Environment::setScreenSize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}

void Environment::setGroundY(int newGroundY) {
    groundY = newGroundY;
}

int Environment::getGroundY() const {
    return groundY;
}

void Environment::setSpeed(int newSpeed) {
    if (newSpeed > 0) {
        speed = newSpeed;
    }
}

int Environment::getSpeed() const {
    return speed;
}

void Environment::setSpawnDistance(int minGapValue, int maxGapValue) {
    minGap = minGapValue;
    maxGap = maxGapValue;

    if (minGap < 1) {
        minGap = 1;
    }
    if (maxGap < minGap) {
        maxGap = minGap;
    }
}

int Environment::getObstacleCount() const {
    return obstacleCount;
}

const Obstacle& Environment::getObstacle(int index) const {
    return obstacles[index];
}

int Environment::getCloud1X() const {
    return cloud1X;
}

int Environment::getCloud2X() const {
    return cloud2X;
}

const char** Environment::getCactusFrame() const {
    return CACTUS_FRAME;
}

const char** Environment::getCloudFrame() const {
    return CLOUD_FRAME;
}

void Environment::moveClouds() {
    // Awan bergerak lebih pelan dari obstacle (setengah speed).
    for (int s = 0; s < speed; ++s) {
        cloud1X = cloud1X - 1;
        if (cloud1X + CLOUD_WIDTH < 0) {
            cloud1X = screenWidth;
        }

        cloud2X = cloud2X - 1;
        if (cloud2X + CLOUD_WIDTH < 0) {
            cloud2X = screenWidth;
        }
    }
}

void Environment::moveObstacles() {
    for (int i = 0; i < obstacleCount; ++i) {
        if (!obstacles[i].active) {
            continue;
        }

        obstacles[i].x = obstacles[i].x - speed;

        // Obstacle keluar layar -> nonaktifkan (bisa dipakai ulang)
        if (obstacles[i].x + obstacles[i].width < 0) {
            obstacles[i].active = false;
        }
    }
}

void Environment::spawnObstacle() {
    // Jaga jarak aman supaya pemain punya waktu bereaksi.
    distanceToNextSpawn = distanceToNextSpawn - speed;
    if (distanceToNextSpawn > 0) {
        return;
    }

    // Jarak spawn berikutnya acak agar tidak monoton.
    int gap = minGap;
    if (maxGap > minGap) {
        gap = minGap + (rand() % (maxGap - minGap + 1));
    }
    distanceToNextSpawn = gap;

    // Cari slot obstacle kosong.
    int slot = -1;
    for (int i = 0; i < 8; ++i) {
        if (!obstacles[i].active) {
            slot = i;
            break;
        }
    }
    if (slot < 0) {
        return;
    }

    obstacles[slot].active = true;
    obstacles[slot].width = CACTUS_WIDTH;
    obstacles[slot].height = CACTUS_HEIGHT;
    obstacles[slot].x = screenWidth;
    obstacles[slot].y = groundY - (CACTUS_HEIGHT - 1);

    if (slot >= obstacleCount) {
        obstacleCount = slot + 1;
    }
}
