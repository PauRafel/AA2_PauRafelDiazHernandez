#pragma once
#include "Player.h"
#include <string>

class GameUI
{
private:
	int _uiX;
	int _uiY;

public:
	GameUI(int uiX = 35, int uiY = 2);
	~GameUI() {}

	void DrawPlayerStats(Player* player);
	void DrawMessage(std::string message, int line);
	void ClearMessages();
};