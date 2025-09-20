#include "../include/Update.hpp"
#include "../include/Levels.hpp"
#include "../libpacman/include/Tile.hpp"
#include "../libpacman/include/Entity.hpp"
#include "../Raylib/include/raylib.h"
#include "../include/UI.hpp"
#include <cstdint>

bool running = false;
void ResfreshWindow(){
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
}

void UpdateTiles(){
        for (uint8_t i = 0; i < 20; i++){
                for (uint8_t k = 0; k < 20; k++){
			if (Tile::tileSet.matrix[i][k].m_coinContainer){
				Tile::tileSet.matrix[i][k].m_coinContainer->Update();
			}
                        if (Tile::tileSet.matrix[i][k].m_containedEntity){
				if ((int)Player::score == (int)Coin::coinCount){
					std::cout << "You win!\n";
					LevelLogic::Reload();
					break;
				}
                                Tile::tileSet.matrix[i][k].m_containedEntity->Update();
                        }
                }
        }
}

void UpdateSelectionMenu(){
	instance = LEVEL_EDITOR;
	for(uint8_t i = 0; i < 100; i++){
		for(uint8_t k = 0; k < 100; k++){
			if (LevelLogic::entireSet.matrix[i][k].m_coinContainer){
				LevelLogic::entireSet.matrix[i][k].m_coinContainer->Update();
			}
                        if (LevelLogic::entireSet.matrix[i][k].m_containedEntity){
                                LevelLogic::entireSet.matrix[i][k].m_containedEntity->Update();
                        }
		}
	}
}

void Update(){
	running = true;
        while (running){
                if (WindowShouldClose()) running = false;
                ResfreshWindow();
		UI::NavigateUI();
		switch (UI::mode){
			case UIMode::MENU: break;
			case UIMode::SELECTION:
				UpdateSelectionMenu();
				break;
			case UIMode::GAME:
				UpdateTiles();
		}
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L)){
			LevelLogic::Reload();
		}
	}
}
