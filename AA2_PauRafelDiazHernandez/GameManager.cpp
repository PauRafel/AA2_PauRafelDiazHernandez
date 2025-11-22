#include "GameManager.h"
#include "Timer.h"
#include "ConsoleControl.h"

GameManager::GameManager()
{
	_world = nullptr;
	_player = nullptr;
	_inputManager = nullptr;
	_ui = nullptr;
	_isRunning = false;
}

GameManager::~GameManager()
{
	if (_inputManager != nullptr)
		delete _inputManager;
	if (_player != nullptr)
		delete _player;
	if (_world != nullptr)
		delete _world;
	if (_ui != nullptr)
		delete _ui;
}

void GameManager::Initialize()
{
	CC::Clear();

	_world = new WorldManager(3, 3);
	_player = new Player(15, 10);
	_ui = new GameUI(35, 2);
	_inputManager = new InputManager();

	_world->DrawCurrentMap();
	_world->GetCurrentMap()->SetTile(_player->GetX(), _player->GetY(), TileType::PLAYER);
	_world->GetCurrentMap()->DrawTile(_player->GetX(), _player->GetY());
	_ui->DrawPlayerStats(_player);

	CC::Lock();
	CC::SetPosition(35, 15);
	CC::SetColor(CC::YELLOW);
	std::cout << "=== DUNGEON CRAWLER ===";
	CC::SetPosition(35, 17);
	CC::SetColor(CC::GREEN);
	std::cout << "[INPUT THREAD TEST]";
	CC::SetPosition(35, 19);
	CC::SetColor(CC::WHITE);
	std::cout << "Game running...";
	CC::Unlock();
}

void GameManager::Run()
{
	_isRunning = true;

	_inputManager->Start();

	while (_isRunning)
	{
		ProcessInput();
		Timer::SleepThread(50);
	}

	_inputManager->Stop();
}

void GameManager::Stop()
{
	_isRunning = false;
}

void GameManager::ProcessInput()
{
	InputCommand cmd = _inputManager->GetCommand();

	switch (cmd)
	{
	case InputCommand::MOVE_UP:
		HandleMovement(0, -1);
		break;
	case InputCommand::MOVE_DOWN:
		HandleMovement(0, 1);
		break;
	case InputCommand::MOVE_LEFT:
		HandleMovement(-1, 0);
		break;
	case InputCommand::MOVE_RIGHT:
		HandleMovement(1, 0);
		break;
	case InputCommand::USE_POTION:
		HandlePotion();
		break;
	case InputCommand::EXIT_GAME:
		Stop();
		break;
	default:
		break;
	}
}

void GameManager::HandleMovement(int deltaX, int deltaY)
{
	if (!_player->CanMove())
		return;

	_player->Lock();
	int newX = _player->GetX() + deltaX;
	int newY = _player->GetY() + deltaY;
	_player->Unlock();

	_world->Lock();
	Map* currentMap = _world->GetCurrentMap();

	if (currentMap->IsValidPosition(newX, newY))
	{
		Tile* targetTile = currentMap->GetTile(newX, newY);

		if (targetTile->IsPortal())
		{
			currentMap->SetTile(_player->GetX(), _player->GetY(), TileType::EMPTY);
			currentMap->DrawTile(_player->GetX(), _player->GetY());

			if (_world->ChangeMap(targetTile->type, newX, newY))
			{
				_world->DrawCurrentMap();
				_player->Lock();
				_player->SetPosition(newX, newY);
				_player->Unlock();
				_ui->DrawPlayerStats(_player);
				_ui->DrawMessage("Changed room!", 0);
			}

			currentMap = _world->GetCurrentMap();
		}
		else if (currentMap->IsWalkable(newX, newY))
		{
			currentMap->SetTile(_player->GetX(), _player->GetY(), TileType::EMPTY);
			currentMap->DrawTile(_player->GetX(), _player->GetY());

			_player->Lock();
			_player->SetPosition(newX, newY);
			_player->Unlock();
		}

		currentMap->SetTile(_player->GetX(), _player->GetY(), TileType::PLAYER);
		currentMap->DrawTile(_player->GetX(), _player->GetY());

		_player->UpdateMoveTime();
	}

	_world->Unlock();
}

void GameManager::HandlePotion()
{
	_player->Lock();
	int oldHealth = _player->GetHealth();
	_player->UsePotion();
	int newHealth = _player->GetHealth();
	_player->Unlock();

	_ui->DrawPlayerStats(_player);

	if (newHealth > oldHealth)
	{
		_ui->DrawMessage("Used potion!", 0);
	}
	else
	{
		_ui->DrawMessage("No potions!", 0);
	}
}