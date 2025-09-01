#include "../include/Matrix.hpp"
#include "../include/Tile.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
namespace FileI{
	extern std::ifstream FindFile();
	extern Matrix2<Tile, 20> MakeMatrix(std::ifstream file);
}
