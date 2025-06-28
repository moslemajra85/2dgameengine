#include "Game.h"
#include <iostream>

Game::Game() {

    std::cout << "Game constructor Called" << std::endl;
}

Game::~Game() {

        std::cout << "Game destructor Called" << std::endl;

}

void Game::Initialize(){}

void Game::Run() {

    // while(true) {

    //     ProcessInput();
    //     Update();
    //     Render();
    // }
}

void Game::ProcessInput() {}

void Game::Update() {}

void Game::Destroy() {}

void Game::Render(){}