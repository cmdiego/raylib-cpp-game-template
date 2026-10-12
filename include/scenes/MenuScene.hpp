#pragma once
#include "core/Scene.hpp"
#include "resources/MusicRAII.hpp"
#include "resources/TextureRAII.hpp"

class MenuScene : public Scene {
public:
  void onEnter() override;     // load bg texture, title logo, music
  void onExit() override;      // stop music
  void handleInput() override; // ENTER -> replace with Gameplay
  void update(float dt) override;
  void render() override;

private:
  TextureRAII bgTexture_;
  TextureRAII titleLogo_;
  MusicRAII bgMusic_;
};
