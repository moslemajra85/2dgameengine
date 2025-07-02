#include "Game.h"
#include <SDL2/SDL.h>
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

void Game::Setup() {

  // Initialize game objects
}

void Game::Update() {

  // Todo Update Game Objects
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

  // draw Rectangle
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   
  SDL_Rect player = {10, 10, 20, 20};
  SDL_RenderFillRect(renderer, &player);
 
  SDL_RenderPresent(renderer);
}