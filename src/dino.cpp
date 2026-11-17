#include "dino.h"

// ASCII art frames.
// Standing frames: 4 baris, lebar konsisten (dipadding spasi).
static const char* IDLE_FRAME[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /       /   "
};

static const char* RUN_FRAME_1[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /  /  _/    "
};

static const char* RUN_FRAME_2[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /  \\_ /     "
};

static const char* JUMP_FRAME[] = {
    "          __ ",
    "         / _)",
    "  .-^^^-/ /  ",
    " /   \\__/    "
};

// Ducking frames: 2 baris, lebar konsisten.
static const char* DUCK_FRAME_1[] = {
    "  .-^^^^-.__ ",
    " /  _  _   / "
};

static const char* DUCK_FRAME_2[] = {
    "  .-^^^^-.__ ",
    " /  _  _  \\_ "
};

static constexpr int STAND_WIDTH = 13;
static constexpr int STAND_HEIGHT = 4;
static constexpr int DUCK_WIDTH = 13;
static constexpr int DUCK_HEIGHT = 2;

Dino::Dino()
    : x(5),
      y(0),
      groundY(0),
      state(DinoState::RUNNING),
      stateBeforeJump(DinoState::RUNNING),
      animTick(0),
      frameIndex(0),
      verticalVelocity(0) {}

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

    // Mulai lompat hanya jika sedang di tanah.
    if (newState == DinoState::JUMPING) {
        if (!isOnGround()) {
            return; // tidak ada double jump
        }
        stateBeforeJump = (state == DinoState::DUCKING) ? DinoState::RUNNING : state;
        state = DinoState::JUMPING;
        verticalVelocity = JUMP_INITIAL_VELOCITY;
        animTick = 0;
        frameIndex = 0;
        return;
    }

    // Abaikan perubahan state lain saat di udara; state akhir ditentukan saat mendarat.
    if (state == DinoState::JUMPING) {
        return;
    }

    DinoState oldState = state;
    state = newState;
    animTick = 0;
    frameIndex = 0;

    // Sesuaikan posisi Y agar kaki tetap di ground saat tinggi karakter berubah.
    int oldHeight = (oldState == DinoState::DUCKING) ? DUCK_HEIGHT : STAND_HEIGHT;
    int newHeight = (state == DinoState::DUCKING) ? DUCK_HEIGHT : STAND_HEIGHT;
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
    return (state == DinoState::DUCKING) ? DUCK_WIDTH : STAND_WIDTH;
}

int Dino::getHeight() const {
    return (state == DinoState::DUCKING) ? DUCK_HEIGHT : STAND_HEIGHT;
}

const char** Dino::getCurrentFrame() const {
    int count = 0;
    int h = 0;
    int w = 0;
    const char** frames = getFramesForState(state, count, h, w);
    if (count <= 0) {
        return IDLE_FRAME;
    }
    if (frameIndex < 0 || frameIndex >= count) {
        return frames;
    }
    // getFramesForState mengembalikan pointer ke "set" frame; untuk multi-frame
    // kita hitung offset manual berdasarkan state.
    switch (state) {
        case DinoState::RUNNING:
            return (frameIndex == 0) ? RUN_FRAME_1 : RUN_FRAME_2;
        case DinoState::DUCKING:
            return (frameIndex == 0) ? DUCK_FRAME_1 : DUCK_FRAME_2;
        case DinoState::JUMPING:
            return JUMP_FRAME;
        case DinoState::IDLE:
        default:
            return IDLE_FRAME;
    }
}

bool Dino::isOnGround() const {
    return state != DinoState::JUMPING;
}

bool Dino::isJumping() const {
    return state == DinoState::JUMPING;
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
    y += verticalVelocity;
    verticalVelocity += GRAVITY;

    int groundTopY = groundY - (STAND_HEIGHT - 1);
    if (y >= groundTopY) {
        // Kembali ke ground (fase turun selesai).
        y = groundTopY;
        verticalVelocity = 0;

        // Kembali ke state sebelum lompat agar kontrol engine tetap konsisten.
        DinoState resume = stateBeforeJump;
        state = (resume == DinoState::JUMPING) ? DinoState::RUNNING : resume;
        animTick = 0;
        frameIndex = 0;

        // Jaga posisi ground jika state akhir memiliki tinggi berbeda.
        if (isOnGround()) {
            y = groundY - (getHeight() - 1);
        }
    }
}

void Dino::updateAnimationFrame() {
    int frameCount = 1;
    switch (state) {
        case DinoState::RUNNING:
            frameCount = 2;
            break;
        case DinoState::DUCKING:
            frameCount = 2;
            break;
        case DinoState::IDLE:
        case DinoState::JUMPING:
        default:
            frameCount = 1;
            break;
    }

    if (frameCount <= 1) {
        frameIndex = 0;
        animTick = 0;
        return;
    }

    ++animTick;
    if (animTick >= ANIM_TICKS_PER_FRAME) {
        animTick = 0;
        frameIndex = (frameIndex + 1) % frameCount;
    }
}

const char** Dino::getFramesForState(DinoState s, int& outFrameCount, int& outHeight, int& outWidth) const {
    switch (s) {
        case DinoState::RUNNING:
            outFrameCount = 2;
            outHeight = STAND_HEIGHT;
            outWidth = STAND_WIDTH;
            return RUN_FRAME_1;
        case DinoState::DUCKING:
            outFrameCount = 2;
            outHeight = DUCK_HEIGHT;
            outWidth = DUCK_WIDTH;
            return DUCK_FRAME_1;
        case DinoState::JUMPING:
            outFrameCount = 1;
            outHeight = STAND_HEIGHT;
            outWidth = STAND_WIDTH;
            return JUMP_FRAME;
        case DinoState::IDLE:
        default:
            outFrameCount = 1;
            outHeight = STAND_HEIGHT;
            outWidth = STAND_WIDTH;
            return IDLE_FRAME;
    }
}
