#include <iostream>
#include "ConsoleControl.h"
#include "KeyCodes.h"
#include "Map.h"
#include "GameUI.h"
#include "Player.h"
#include "Timer.h"

int main()
{
    CC::Clear();

    Map* gameMap = new Map(30, 20, 2, 2);

    Player* player = new Player(15, 10);
    gameMap->SetTile(player->GetX(), player->GetY(), TileType::PLAYER);

    gameMap->SetTile(15, 1, TileType::PORTAL_UP);
    gameMap->SetTile(15, 18, TileType::PORTAL_DOWN);
    gameMap->SetTile(1, 10, TileType::PORTAL_LEFT);
    gameMap->SetTile(28, 10, TileType::PORTAL_RIGHT);

    for (int i = 5; i < 15; i++)
    {
        gameMap->SetTile(10, i, TileType::WALL);
    }

    gameMap->SetTile(5, 5, TileType::CHEST);
    gameMap->SetTile(20, 15, TileType::ITEM);

    GameUI* ui = new GameUI(35, 2);

    gameMap->DrawFullMap();
    ui->DrawPlayerStats(player);


    CC::SetPosition(35, 15);
    CC::SetColor(CC::GREEN);
    std::cout << "[TEST]";

    CC::SetPosition(35, 16);
    CC::SetColor(CC::WHITE);
    std::cout << "Press 1: Add coins";
    CC::SetPosition(35, 17);
    std::cout << "Press 2: Use potion";
    CC::SetPosition(35, 18);
    std::cout << "Press 3: Take damage";
    CC::SetPosition(35, 19);
    std::cout << "Press 4: Change weapon";

    CC::SetPosition(0, 24);
    std::cout << "Press ESC to exit...";

    //Test loop
    bool running = true;
    while (running)
    {
        int key = CC::ReadNextKey();

        if (key == K_ESCAPE)
        {
            running = false;
        }
        else if (key == K_1)
        {
            player->AddCoins(10);
            ui->DrawPlayerStats(player);
            ui->DrawMessage("+ 10 coins!", 0);
        }
        else if (key == K_2)
        {
            player->UsePotion();
            ui->DrawPlayerStats(player);
            ui->DrawMessage("Potion used!", 0);
        }
        else if (key == K_3)
        {
            player->TakeDamage(2);
            ui->DrawPlayerStats(player);
            ui->DrawMessage("Took 2 damage!", 0);
        }
        else if (key == K_4)
        {
            if (player->GetWeapon() == WeaponType::SWORD)
                player->SetWeapon(WeaponType::SPEAR);
            else
                player->SetWeapon(WeaponType::SWORD);

            ui->DrawPlayerStats(player);
            ui->DrawMessage("Weapon changed!", 0);
        }

        Timer::SleepThread(50);
    }

    delete player;
    delete gameMap;
    delete ui;

    return 0;
}