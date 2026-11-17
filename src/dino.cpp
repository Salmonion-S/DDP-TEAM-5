#include "dino.h"

// Gambar ASCII Dino.
// Kepala dan badan dibuat sama, yang berubah adalah posisi kaki.

static const char* IDLE_FRAME[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /    _/     "
};

static const char* RUN_FRAME_1[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /   / \\_    "
};

static const char* RUN_FRAME_2[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /  _/ \\     "
};

static const char* JUMP_FRAME[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /    \\/     "
};

// Dino menunduk (lebih pendek) dan kaki tetap berganti.
static const char* DUCK_FRAME_1[] = {
    "  .-^^^^-.__ ",
    " /  _  / \\_  "
};

static const char* DUCK_FRAME_2[] = {
    "  .-^^^^-.__ ",
    " /  _ _/ \\   "
};

static const int STAND_WIDTH = 13;
static const int STAND_HEIGHT = 4;
static const int DUCK_WIDTH = 13;
static const int DUCK_HEIGHT = 2;

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
    // Kalau sedang lompat, gerakkan posisi Y dulu
    if (state == DinoState::JUMPING) {
        applyJumpPhysics();
    }

    updateAnimationFrame();
}

void Dino::setState(DinoState newState) {
    if (newState == state) {
        return;
    }

    // Mulai lompat hanya jika di tanah (tidak bisa double jump)
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
        verticalVelocity = JUMP_INITIAL_VELOCITY;
        animTick = 0;
        frameIndex = 0;
        return;
    }

    // Saat lompat, state lain diabaikan dulu
    if (state == DinoState::JUMPING) {
        return;
    }

    DinoState oldState = state;
    state = newState;
    animTick = 0;
    frameIndex = 0;

    // Kalau tinggi badan berubah (misal berdiri ke nunduk), sesuaikan Y supaya kaki tetap di tanah
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
        if (frameIndex == 0) {
            return DUCK_FRAME_1;
        } else {
            return DUCK_FRAME_2;
        }
    } else if (state == DinoState::JUMPING) {
        return JUMP_FRAME;
    } else { // IDLE
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

    // Saat di tanah, posisikan Y berdasarkan tinggi karakter sekarang
    if (isOnGround()) {
        y = groundY - (getHeight() - 1);
    }
}

int Dino::getGroundY() const {
    return groundY;
}

void Dino::applyJumpPhysics() {
    // Naik/turun sederhana: velocity berubah tiap update
    y = y + verticalVelocity;
    verticalVelocity = verticalVelocity + GRAVITY;

    int groundTopY = groundY - (STAND_HEIGHT - 1);

    if (y >= groundTopY) {
        // Sudah sampai tanah
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
    } else if (state == DinoState::DUCKING) {
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
    if (animTick >= ANIM_TICKS_PER_FRAME) {
        animTick = 0;
        frameIndex = frameIndex + 1;
        if (frameIndex >= frameCount) {
            frameIndex = 0;
        }
    }
}

// Fungsi ini masih dipakai oleh deklarasi class (tidak masalah walau sederhana)
const char** Dino::getFramesForState(DinoState s, int& outFrameCount, int& outHeight, int& outWidth) const {
    if (s == DinoState::RUNNING) {
        outFrameCount = 2;
        outHeight = STAND_HEIGHT;
        outWidth = STAND_WIDTH;
        return RUN_FRAME_1;
    } else if (s == DinoState::DUCKING) {
        outFrameCount = 2;
        outHeight = DUCK_HEIGHT;
        outWidth = DUCK_WIDTH;
        return DUCK_FRAME_1;
    } else if (s == DinoState::JUMPING) {
        outFrameCount = 1;
        outHeight = STAND_HEIGHT;
        outWidth = STAND_WIDTH;
        return JUMP_FRAME;
    } else {
        outFrameCount = 1;
        outHeight = STAND_HEIGHT;
        outWidth = STAND_WIDTH;
        return IDLE_FRAME;
    }
}
