#include <vector>
#include <string>
#include "../libpacman/include/FileI.hpp"
#include "../libpacman/include/Matrix.hpp"

namespace LevelLogic{
	extern std::vector<std::string> levelData;
	extern void CreateLevels(std::vector<std::string>& list);
	extern void Reload();
}
