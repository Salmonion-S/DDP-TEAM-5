#pragma once

// Environment & Obstacle untuk Terminal Dino Game.
// Modul ini TIDAK menangani input, collision, score, atau game loop.

struct Obstacle {
    int x = 0;
    int y = 0;
    int width = 3;
    int height = 3;
    bool active = false;
};

class Environment {
public:
    Environment();

    void update();
    void reset();

    // Ukuran layar terminal dan ground (koordinat terminal).
    void setScreenSize(int width, int height);
    void setGroundY(int groundY);
    int getGroundY() const;

    // Kecepatan gerak environment/obstacle (default 1 per update).
    void setSpeed(int speed);
    int getSpeed() const;

    // Jarak spawn obstacle (dalam kolom), random di antara min/max.
    void setSpawnDistance(int minGap, int maxGap);

    // Akses data obstacle untuk rendering & collision (Developer 3).
    int getObstacleCount() const;
    const Obstacle& getObstacle(int index) const;

    // Akses posisi awan untuk rendering.
    int getCloud1X() const;
    int getCloud2X() const;

    // Ground scrolling (pola berulang, bergerak kanan -> kiri).
    int getGroundOffset() const;
    char getGroundChar(int column) const;

    // Frame ASCII untuk rendering (jumlah baris = height masing-masing).
    const char** getCactusFrame() const;
    const char** getCloudFrame() const;

private:
    void spawnObstacle();
    void moveClouds();
    void moveObstacles();

    int groundOffset;
    int cloudTick;

    int screenWidth;
    int screenHeight;
    int groundY;

    int speed;

    int minGap;
    int maxGap;
    int distanceToNextSpawn;

    // Awan bergerak perlahan dari kanan ke kiri
    int cloud1X;
    int cloud2X;

    Obstacle obstacles[8];
    int obstacleCount;
};
