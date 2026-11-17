#pragma once

enum class DinoState {
    IDLE,
    RUNNING,
    DUCKING,
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

    // Mengembalikan frame ASCII saat ini sebagai array baris C-string.
    // Jumlah baris sama dengan getHeight().
    const char** getCurrentFrame() const;

    // True jika Dino sedang berada di tanah (bukan melompat).
    bool isOnGround() const;

    // True jika Dino sedang melompat.
    bool isJumping() const;

    // Set posisi tanah (koordinat Y kaki Dino saat berdiri/menunduk di tanah).
    void setGroundY(int groundY);
    int getGroundY() const;

private:
    void applyJumpPhysics();
    void updateAnimationFrame();
    const char** getFramesForState(DinoState s, int& outFrameCount, int& outHeight, int& outWidth) const;

    int x;
    int y;
    int groundY;

    DinoState state;
    DinoState stateBeforeJump;

    int animTick;
    int frameIndex;

    // Jump physics (sederhana, per update tick)
    int verticalVelocity;
    static constexpr int JUMP_INITIAL_VELOCITY = -3;
    static constexpr int GRAVITY = 1;

    // Konfigurasi animasi
    static constexpr int ANIM_TICKS_PER_FRAME = 2;
};
