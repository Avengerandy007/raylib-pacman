#include "../include/Levels.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include "../Raylib/include/raylib.h"
#include <vector>
#include "../include/UI.hpp"


void Level::Load(){
	UI::mode = UIMode::GAME;

	Wall::Texture().Resize(50);
	Player::Texture().Resize(50);
	Coin::Texture().Resize(50);
	Ghost::Texture().Resize(50);


	Tile::tileSet = FileI::CreateTileSet<20>(data, 0);
	Coin::coinCount = coinCount;
   	Tile::InitTileSet<20>(50, Tile::tileSet);
	Tile::SetEntityRectangles<20>(Tile::tileSet);

	std::cout << "Loaded " << name << "\n";
}

void Level::Update(){
	DrawText(name.c_str(), X * 10, Y * 10 + 21 * 10, 32, WHITE);
}


namespace LevelLogic{
	std::vector<Level> levelData;
	Matrix2<Tile, 100> entireSet;
	std::string inputedName = "";
	bool listeningForName = false;

	void SelectionScreen(){
		UI::mode = UIMode::SELECTION;

		Wall::Texture().Resize(10);
		Player::Texture().Resize(10);
		Coin::Texture().Resize(10);
		Ghost::Texture().Resize(10);

		LevelLogic::GetLevelData(LevelLogic::levelData);
		LevelLogic::entireSet = LevelLogic::SetTileSet();
		Tile::InitTileSet<100>(10, LevelLogic::entireSet);
		Tile::SetEntityRectangles<100>(LevelLogic::entireSet);
	}

	void GetLevelData(std::vector<Level>& list){
		uint8_t currentLevel = 0;
		uint16_t currentY = 0;
		uint16_t currentX = 0;

		for (const auto& entry : std::filesystem::directory_iterator("./levels")){
			//Get file from dir
			std::ifstream file;
			std::string name;
			{
				const std::string path = entry.path().string();
				file.open(path);
				
				if (file.bad()) continue;
				//Get the name of the file
				uint16_t currentChar = path.length() - 2;
				while (path[currentChar - 1] != '/'){
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
			if (currentLevel % 5 == 0 && currentLevel != 0){
				currentX = 0;
				currentY += 25;
				std::cout << "Going 1 down\n";
			}else if (currentLevel != 0){
				std::cout << "Going 1 left\n";
				currentX += 20;
			}
			
			level.Y = currentY;
			level.X = currentX;

			std::cout << name << " level: " << currentLevel << " is placed at " << level.X << "," << level.Y << "\n";
			currentLevel++;

			list.push_back(level);
		}
	}

	 Matrix2<Tile, 100> SetTileSet(){
		std::string entireData = "";
		entireData.append(10000, '0');
		for (auto& level : levelData){
			uint16_t charToChange = level.X * 100 + level.Y;
			uint16_t substrID = 0;
			for (uint8_t i = 0; i < 20; i++){
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



	void GetNameInput(){
		int key = GetCharPressed();
		while (key > 0){
			if (key >= 32 && key <= 126){
				inputedName += static_cast<char>(key);
			}
			key = GetCharPressed();
		}
	}

	
	void SelectLevel(const std::string &levelName){
		for(auto& level : levelData){
			if (levelName == level.name){
				std::cout << levelName << " matches " << level.name << "\n";
				level.Load();
			}else{
				std::cout << levelName << " does not match " << level.name << "\n";
			}
		}
	}


	void Reload(){
		std::ifstream file = FileI::FindFile();
		Tile::tileSet = FileI::MakeMatrix(file);
   		Tile::InitTileSet<20>(50, Tile::tileSet);
		Tile::SetEntityRectangles<20>(Tile::tileSet);
	}
}
