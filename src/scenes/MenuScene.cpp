#include "scenes/MenuScene.hpp"

void MenuScene::onEnter() {
  // load assets, init UI
  bgTexture_ = TextureRAII("assets/textures/menu_background.png");
  titleFont_ = FontRAII("assets/fonts/title_font.png");
  bgMusic_ = MusicRAII("assets/music/menu_music.wav");
}

void MenuScene::onExit() {
  // nothing to do here... yet
}

void MenuScene::handleInput() {
  if (IsKeyPressed(KEY_ENTER)) {
    TraceLog(LOG_INFO, "Enter pressed: transition to GameplayScene");
  }
  if (IsKeyPressed(KEY_ESCAPE)) {
    CloseWindow();
  }
}

void MenuScene::update(float dt) {}

void MenuScene::render() {
  // draw current frame
  BeginDrawing();
  ClearBackground(BLACK);

  if (bgTexture_.valid()) {
    DrawTexture(bgTexture_.get(), 0, 0, WHITE);
  }

  if (bgMusic_.valid()) {
    PlayMusicStream(bgMusic_.get());
  }

  if (titleFont_.valid()) {
    DrawTextEx(titleFont_.get(), "Press ENTER to Start", {80, 400}, 32, 2,
               WHITE);
  }

  EndDrawing();
}
