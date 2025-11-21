#pragma once
#include "Tile.h"
#include <vector>
#include <mutex>

class Map
{
private:
	int _width;
	int _height;
	int _offsetX; 
	int _offsetY;
	std::vector<std::vector<Tile*>> _tiles;
	std::mutex* _mapMutex;

public:
	Map(int width, int height, int offsetX = 0, int offsetY = 0);
	~Map();

	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	Tile* GetTile(int x, int y);

	//Operations
	void SetTile(int x, int y, TileType type);
	void DrawTile(int x, int y);
	void DrawFullMap();
	void ClearMap();

	//Utilities
	bool IsValidPosition(int x, int y);
	bool IsWalkable(int x, int y);


	void Lock() { _mapMutex->lock(); }
	void Unlock() { _mapMutex->unlock(); }
};