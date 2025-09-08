#pragma once
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
	static void InitTileSet(const uint8_t size);
	static void SetEntityRectangles();

	static Matrix2<Tile, 20> tileSet;
};
