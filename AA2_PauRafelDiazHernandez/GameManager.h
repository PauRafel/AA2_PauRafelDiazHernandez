#pragma once
#include "WorldManager.h"
#include "InputManager.h"
#include "Player.h"
#include "GameUI.h"
#include <atomic>

class GameManager
{
private:
	WorldManager* _world;
	Player* _player;
	InputManager* _inputManager;
	GameUI* _ui;
	std::atomic<bool> _isRunning;

	void ProcessInput();
	void HandleMovement(int deltaX, int deltaY);
	void HandlePotion();

public:
	GameManager();
	~GameManager();

	void Initialize();
	void Run();
	void Stop();
};