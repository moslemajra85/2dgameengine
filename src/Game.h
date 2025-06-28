#ifndef GAME_H
#define GAME_H
class Game {
    private:


    public:
        Game();
        ~Game();
        void Initialize();
        void ProcessInput();
        void Update();
        void Run();
        void Render();
        void Destroy();
 
};

#endif