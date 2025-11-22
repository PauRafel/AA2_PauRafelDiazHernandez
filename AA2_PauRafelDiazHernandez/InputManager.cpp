#include "InputManager.h"
#include "ConsoleControl.h"
#include "KeyCodes.h"
#include "Timer.h"

InputManager::InputManager()
{
	_inputMutex = new std::mutex();
	_isRunning = false;
	_lastCommand = InputCommand::NONE;
	_commandProcessed = true;
	_inputThread = nullptr;
}

InputManager::~InputManager()
{
	Stop();
	delete _inputMutex;
}

void InputManager::Start()
{
	if (_isRunning)
		return;

	_isRunning = true;
	_inputThread = new std::thread(&InputManager::InputLoop, this);
}

void InputManager::Stop()
{
	if (!_isRunning)
		return;

	_isRunning = false;

	if (_inputThread != nullptr)
	{
		if (_inputThread->joinable())
			_inputThread->join();

		delete _inputThread;
		_inputThread = nullptr;
	}
}

void InputManager::InputLoop()
{
	while (_isRunning)
	{
		int key = CC::ReadNextKey();

		if (key != 0)
		{
			_inputMutex->lock();

			//Only set new command if previous was processed
			if (_commandProcessed)
			{
				switch (key)
				{
				case K_W:
					_lastCommand = InputCommand::MOVE_UP;
					_commandProcessed = false;
					break;
				case K_S:
					_lastCommand = InputCommand::MOVE_DOWN;
					_commandProcessed = false;
					break;
				case K_A:
					_lastCommand = InputCommand::MOVE_LEFT;
					_commandProcessed = false;
					break;
				case K_D:
					_lastCommand = InputCommand::MOVE_RIGHT;
					_commandProcessed = false;
					break;
				case K_SPACE:
					_lastCommand = InputCommand::USE_POTION;
					_commandProcessed = false;
					break;
				case K_ESCAPE:
					_lastCommand = InputCommand::EXIT_GAME;
					_commandProcessed = false;
					break;
				default:
					break;
				}
			}

			_inputMutex->unlock();
		}

		Timer::SleepThread(50); 
	}
}

InputCommand InputManager::GetCommand()
{
	_inputMutex->lock();

	InputCommand cmd = InputCommand::NONE;

	if (!_commandProcessed && _lastCommand != InputCommand::NONE)
	{
		cmd = _lastCommand;
		_lastCommand = InputCommand::NONE;
		_commandProcessed = true;
	}

	_inputMutex->unlock();

	return cmd;
}

bool InputManager::HasCommand()
{
	_inputMutex->lock();
	bool hasCmd = !_commandProcessed;
	_inputMutex->unlock();
	return hasCmd;
}