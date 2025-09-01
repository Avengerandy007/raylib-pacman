#pragma once
#include <cstdint>
#include <memory>
#include "Entity.hpp"
#include "Matrix.hpp"

class Tile{
	void SetPosition(uint8_t x, uint8_t y);
public:
	std::shared_ptr<Rectangle> m_def; //Definition of tile
	std::unique_ptr<Entity>	m_containedEntity;
	static void InitTileSet();
	static void SetEntityRectangles();

	static Matrix2<Tile, 20> tileSet;
};
