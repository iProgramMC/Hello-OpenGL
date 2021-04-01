#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

class Game {
public:
    int m_scrollDelta = 0;

    void OnRender();
    void OnUpdate();
    void Init();
    void LoadTextures();
};

extern Game* g_game;
Game* GetGame();

#endif // GAME_HPP_INCLUDED
