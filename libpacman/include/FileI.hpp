#include "../include/Matrix.hpp"
#include "../include/Tile.hpp"
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>

namespace FileI{
	extern std::ifstream FindFile();
	extern std::string FileContent(std::ifstream& file);
	extern uint16_t GetCoinCount(const std::string& fileContent, uint16_t& currentChar);

	template<size_t matrixSize>
	Matrix2<Tile, matrixSize> CreateTileSet(std::string& fileContent, const uint16_t startChar){
		Matrix2<Tile, matrixSize> matrix;
				
		uint16_t currentChar = startChar;

		for (uint32_t i = 0; i < matrixSize; i++){
			for (uint32_t k = 0; k < matrixSize; k++){
				switch (fileContent[currentChar]) {
					case '0':
						break;

					case '1':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Wall>();
						break;

					case '2':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Player>(i, k);
						break;

					case '3':
						matrix.matrix[i][k].m_coinContainer= std::make_unique<Coin>();
						break;
					case '4':
						matrix.matrix[i][k].m_containedEntity = std::make_unique<Ghost>(i, k);
						break;

					default:
						std::cout << "Unrecognized char " << fileContent[currentChar] << "at: " << (int)currentChar << "\n";
						break;

				}
				currentChar++;
			}
		}
		std::cout << "Finished creating matrix\n";
		return matrix;
	}
	extern Matrix2<Tile, 20> MakeMatrix(std::ifstream& file);
}
