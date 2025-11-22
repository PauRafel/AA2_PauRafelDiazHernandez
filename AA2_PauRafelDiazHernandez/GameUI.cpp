#include "GameUI.h"
#include "ConsoleControl.h"
#include <iostream>
#include <string>

GameUI::GameUI(int uiX, int uiY)
{
	_uiX = uiX;
	_uiY = uiY;
}

void GameUI::DrawPlayerStats(Player* player)
{
	CC::Lock();

	//Title
	CC::SetPosition(_uiX, _uiY);
	CC::SetColor(CC::YELLOW);
	std::cout << "=== PLAYER STATS ===";

	//Health
	CC::SetPosition(_uiX, _uiY + 2);
	CC::SetColor(CC::RED);
	std::cout << "HP: " << player->GetHealth() << "/" << player->GetMaxHealth() << "  ";

	//Coins
	CC::SetPosition(_uiX, _uiY + 3);
	CC::SetColor(CC::YELLOW);
	std::cout << "Coins: " << player->GetCoins() << "  ";

	//Potions
	CC::SetPosition(_uiX, _uiY + 4);
	CC::SetColor(CC::GREEN);
	std::cout << "Potions: " << player->GetPotions() << "  ";

	//Weapon
	CC::SetPosition(_uiX, _uiY + 5);
	CC::SetColor(CC::CYAN);
	std::cout << "Weapon: ";
	if (player->GetWeapon() == WeaponType::SWORD)
		std::cout << "Sword (R:1)  ";
	else
		std::cout << "Spear (R:2)  ";

	//Controls
	CC::SetPosition(_uiX, _uiY + 7);
	CC::SetColor(CC::WHITE);
	std::cout << "Controls:";
	CC::SetPosition(_uiX, _uiY + 8);
	std::cout << "WASD - Move/Attack";
	CC::SetPosition(_uiX, _uiY + 9);
	std::cout << "SPACE - Use Potion";
	CC::SetPosition(_uiX, _uiY + 10);
	std::cout << "ESC - Exit";

	CC::SetColor(CC::WHITE);
	CC::Unlock();
}

void GameUI::DrawMessage(std::string message, int line)
{
	CC::Lock();
	CC::SetPosition(_uiX, _uiY + 12 + line);
	CC::SetColor(CC::MAGENTA);

	//Clear line first
	std::cout << "                    ";
	CC::SetPosition(_uiX, _uiY + 12 + line);
	std::cout << message;

	CC::SetColor(CC::WHITE);
	CC::Unlock();
}

void GameUI::ClearMessages()
{
	CC::Lock();
	for (int i = 0; i < 5; i++)
	{
		CC::SetPosition(_uiX, _uiY + 12 + i);
		std::cout << "                    ";
	}
	CC::Unlock();
}