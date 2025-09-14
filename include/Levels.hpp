#pragma once
#include <vector>
#include <string>
#include "../libpacman/include/FileI.hpp"

struct Level{
	uint16_t X, Y;
	uint16_t coinCount;
	std::string data;
	std::string name;
};

namespace LevelLogic{
	extern std::vector<Level> levelData;
	extern Matrix2<Tile, 100> entireSet;
	extern void GetLevelData(std::vector<Level>& list);
	extern Matrix2<Tile, 100> SetTileSet();
	extern void Reload();
}
