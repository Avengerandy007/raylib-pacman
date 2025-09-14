#include "../include/Matrix.hpp"
#include "../include/Tile.hpp"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
namespace FileI{
	extern std::ifstream FindFile();
	extern std::string FileContent(std::ifstream& file);
	extern uint16_t GetCoinCount(const std::string& fileContent, uint16_t& currentChar);
	extern Matrix2<Tile, 20> CreateTileSet(std::string& fileContent, const uint16_t startChar);
	extern Matrix2<Tile, 20> MakeMatrix(std::ifstream& file);
}
