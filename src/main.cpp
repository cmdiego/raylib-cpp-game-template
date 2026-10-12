#include "core/Game.hpp"

const struct {
  int width = 800;
  int height = 700;
} windowScreen;

int main() {
  // Game owns the window, audio device and scene stack (starts on MenuScene)
  Game game(windowScreen.width, windowScreen.height,
            "raylib-cpp-game-template");
  game.run();
}
