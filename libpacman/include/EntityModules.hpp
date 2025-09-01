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
	Image image;
	Texture2D texture;
	void LoadTexturesInMap();
public:
	ImageTexture();
	ImageTexture(std::string fileName);
	void Render(std::shared_ptr<Rectangle> rect);
	~ImageTexture();
};

struct InputHandler{
	void ProccesInput(Controller& controller);
};
