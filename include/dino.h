#pragma once

enum class DinoState {
    IDLE,
    RUNNING,
    JUMPING
};

class Dino {
public:
    Dino();

    void update();
    void setState(DinoState state);
    DinoState getState() const;

    void setPosition(int x, int y);

    int getX() const;
    int getY() const;

    int getWidth() const;
    int getHeight() const;

    // Mengembalikan frame ASCII sekarang (array baris, jumlah baris = getHeight()).
    const char** getCurrentFrame() const;

    bool isOnGround() const;
    bool isJumping() const;

    // Posisi tanah (koordinat Y kaki saat di tanah).
    void setGroundY(int groundY);
    int getGroundY() const;

private:
    void applyJumpPhysics();
    void updateAnimationFrame();

    int x;
    int y;
    int groundY;

    DinoState state;

    int animTick;
    int frameIndex;
    int verticalVelocity;
};
