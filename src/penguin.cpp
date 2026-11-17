#include "penguin.h"

// Gambar Penguin ASCII sederhana.
// Kepala dan badan dibuat konsisten, kaki bergerak saat lari.

static const char* IDLE_FRAME[] = {
    "   .---.  ",
    "  ( o o ) ",
    " /|  ^  |\\",
    "  | '_' | ",
    "  /_/ \\_\\ "
};

static const char* RUN_FRAME_1[] = {
    "   .---.  ",
    "  ( o o ) ",
    " /|  ^  |\\",
    "  | '_' | ",
    "  /_/ \\   "
};

static const char* RUN_FRAME_2[] = {
    "   .---.  ",
    "  ( o o ) ",
    " /|  ^  |\\",
    "  | '_' | ",
    "   / \\_\\  "
};

static const char* JUMP_FRAME[] = {
    "   .---.  ",
    "  ( o o ) ",
    " /|  ^  |\\",
    "  | '_' | ",
    "   \\   /  "
};

// Menunduk: badan lebih pendek, hitbox ikut lebih kecil.
static const char* DUCK_FRAME[] = {
    "  .---.   ",
    " ( o o )  ",
    " <_'^'_>  ",
    "  /_ _\\   "
};

static const int STAND_WIDTH = 10;
static const int STAND_HEIGHT = 5;
static const int DUCK_WIDTH = 10;
static const int DUCK_HEIGHT = 4;

static const int JUMP_VELOCITY = -3;
static const int GRAVITY = 1;
static const int ANIM_SPEED = 2;

Penguin::Penguin() {
    x = 5;
    y = 0;
    groundY = 0;
    state = PenguinState::RUNNING;
    stateBeforeJump = PenguinState::RUNNING;
    animTick = 0;
    frameIndex = 0;
    verticalVelocity = 0;
}

void Penguin::update() {
    if (state == PenguinState::JUMPING) {
        applyJumpPhysics();
    }

    updateAnimationFrame();
}

void Penguin::setState(PenguinState stateBaru) {
    if (stateBaru == state) {
        return;
    }

    // Lompat hanya dari tanah (tidak bisa double jump)
    if (stateBaru == PenguinState::JUMPING) {
        if (!isOnGround()) {
            return;
        }

        if (state == PenguinState::DUCKING) {
            stateBeforeJump = PenguinState::RUNNING;
        } else {
            stateBeforeJump = state;
        }

        state = PenguinState::JUMPING;
        verticalVelocity = JUMP_VELOCITY;
        animTick = 0;
        frameIndex = 0;
        return;
    }

    // Saat di udara, perubahan state lain diabaikan dulu
    if (state == PenguinState::JUMPING) {
        return;
    }

    PenguinState oldState = state;
    state = stateBaru;
    animTick = 0;
    frameIndex = 0;

    // Jika tinggi berubah (berdiri <-> menunduk), jaga kaki tetap di tanah
    int oldHeight = STAND_HEIGHT;
    int newHeight = STAND_HEIGHT;
    if (oldState == PenguinState::DUCKING) {
        oldHeight = DUCK_HEIGHT;
    }
    if (state == PenguinState::DUCKING) {
        newHeight = DUCK_HEIGHT;
    }
    if (oldHeight != newHeight) {
        y = groundY - (newHeight - 1);
    }
}

PenguinState Penguin::getState() const {
    return state;
}

void Penguin::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
}

int Penguin::getX() const {
    return x;
}

int Penguin::getY() const {
    return y;
}

int Penguin::getWidth() const {
    if (state == PenguinState::DUCKING) {
        return DUCK_WIDTH;
    } else {
        return STAND_WIDTH;
    }
}

int Penguin::getHeight() const {
    if (state == PenguinState::DUCKING) {
        return DUCK_HEIGHT;
    } else {
        return STAND_HEIGHT;
    }
}

const char** Penguin::getCurrentFrame() const {
    if (state == PenguinState::RUNNING) {
        if (frameIndex == 0) {
            return RUN_FRAME_1;
        } else {
            return RUN_FRAME_2;
        }
    } else if (state == PenguinState::DUCKING) {
        return DUCK_FRAME;
    } else if (state == PenguinState::JUMPING) {
        return JUMP_FRAME;
    } else {
        return IDLE_FRAME;
    }
}

bool Penguin::isOnGround() const {
    if (state == PenguinState::JUMPING) {
        return false;
    } else {
        return true;
    }
}

bool Penguin::isJumping() const {
    if (state == PenguinState::JUMPING) {
        return true;
    } else {
        return false;
    }
}

void Penguin::setGroundY(int tanahY) {
    groundY = tanahY;

    if (isOnGround()) {
        y = groundY - (getHeight() - 1);
    }
}

int Penguin::getGroundY() const {
    return groundY;
}

void Penguin::applyJumpPhysics() {
    // Fase naik dan turun sederhana
    y = y + verticalVelocity;
    verticalVelocity = verticalVelocity + GRAVITY;

    int groundTopY = groundY - (STAND_HEIGHT - 1);
    if (y >= groundTopY) {
        y = groundTopY;
        verticalVelocity = 0;

        state = stateBeforeJump;
        if (state == PenguinState::JUMPING) {
            state = PenguinState::RUNNING;
        }

        animTick = 0;
        frameIndex = 0;

        // Pastikan posisi sesuai tinggi karakter saat mendarat
        y = groundY - (getHeight() - 1);
    }
}

void Penguin::updateAnimationFrame() {
    int frameCount = 1;

    if (state == PenguinState::RUNNING) {
        frameCount = 2;
    } else {
        frameCount = 1;
    }

    if (frameCount <= 1) {
        frameIndex = 0;
        animTick = 0;
        return;
    }

    animTick = animTick + 1;
    if (animTick >= ANIM_SPEED) {
        animTick = 0;
        frameIndex = frameIndex + 1;
        if (frameIndex >= frameCount) {
            frameIndex = 0;
        }
    }
}
