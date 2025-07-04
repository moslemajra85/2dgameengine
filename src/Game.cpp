#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {

  isRunning = false;
  std::cout << "Game constructor Called" << std::endl;
}

Game::~Game() { std::cout << "Game destructor Called" << std::endl; }

void Game::Initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

    std::cerr << "Error Initializing SDL!" << std::endl;
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

    std::cerr << "Error creating SDL Window!" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {

    std::cerr << "Error Creating SDL Renderer:" << std::endl;
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
  playerVelocity = glm::vec2(1.0, 0.0);
}

void Game::Update() {

  // if we are too fast, we need to wast some time
  // until we reach the target time that each frame
  // should take(MILLISECS_PER_FRAME)

  //locking the execution inside the while loop
  while (!SDL_TICKS_PASSED(SDL_GetTicks(),
                           millisecsPreviousFrame + MILLISECS_PER_FRAME));

  // store the current frame time
  millisecsPreviousFrame = SDL_GetTicks();

  // Todo Update Game Objects
  playerPosition.x += playerVelocity.x;
  playerPosition.y += playerVelocity.y;
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