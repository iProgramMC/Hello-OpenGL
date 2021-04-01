#include "Game.hpp"
#include "Renderer.hpp"
#include "Main.hpp"
#define TextureCount 10

int g_currentID;
Game* g_game;
Game* GetGame() {
    if (!g_game) {
        g_game = new Game();
    }
    return g_game;
}

void Game::OnRender() {
    /*Color colors[2][4] = {
        {
            0xFF0000FF,
            0x00FF00FF,
            0x0000FFFF,
            0xFF00FFFF,
        },
        {
            0x0000FFFF,
            0x00FF00FF,
            0xFF00FFFF,
            0xFF0000FF
        }
    };*/

    //DrawQuad(g_mouseX, g_mouseY, 100, 100, colors[g_isMouseDown]);
    DrawTexturedQuad(g_currentID, GetMouseX(), GetMouseY(), 256, 256);//, colors[g_isMouseDown]);
}

void Game::OnUpdate() {
    if (m_scrollDelta) {
        int k = m_scrollDelta / 120; // one notch
        g_currentID += k;
        while (g_currentID < 0) g_currentID += TextureCount;
        while (g_currentID >= TextureCount) g_currentID -= TextureCount;

        m_scrollDelta = 0;
    }
}

void Game::LoadTextures() {
    for(int i=0; i<TextureCount; i++)
        LoadRGBA5551Texture(g_textures[i], 32,32,false);
}

void Game::Init() {


}
