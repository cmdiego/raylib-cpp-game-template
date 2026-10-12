/*
Game::run()
   └─ SceneManager.top() = MenuScene
       ├─ onEnter() → LoadTexture + LoadMusic + LoadFont
       ├─ update(dt) → bgMusic_.update()
       ├─ render()   → DrawTexture / DrawTextEx
       └─ onExit()   → (optional StopMusic)
Scene popped
   └─ ~MenuScene()
        ├─ ~TextureRAII() → UnloadTexture
        ├─ ~MusicRAII()   → UnloadMusicStream
        └─ ~FontRAII()    → UnloadFont
*/
#include "core/Game.hpp"
#include "raylib.h"
#include "scenes/MenuScene.hpp"

// Constructor: initialize window + timing
Game::Game(int w, int h, const char *title) {
  width_ = w;
  height_ = h;
  InitAudioDevice();

  // Basic window config (tweak as needed)
  SetConfigFlags(FLAG_VSYNC_HINT); // reduces tearing; optional
  InitWindow(w, h, title);
  SetTargetFPS(60);

  // Init Menu on SceneManager
  scenes().push(std::make_unique<MenuScene>());
}

// Destructor: orderly shutdown
Game::~Game() {
  // Ensure scenes exit in LIFO order; calls onExit() for each
  this->scenes().clear();

  // Scenes (and their music/sounds) are gone, so the audio device can close
  if (IsAudioDeviceReady()) {
    CloseAudioDevice();
  }

  // Close Raylib window/context
  if (IsWindowReady()) {
    CloseWindow();
  }
}

// Main loop
void Game::run() {
  // Exit if nothing to run
  if (this->scenes().empty()) {
    return;
  }

  while (!WindowShouldClose()) {
    // If all scenes were popped, exit the loop
    if (this->scenes().empty())
      break;

    // Active scene
    auto &scene = this->scenes().top();

    // 1) Input
    scene.handleInput();

    // 2) Update (seconds since last frame)
    const float dt = GetFrameTime();
    scene.update(dt);

    // 3) Render
    BeginDrawing();
    ClearBackground(BLACK); // Customize as needed
    scene.render();
    EndDrawing();
  }
}
