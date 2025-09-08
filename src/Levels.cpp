#include "../include/Levels.hpp"
#include <filesystem>
#include <fstream>
#include <vector>

namespace LevelLogic{
	std::vector<std::string> levelData;
	void GetLevelData(std::vector<std::string>& list){
		for (const auto& entry : std::filesystem::directory_iterator("./levels")){
			const std::string name = entry.path().string();
			std::ifstream file(name);
			if (file.bad()) continue;
			list.push_back(FileI::FileContent(file));
		}
	}
}
