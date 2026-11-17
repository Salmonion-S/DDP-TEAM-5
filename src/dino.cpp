#include "dino.h"

// Gambar Dino (T-Rex) sederhana.
// Kepala, moncong, mata, leher, badan, ekor, dan dua kaki dibuat jelas.
// Kepala dan badan konsisten, posisi kaki berubah saat berlari.

static const char* IDLE_FRAME[] = {
    "          __  ",
    "         / _)_",
    "        / /   ",
    "  _/\\/\\/ /    ",
    " /      /     ",
    " \\_/ \\_/      "
};

static const char* RUN_FRAME_1[] = {
    "          __  ",
    "         / _)_",
    "        / /   ",
    "  _/\\/\\/ /    ",
    " /      /     ",
    "  \\_/  \\      "
};

static const char* RUN_FRAME_2[] = {
    "          __  ",
    "         / _)_",
    "        / /   ",
    "  _/\\/\\/ /    ",
    " /      /     ",
    "   /  \\_/     "
};

static const char* JUMP_FRAME[] = {
    "          __  ",
    "         / _)_",
    "        / /   ",
    "  _/\\/\\/ /    ",
    " /      /     ",
    "   \\   /      "
};

// Menunduk: badan lebih rendah tapi kepala/moncong dan kaki tetap terlihat.
static const char* DUCK_FRAME[] = {
    "              ",
    "  __          ",
    " / _)_/\\/\\/\\  ",
    " \\_____/  \\   "
};

static const int STAND_WIDTH = 14;
static const int STAND_HEIGHT = 6;
static const int DUCK_WIDTH = 14;
static const int DUCK_HEIGHT = 4;

static const int JUMP_VELOCITY = -3;
static const int GRAVITY = 1;
static const int ANIM_SPEED = 2;

Dino::Dino() {
    x = 5;
    y = 0;
    groundY = 0;
    state = DinoState::RUNNING;
    stateBeforeJump = DinoState::RUNNING;
    animTick = 0;
    frameIndex = 0;
    verticalVelocity = 0;
}

void Dino::update() {
    if (state == DinoState::JUMPING) {
        applyJumpPhysics();
    }

    updateAnimationFrame();
}

void Dino::setState(DinoState newState) {
    if (newState == state) {
        return;
    }

    // Lompat hanya dari tanah (tidak bisa double jump)
    if (newState == DinoState::JUMPING) {
        if (!isOnGround()) {
            return;
        }

        if (state == DinoState::DUCKING) {
            stateBeforeJump = DinoState::RUNNING;
        } else {
            stateBeforeJump = state;
        }

        state = DinoState::JUMPING;
        verticalVelocity = JUMP_VELOCITY;
        animTick = 0;
        frameIndex = 0;
        return;
    }

    // Saat di udara, perubahan state lain diabaikan dulu
    if (state == DinoState::JUMPING) {
        return;
    }

    DinoState oldState = state;
    state = newState;
    animTick = 0;
    frameIndex = 0;

    // Jika tinggi berubah (berdiri <-> menunduk), jaga kaki tetap di tanah
    int oldHeight = STAND_HEIGHT;
    int newHeight = STAND_HEIGHT;
    if (oldState == DinoState::DUCKING) {
        oldHeight = DUCK_HEIGHT;
    }
    if (state == DinoState::DUCKING) {
        newHeight = DUCK_HEIGHT;
    }
    if (oldHeight != newHeight) {
        y = groundY - (newHeight - 1);
    }
}

DinoState Dino::getState() const {
    return state;
}

void Dino::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

int Dino::getX() const {
    return x;
}

int Dino::getY() const {
    return y;
}

int Dino::getWidth() const {
    if (state == DinoState::DUCKING) {
        return DUCK_WIDTH;
    } else {
        return STAND_WIDTH;
    }
}

int Dino::getHeight() const {
    if (state == DinoState::DUCKING) {
        return DUCK_HEIGHT;
    } else {
        return STAND_HEIGHT;
    }
}

const char** Dino::getCurrentFrame() const {
    if (state == DinoState::RUNNING) {
        if (frameIndex == 0) {
            return RUN_FRAME_1;
        } else {
            return RUN_FRAME_2;
        }
    } else if (state == DinoState::DUCKING) {
        return DUCK_FRAME;
    } else if (state == DinoState::JUMPING) {
        return JUMP_FRAME;
    } else {
        return IDLE_FRAME;
    }
}

bool Dino::isOnGround() const {
    if (state == DinoState::JUMPING) {
        return false;
    } else {
        return true;
    }
}

bool Dino::isJumping() const {
    if (state == DinoState::JUMPING) {
        return true;
    } else {
        return false;
    }
}

void Dino::setGroundY(int newGroundY) {
    groundY = newGroundY;

    if (isOnGround()) {
        y = groundY - (getHeight() - 1);
    }
}

int Dino::getGroundY() const {
    return groundY;
}

void Dino::applyJumpPhysics() {
    // Fase naik dan turun sederhana
    y = y + verticalVelocity;
    verticalVelocity = verticalVelocity + GRAVITY;

    int groundTopY = groundY - (STAND_HEIGHT - 1);
    if (y >= groundTopY) {
        y = groundTopY;
        verticalVelocity = 0;

        state = stateBeforeJump;
        if (state == DinoState::JUMPING) {
            state = DinoState::RUNNING;
        }

        animTick = 0;
        frameIndex = 0;

        // Pastikan posisi sesuai tinggi karakter saat mendarat
        y = groundY - (getHeight() - 1);
    }
}

void Dino::updateAnimationFrame() {
    int frameCount = 1;

    if (state == DinoState::RUNNING) {
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
