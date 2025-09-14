#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include "Entity.hpp"
#include "Matrix.hpp"

class Tile{
	void SetPosition(const uint8_t x, const uint8_t y, const uint8_t size) const;
public:
	std::shared_ptr<Rectangle> m_def; //Definition of tile
	std::unique_ptr<Entity>	m_containedEntity;
	std::unique_ptr<Coin> m_coinContainer;

	template<uint16_t matrixSize>
	static void InitTileSet(const uint8_t tileSize, Matrix2<Tile, matrixSize>& set){
		uint8_t x = 0, y = 0;
		for (; x < matrixSize; x++){
			y = 0;
			for (; y < matrixSize; y++){
				set.matrix[x][y].m_def = std::make_shared<Rectangle>();
				set.matrix[x][y].SetPosition(x, y, tileSize);
			}
		}
	
	}
	template<uint16_t matrixSize>
	static void SetEntityRectangles(Matrix2<Tile, matrixSize>& set){
		for (uint8_t i = 0; i < matrixSize; i++){
				for(uint8_t k = 0; k < matrixSize; k++){
					if (set.matrix[i][k].m_containedEntity) set.matrix[i][k].m_containedEntity->rect = set.matrix[i][k].m_def;
					if (set.matrix[i][k].m_coinContainer) set.matrix[i][k].m_coinContainer->rect = set.matrix[i][k].m_def;
				}
			}
	}

	static Matrix2<Tile, 20> tileSet;
};
