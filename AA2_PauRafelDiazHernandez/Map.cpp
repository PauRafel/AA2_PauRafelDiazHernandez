#include "Map.h"
#include "ConsoleControl.h"
#include <iostream>

Map::Map(int width, int height, int offsetX, int offsetY)
{
	_width = width;
	_height = height;
	_offsetX = offsetX;
	_offsetY = offsetY;
	_mapMutex = new std::mutex();

	//Init grid
	_tiles.resize(_height);
	for (int y = 0; y < _height; y++)
	{
		_tiles[y].resize(_width);
		for (int x = 0; x < _width; x++)
		{
			_tiles[y][x] = new Tile(TileType::EMPTY);
		}
	}

	//Create wall border
	for (int x = 0; x < _width; x++)
	{
		_tiles[0][x]->SetType(TileType::WALL);
		_tiles[_height - 1][x]->SetType(TileType::WALL);
	}

	for (int y = 0; y < _height; y++)
	{
		_tiles[y][0]->SetType(TileType::WALL);
		_tiles[y][_width - 1]->SetType(TileType::WALL);
	}
}

Map::~Map()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			delete _tiles[y][x];
		}
	}
	delete _mapMutex;
}

Tile* Map::GetTile(int x, int y)
{
	if (!IsValidPosition(x, y))
		return nullptr;

	return _tiles[y][x];
}

void Map::SetTile(int x, int y, TileType type)
{
	if (!IsValidPosition(x, y))
		return;

	_tiles[y][x]->SetType(type);
}

void Map::DrawTile(int x, int y)
{
	if (!IsValidPosition(x, y))
		return;

	Tile* tile = _tiles[y][x];

	CC::Lock();
	CC::SetPosition(_offsetX + x, _offsetY + y);
	CC::SetColor((CC::ConsoleColor)tile->colorForeground, (CC::ConsoleColor)tile->colorBackground);
	std::cout << tile->symbol;
	CC::SetColor(CC::WHITE, CC::BLACK);
	CC::Unlock();
}

void Map::DrawFullMap()
{
	CC::Lock();
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			Tile* tile = _tiles[y][x];
			CC::SetPosition(_offsetX + x, _offsetY + y);
			CC::SetColor((CC::ConsoleColor)tile->colorForeground, (CC::ConsoleColor)tile->colorBackground);
			std::cout << tile->symbol;
		}
	}
	CC::SetColor(CC::WHITE, CC::BLACK);
	CC::Unlock();
}

void Map::ClearMap()
{
	for (int y = 1; y < _height - 1; y++)
	{
		for (int x = 1; x < _width - 1; x++)
		{
			_tiles[y][x]->SetType(TileType::EMPTY);
		}
	}
}

bool Map::IsValidPosition(int x, int y)
{
	return x >= 0 && x < _width && y >= 0 && y < _height;
}

bool Map::IsWalkable(int x, int y)
{
	if (!IsValidPosition(x, y))
		return false;

	return _tiles[y][x]->IsWalkable();
}