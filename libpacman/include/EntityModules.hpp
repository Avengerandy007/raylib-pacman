#pragma once
#include "../../Raylib/include/raylib.h"
#include <cstdint>
#include <memory>
#include <string>

class Controller{
	uint16_t m_speed;
	bool CheckWall(uint8_t& destx, uint8_t& desty);
public:
	uint8_t X, Y;
	bool m_calledMoveThisFrame;
	Vector2 dir;
	Controller(uint16_t speed, uint8_t x, uint8_t y);
	void Move();
};

class Tile;
struct TileCollider{
	bool Colliding(Tile& currentTile);
};

class ImageTexture{
	static const std::string path;
	const std::string name;
	Image image;
	Texture2D texture;
public:
	ImageTexture();
	ImageTexture(const std::string fileName);
	void Resize(const uint8_t size);
	void Render(std::shared_ptr<Rectangle> rect);
	~ImageTexture();
};

struct InputHandler{
	void ProccesInput(Controller& controller);
};
