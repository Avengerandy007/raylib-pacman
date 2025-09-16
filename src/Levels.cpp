#include "../include/Levels.hpp"
#include <bits/stdc++.h>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace LevelLogic{
	std::vector<Level> levelData;
	Matrix2<Tile, 100> entireSet;
	void GetLevelData(std::vector<Level>& list){

		uint8_t currentLevel = 0;
		uint16_t currentY = 25;

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
				std::cout << "Read: " << name << "\n";
			}
			
			//Create level and assign data to it
			Level level;
			level.data = FileI::FileContent(file);

			//Get coin count of level
			{
				uint16_t currentChar = 0;
				std::string coinCount = "";
				// amount of coins can't be bigger than 3 chars +1 for ','
				while(currentChar <= 3){
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
			std::cout << name << " contains: " << level.data << "\n";
			//Set positions for levels
			if (currentLevel % 2 == 0 && currentLevel != 0){
				level.X = 0;
				currentY += 25;
			}else{
				level.X = 25;
			}
			
			level.Y = currentY;

			std::cout << name << " level: " << currentLevel << " is placed at " << level.X << "," << level.Y << "\n";
			currentLevel++;

			list.push_back(level);
		}
	}

	 Matrix2<Tile, 100> SetTileSet(){
		std::string entireData = "";
		for (uint8_t i = 0; i < 100; i++){
			for (uint8_t k = 0; k < 100; k++){
				for(auto& level : levelData){
					if (level.X == i && level.Y == k){
						uint8_t currentChar = 0;
						for(uint8_t j = 0; j < 4; j++){
							entireData += level.data.substr(currentChar, currentChar + 20);
							currentChar += 20;
							for (uint8_t l = 0; l < 100 - (level.Y + 20); l++) entireData += "0";
						}
					}else entireData += "0";
				}
			}
		}
		std::cout << "Entire screen data: " << entireData << "\n";
		return FileI::CreateTileSet<100>(entireData, 0);
	}

	void Reload(){
		std::ifstream file = FileI::FindFile();
		Tile::tileSet = FileI::MakeMatrix(file);
   		Tile::InitTileSet<20>(50, Tile::tileSet);
		Tile::SetEntityRectangles<20>(Tile::tileSet);
	}
}
