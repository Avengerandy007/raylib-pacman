#include "../include/Matrix.hpp"
#include "../include/Tile.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
namespace FileI{
	extern std::ifstream FindFile();
	extern std::string FileContent(std::ifstream& file);
	extern Matrix2<Tile, 20> CreateTileSet(std::string& fileContent);
	extern Matrix2<Tile, 20> MakeMatrix(std::ifstream& file);
}
