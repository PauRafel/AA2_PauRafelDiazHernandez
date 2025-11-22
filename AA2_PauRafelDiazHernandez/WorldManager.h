#pragma once
#include "Map.h"
#include <vector>
#include <mutex>

struct MapCoordinates
{
	int worldX;
	int worldY;

	MapCoordinates(int x, int y) : worldX(x), worldY(y) {}

	bool operator==(const MapCoordinates& other) const
	{
		return worldX == other.worldX && worldY == other.worldY;
	}
};

class WorldManager
{
private:
	std::vector<std::vector<Map*>> _worldMaps;
	int _worldWidth; 
	int _worldHeight;
	int _currentMapX;
	int _currentMapY;
	Map* _currentMap;
	std::mutex* _worldMutex;

	void CreateWorldMaps();
	void SetupMapPortals(int mapX, int mapY);
	void AddRandomWalls(Map* map);

public:
	WorldManager(int worldWidth = 3, int worldHeight = 3);
	~WorldManager();

	Map* GetCurrentMap() { return _currentMap; }
	MapCoordinates GetCurrentCoordinates() { return MapCoordinates(_currentMapX, _currentMapY); }

	bool ChangeMap(TileType portalType, int& playerX, int& playerY);
	void DrawCurrentMap();

	void Lock() { _worldMutex->lock(); }
	void Unlock() { _worldMutex->unlock(); }
};