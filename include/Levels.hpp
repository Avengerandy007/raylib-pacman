#pragma once
#include <array>
#include <vector>
#include <string>
#include "../libpacman/include/FileI.hpp"
#include "../libpacman/include/Matrix.hpp"

struct Level{
	uint16_t X, Y;
	uint16_t coinCount;
	std::string data;
	std::string name;
};

namespace LevelLogic{
	extern std::vector<Level> levelData;
	extern void CreateLevels(std::vector<std::string>& list);
	extern void Reload();
}
