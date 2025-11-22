#include <iostream>
#include "ConsoleControl.h"
#include "KeyCodes.h"
#include "Map.h"
#include "GameUI.h"
#include "Player.h"
#include "Timer.h"
#include "WorldManager.h"
#include "GameManager.h"

int main()
{
	GameManager* game = new GameManager();

	game->Initialize();
	game->Run();

	delete game;

	return 0;
}