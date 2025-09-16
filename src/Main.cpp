#include "../Raylib/include/raylib.h"
#include "../include/Levels.hpp"
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

	LevelLogic::GetLevelData(LevelLogic::levelData);
	LevelLogic::entireSet = LevelLogic::SetTileSet();
        Tile::InitTileSet<100>(10, LevelLogic::entireSet);
	Tile::SetEntityRectangles<100>(LevelLogic::entireSet);
	
        Update();

        CloseWindow();
}
