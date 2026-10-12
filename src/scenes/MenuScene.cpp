#include "scenes/MenuScene.hpp"

void MenuScene::onEnter() {
  // load assets, init UI
  bgTexture_ = TextureRAII("assets/textures/menu_background.png");
  titleLogo_ = TextureRAII("assets/textures/title_logo.png");
  bgMusic_ = MusicRAII("assets/music/menu_music.wav");

  // Start once here; update() keeps the stream fed every frame
  if (bgMusic_.valid()) {
    PlayMusicStream(bgMusic_.get());
  }
}

void MenuScene::onExit() {
  if (bgMusic_.valid()) {
    StopMusicStream(bgMusic_.get());
  }
}

void MenuScene::handleInput() {
  if (IsKeyPressed(KEY_ENTER)) {
    TraceLog(LOG_INFO, "Enter pressed: transition to GameplayScene");
  }
  // ESC is raylib's default exit key: WindowShouldClose() in Game::run() ends
  // the loop, so the scene must not close the window itself
}

void MenuScene::update(float /*dt*/) { bgMusic_.update(); }

void MenuScene::render() {
  // Game::run() wraps this in BeginDrawing()/ClearBackground()/EndDrawing()
  if (bgTexture_.valid()) {
    DrawTexture(bgTexture_.get(), 0, 0, WHITE);
  }

  if (titleLogo_.valid()) {
    const Texture2D &logo = titleLogo_.get();
    DrawTexture(logo, (GetScreenWidth() - logo.width) / 2, 200, WHITE);
  }

  const char *prompt = "Press ENTER to Start";
  const int promptSize = 32;
  DrawText(prompt, (GetScreenWidth() - MeasureText(prompt, promptSize)) / 2,
           400, promptSize, WHITE);
}
