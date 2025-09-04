#include "../include/Update.hpp"
#include "../libpacman/include/FileI.hpp"
bool running = false;
void ResfreshWindow(){
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
}

void Reload(){
	Tile::tileSet = FileI::MakeMatrix(FileI::FindFile());
   	Tile::InitTileSet();
	Tile::SetEntityRectangles();
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
					Reload();
				}
                                Tile::tileSet.matrix[i][k].m_containedEntity->Update();
                        }
                }
        }
}

void Update(){
	running = true;
        while (running){
                if (WindowShouldClose()) running = false;
                ResfreshWindow();
                UpdateTiles();
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L)){
			Reload();
		}
	}
}
