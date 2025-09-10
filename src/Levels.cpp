#include "../include/Levels.hpp"
#include <bits/stdc++.h>
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
			std::ifstream file;
			std::string name;
			{
				const std::string path = entry.path().string();
				file.open(path);
				
				if (file.bad()) continue;
				//Get the name of the file
				uint16_t currentChar = path.length() - 1;
				while (path[currentChar] != '/'){
					currentChar--;
					name += path[currentChar];
				}
				
				std::reverse(name.begin(), name.end());
			}
			
			//Create level and assign data to it
			Level level;
			level.data = FileI::FileContent(file);
			//Get coin count of level
			{
				uint16_t currentChar = 0;
				std::string coinCount = "";
				// ammount of coins can't be bigger than 3 chars +1 for ','
				while(currentChar <= 4){
					if (level.data[currentChar] == ','){
						level.data.erase(level.data.begin() + currentChar);
						break;
					}
					coinCount += level.data[currentChar];
					currentChar++;
				}
				level.coinCount = std::stoi(coinCount);
			}
			
			level.name = name;

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
