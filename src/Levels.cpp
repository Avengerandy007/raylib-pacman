#include "../include/Levels.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace LevelLogic{
	std::vector<Level> levelData;
	void GetLevelData(std::vector<Level>& list){
		for (const auto& entry : std::filesystem::directory_iterator("./levels")){
			//Get file from dir
			const std::string name = entry.path().string();
			std::ifstream file(name);
			if (file.bad()) continue;
			
			//Create level and assign data to it
			Level level;
			level.name = name;
			level.data = FileI::FileContent(file);
			//Get coin count of level
			{
				uint16_t currentChar = 0;
				std::string coinCount = "";
				while(currentChar <= 400){
					if (level.data[currentChar] == ','){
						level.data.erase(level.data.begin() + currentChar);
						break;
					}
					coinCount += level.data[currentChar];
					currentChar++;
				}
				level.coinCount = std::stoi(coinCount);
			}
			

			list.push_back(level);
		}
	}

	void Reload(){
		std::ifstream file = FileI::FindFile();
		Tile::tileSet = FileI::MakeMatrix(file);
   		Tile::InitTileSet(50);
		Tile::SetEntityRectangles();
	}
}
