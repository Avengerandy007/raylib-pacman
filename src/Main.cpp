#include "../Raylib/include/raylib.h"
#include "../include/Update.hpp"
#include "../libpacman/include/Entity.hpp"
void InitRaylib(){
        SetTargetFPS(165);
        InitWindow(1000, 1000, "Pacman");
        SetExitKey(KEY_NULL);
}

void InitTextures(){
        Wall::Texture();
        Player::Texture();
        Coin::Texture();
        Ghost::Texture();
}

int main(){
        instance = GAME;

        InitRaylib();

	InitTextures();

		
        Update();

        CloseWindow();
}
