#pragma once

enum class TileType
{
	EMPTY = 0,
	WALL = 1,
	PORTAL_UP = 2,
	PORTAL_DOWN = 3,
	PORTAL_LEFT = 4,
	PORTAL_RIGHT = 5,
	PLAYER = 6,
	ENEMY = 7,
	CHEST = 8,
	ITEM = 9
};

class Tile
{
public:
	TileType type;
	char symbol;
	int colorForeground;
	int colorBackground;

	Tile();
	Tile(TileType type);
	~Tile() {}

	void SetType(TileType newType);
	bool IsWalkable();
	bool IsPortal();
};