#include <iostream>
#include "ConsoleControl.h"
#include "KeyCodes.h"
#include "Map.h"

int main()
{
    CC::Clear();

    //Test Map
    Map* testMap = new Map(30, 20, 2, 2);

    testMap->SetTile(15, 0, TileType::PORTAL_UP);
    testMap->SetTile(15, 19, TileType::PORTAL_DOWN);
    testMap->SetTile(0, 10, TileType::PORTAL_LEFT);
    testMap->SetTile(29, 10, TileType::PORTAL_RIGHT);

    for (int i = 5; i < 15; i++)
    {
        testMap->SetTile(10, i, TileType::WALL);
    }

    testMap->SetTile(5, 5, TileType::CHEST);
    testMap->SetTile(20, 15, TileType::ENEMY);
    testMap->SetTile(15, 10, TileType::PLAYER);

    testMap->DrawFullMap();

    //Info
    CC::SetPosition(0, 0);
    CC::SetColor(CC::YELLOW);
    std::cout << "MAP TEST";

    CC::SetPosition(35, 2);
    CC::SetColor(CC::WHITE);
    std::cout << "Legend:";
    CC::SetPosition(35, 3);
    std::cout << "# = Wall";
    CC::SetPosition(35, 4);
    CC::SetColor(CC::CYAN);
    std::cout << "^v<> = Portals";
    CC::SetPosition(35, 5);
    CC::SetColor(CC::YELLOW);
    std::cout << "@ = Player";
    CC::SetPosition(35, 6);
    CC::SetColor(CC::RED);
    std::cout << "E = Enemy";
    CC::SetPosition(35, 7);
    CC::SetColor(CC::DARKYELLOW);
    std::cout << "C = Chest";

    CC::SetPosition(0, 24);
    CC::SetColor(CC::WHITE);
    std::cout << "Press any key to exit...";

    CC::WaithForReadNextKey();

    delete testMap;
    return 0;
}