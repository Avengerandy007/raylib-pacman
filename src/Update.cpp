#include "../include/Update.hpp"
#include <iostream>
bool running = false;
void ResfreshWindow(){
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
}

void UpdateTiles(){
	Player* player;
        for (uint8_t i = 0; i < 20; i++){
                for (uint8_t k = 0; k < 20; k++){
                        if (!Tile::tileSet.matrix[i][k].m_containedEntity) continue;
                        else{
				player = Tile::tileSet.matrix[i][k].m_containedEntity->typeId == PLAYER ? dynamic_cast<Player*>(Tile::tileSet.matrix[i][k].m_containedEntity.get()) : nullptr;
				if (player && (int)player->score == (int)Coin::coinCount) running = false;
                                Tile::tileSet.matrix[i][k].m_containedEntity->Update();
                        }
                }
        }
}

void Update(){
	running = true;
	std::cout << "Coin count in level: " << (int)Coin::coinCount << "\n";
        while (running){
                if (WindowShouldClose()) running = false;
                ResfreshWindow();
                UpdateTiles();
	}
}
