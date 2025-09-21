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
					UI::mode = UIMode::MENU;
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

	for (auto& level : LevelLogic::levelData){
		level.Update();
	}

	if (LevelLogic::listeningForName){ 
		LevelLogic::GetNameInput();
		DrawText(LevelLogic::inputedName.c_str(), 0, 968, 32, WHITE);
	}else{
		DrawText("Press 'I' to enter level name", 0, 968, 32, WHITE);
	}
	if (IsKeyPressed(KEY_I)) LevelLogic::listeningForName = true;
	if (IsKeyPressed(KEY_BACKSPACE) && LevelLogic::listeningForName && LevelLogic::inputedName != "") LevelLogic::inputedName.pop_back();
	if (IsKeyPressed(KEY_ENTER)){
		LevelLogic::SelectLevel(LevelLogic::inputedName);
		LevelLogic::inputedName.clear();
		LevelLogic::listeningForName = false;
	}

}

void UpdateMenu(){
	DrawText("SHIT PACMAN", 250, 100, 64, YELLOW);
	DrawText("'S' - LEVEL SELECTION", 250, 300, 32, WHITE);
	DrawText("'R' - RANDOM LEVEL", 250, 350, 32, WHITE);
	DrawText("'Q' - QUIT", 250, 400, 32, WHITE);
}

void Update(){
	running = true;
        while (running){
                if (WindowShouldClose()) running = false;
                ResfreshWindow();
		UI::NavigateUI();
		switch (UI::mode){
			case UIMode::MENU:
				UpdateMenu();
				break;
			case UIMode::SELECTION:
				UpdateSelectionMenu();
				break;
			case UIMode::GAME:
				instance = GAME;
				UpdateTiles();
				break;
		}
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L)){
			LevelLogic::Reload();
		}
	}
}
