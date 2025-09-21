#pragma once
#include <vector>
#include <string>
#include "../libpacman/include/FileI.hpp"

struct Level{
	uint16_t X, Y;
	uint16_t coinCount;
	std::string data;
	std::string name;
	
	void Load();
	void Update();
};



namespace LevelLogic{
	extern std::vector<Level> levelData;
	extern Matrix2<Tile, 100> entireSet;
	extern std::string inputedName;
	extern bool listeningForName;

	extern void GetLevelData(std::vector<Level>& list);
	extern Matrix2<Tile, 100> SetTileSet();
	extern void SelectionScreen();
	extern void GetNameInput();
	extern void SelectLevel(const std::string& levelName);

	extern void LoadRandomLevel();

	extern void Reload();
}
