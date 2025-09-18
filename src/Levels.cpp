#include "../include/Levels.hpp"
#include <algorithm>
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

			{
				uint16_t ch = 0;
				level.coinCount = FileI::GetCoinCount(level.data, ch);
			}

			level.data.erase(0, std::to_string(level.coinCount).length() + 1);

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
		entireData.append(10000, '0');
		for (auto& level : levelData){
			uint16_t charToChange = level.Y * level.X;
			uint8_t substrID = 0;
			for (uint8_t i = 0; i < 3; i++){
				for(uint8_t k = 0; k < 20; k++){
					entireData[charToChange + k] = level.data[substrID];
					substrID++;
				}
				charToChange += (100 - level.Y) + level.Y;
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
