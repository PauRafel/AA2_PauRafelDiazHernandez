#include <iostream>
#include "ConsoleControl.h"
#include "KeyCodes.h"
#include "Map.h"
#include "GameUI.h"
#include "Player.h"
#include "Timer.h"
#include "WorldManager.h"

int main()
{
    CC::Clear();

    WorldManager* world = new WorldManager(3, 3);
    Player* player = new Player(15, 10);
    GameUI* ui = new GameUI(35, 2);

    world->DrawCurrentMap();
    world->GetCurrentMap()->SetTile(player->GetX(), player->GetY(), TileType::PLAYER);
    world->GetCurrentMap()->DrawTile(player->GetX(), player->GetY());
    ui->DrawPlayerStats(player);

    CC::SetPosition(35, 15);
    CC::SetColor(CC::YELLOW);
    std::cout << "=== CONTROLS ===";
    CC::SetPosition(35, 16);
    CC::SetColor(CC::WHITE);
    std::cout << "WASD - Move";
    CC::SetPosition(35, 17);
    std::cout << "SPACE - Use Potion";
    CC::SetPosition(35, 18);
    std::cout << "ESC - Exit";

    CC::SetPosition(35, 20);
    CC::SetColor(CC::CYAN);
    std::cout << "Walk into portals";
    CC::SetPosition(35, 21);
    std::cout << "to change rooms!";

    CC::SetPosition(0, 24);
    CC::SetColor(CC::WHITE);
    std::cout << "Press ESC to exit...";

    //Game loop
    bool running = true;
    while (running)
    {
        int key = CC::ReadNextKey();

        if (key == K_ESCAPE)
        {
            running = false;
        }
        else if ((key == K_W || key == K_A || key == K_S || key == K_D) && player->CanMove())
        {
            int newX = player->GetX();
            int newY = player->GetY();

            if (key == K_W) newY--;
            else if (key == K_S) newY++;
            else if (key == K_A) newX--;
            else if (key == K_D) newX++;

            Map* currentMap = world->GetCurrentMap();

            if (currentMap->IsValidPosition(newX, newY))
            {
                Tile* targetTile = currentMap->GetTile(newX, newY);

                if (targetTile->IsPortal())
                {
                    currentMap->SetTile(player->GetX(), player->GetY(), TileType::EMPTY);
                    currentMap->DrawTile(player->GetX(), player->GetY());

                    if (world->ChangeMap(targetTile->type, newX, newY))
                    {
                        world->DrawCurrentMap();
                        player->SetPosition(newX, newY);
                        ui->DrawPlayerStats(player); 
                        ui->DrawMessage("Changed room!", 0);
                    }

                    currentMap = world->GetCurrentMap();
                }
                else if (currentMap->IsWalkable(newX, newY))
                {
                    currentMap->SetTile(player->GetX(), player->GetY(), TileType::EMPTY);
                    currentMap->DrawTile(player->GetX(), player->GetY());

                    player->SetPosition(newX, newY);
                }

                currentMap->SetTile(player->GetX(), player->GetY(), TileType::PLAYER);
                currentMap->DrawTile(player->GetX(), player->GetY());

                player->UpdateMoveTime();
            }
        }
        else if (key == K_SPACE)
        {
            int oldHealth = player->GetHealth();
            player->UsePotion();
            if (player->GetHealth() > oldHealth)
            {
                ui->DrawPlayerStats(player);
                ui->DrawMessage("Used potion!", 0);
            }
            else
            {
                ui->DrawMessage("No potions!", 0);
            }
        }

        Timer::SleepThread(50);
    }

    delete player;
    delete world;
    delete ui;

    return 0;
}