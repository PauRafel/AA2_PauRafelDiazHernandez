#include "WorldManager.h"
#include "ConsoleControl.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

WorldManager::WorldManager(int worldWidth, int worldHeight)
{
	_worldWidth = worldWidth;
	_worldHeight = worldHeight;
	_currentMapX = worldWidth / 2;
	_currentMapY = worldHeight / 2;
	_worldMutex = new std::mutex();

	srand(static_cast<unsigned int>(time(nullptr)));

	CreateWorldMaps();
	_currentMap = _worldMaps[_currentMapY][_currentMapX];
}

WorldManager::~WorldManager()
{
	for (int y = 0; y < _worldHeight; y++)
	{
		for (int x = 0; x < _worldWidth; x++)
		{
			delete _worldMaps[y][x];
		}
	}
	delete _worldMutex;
}

void WorldManager::CreateWorldMaps()
{
	_worldMaps.resize(_worldHeight);

	for (int y = 0; y < _worldHeight; y++)
	{
		_worldMaps[y].resize(_worldWidth);
		for (int x = 0; x < _worldWidth; x++)
		{
			_worldMaps[y][x] = new Map(30, 20, 2, 2);
			SetupMapPortals(x, y);
			AddRandomWalls(_worldMaps[y][x]);
		}
	}
}

void WorldManager::SetupMapPortals(int mapX, int mapY)
{
	Map* map = _worldMaps[mapY][mapX];

	//Portal UP (if not top edge)
	if (mapY > 0)
	{
		map->SetTile(15, 1, TileType::PORTAL_UP);
	}

	//Portal DOWN (if not bottom edge)
	if (mapY < _worldHeight - 1)
	{
		map->SetTile(15, 18, TileType::PORTAL_DOWN);
	}

	//Portal LEFT (if not left edge)
	if (mapX > 0)
	{
		map->SetTile(1, 10, TileType::PORTAL_LEFT);
	}

	//Portal RIGHT (if not right edge)
	if (mapX < _worldWidth - 1)
	{
		map->SetTile(28, 10, TileType::PORTAL_RIGHT);
	}
}

void WorldManager::AddRandomWalls(Map* map)
{
	//Add  random walls
	int numWalls = rand() % 3 + 2;

	for (int i = 0; i < numWalls; i++)
	{
		int startX = rand() % 20 + 5;
		int startY = rand() % 12 + 4;
		int wallLength = rand() % 5 + 3;
		bool horizontal = rand() % 2 == 0;

		for (int j = 0; j < wallLength; j++)
		{
			int x = horizontal ? startX + j : startX;
			int y = horizontal ? startY : startY + j;

			if (map->IsValidPosition(x, y) && map->GetTile(x, y)->type == TileType::EMPTY)
			{
				map->SetTile(x, y, TileType::WALL);
			}
		}
	}
}

bool WorldManager::ChangeMap(TileType portalType, int& playerX, int& playerY)
{
	int newMapX = _currentMapX;
	int newMapY = _currentMapY;
	int newPlayerX = playerX;
	int newPlayerY = playerY;

	//Spawns
	switch (portalType)
	{
	case TileType::PORTAL_UP:
		if (_currentMapY > 0)
		{
			newMapY = _currentMapY - 1;
			newPlayerY = 17; //Bottom
		}
		else
			return false;
		break;

	case TileType::PORTAL_DOWN:
		if (_currentMapY < _worldHeight - 1)
		{
			newMapY = _currentMapY + 1;
			newPlayerY = 2; //Top
		}
		else
			return false;
		break;

	case TileType::PORTAL_LEFT:
		if (_currentMapX > 0)
		{
			newMapX = _currentMapX - 1;
			newPlayerX = 27; //Right
		}
		else
			return false;
		break;

	case TileType::PORTAL_RIGHT:
		if (_currentMapX < _worldWidth - 1)
		{
			newMapX = _currentMapX + 1;
			newPlayerX = 2; //Left
		}
		else
			return false;
		break;

	default:
		return false;
	}

	_currentMapX = newMapX;
	_currentMapY = newMapY;
	_currentMap = _worldMaps[_currentMapY][_currentMapX];

	playerX = newPlayerX;
	playerY = newPlayerY;

	return true;
}

void WorldManager::DrawCurrentMap()
{
	CC::Clear();
	_currentMap->DrawFullMap();

	CC::Lock();
	CC::SetPosition(0, 0);
	CC::SetColor(CC::CYAN);
	std::cout << "Map [" << _currentMapX << "," << _currentMapY << "]";
	CC::SetColor(CC::WHITE);
	CC::Unlock();
}