#include "Game.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {

  isRunning = false;

  Logger::Log("Game constructor Called");
}

Game::~Game() { Logger::Log("Game destructor Called!"); }

void Game::Initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

    Logger::Error("Error Initializing SDL!");
    return;
  }

  // Create a window
  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 800;
  windowHeight = 600;
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, SDL_WINDOW_BORDERLESS

      );

  if (!window) {

    Logger::Error("Error creating SDL Window!");
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    Logger::Error("Error Creating SDL Renderer!");
    return;
  }

  // set window to full screen
  // this will change the video mode to real full screen
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::Run() {

  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::ProcessInput() {

  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {

    switch (sdlEvent.type) {
    case SDL_QUIT:
      isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      break;
    }
  }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {

  // Initialize game objects
  playerPosition = glm::vec2(10.0, 20.0);
  playerVelocity = glm::vec2(40.0, 0.0);
}

void Game::Update() {

  // if we are too fast, we need to wast some time
  // until we reach the target time that each frame
  // should take(MILLISECS_PER_FRAME)

  int timeToWait =
      MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);

  if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  // the difference in ticks since the last frame in seconds
  double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

  millisecsPreviousFrame = SDL_GetTicks();

  // Todo Update Game Objects
  playerPosition.x += playerVelocity.x * deltaTime;
  playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::Destroy() {

  // Clean Up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::Render() {

  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  // draw Game Objects
  SDL_Surface *surface = IMG_Load("./assets/images/tank-tiger-right.png");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  // The destination Rectangle where we want to place our texture
  SDL_Rect destRect = {static_cast<int>(playerPosition.x),
                       static_cast<int>(playerPosition.y), 32, 32};
  SDL_RenderCopy(renderer, texture, NULL, &destRect);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(renderer);
}