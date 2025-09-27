#pragma once
#include "EntityModules.hpp"
#include <memory>
#include <vector>
#include <string>

enum TypeId{
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	COIN = 3,
	GHOST = 4,
};

enum TYPE_OF_INSTANCE{
	LEVEL_EDITOR,
	GAME,
};

extern TYPE_OF_INSTANCE instance;

class Entity{
public:
	std::shared_ptr<Rectangle> rect;
	TypeId typeId; 
	virtual void Update() = 0;
};

class Wall : public Entity{
public:
	static ImageTexture& Texture();
	Wall();
	void Update() override;
};

class Coin : public Entity{
public:
	static uint16_t coinCount;
	static ImageTexture& Texture();
	Coin();
	void Update() override;
};

class Player : public Entity{
	TileCollider collider;
	InputHandler input;
	void HandleCollisions(Tile& currentTile);
public:
	static uint32_t score;
	Controller controller;
	static ImageTexture& Texture();
	Player();
	Player(uint8_t x, uint8_t y);
	void Update() override;
};

class Ghost : public Entity{
	Controller controller;
	void DecideDirections();
	uint8_t framesSinceLastMove;
public:
	static ImageTexture& Texture();
	Ghost();
	Ghost(uint8_t x, uint8_t y);
	void Update() override;
};
