#pragma once
#include <thread>
#include <mutex>
#include <atomic>

enum class InputCommand
{
	NONE = 0,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	USE_POTION,
	EXIT_GAME
};

class InputManager
{
private:
	std::thread* _inputThread;
	std::mutex* _inputMutex;
	std::atomic<bool> _isRunning;
	InputCommand _lastCommand;
	bool _commandProcessed;

	void InputLoop();

public:
	InputManager();
	~InputManager();

	void Start();
	void Stop();

	//Get and consume command (returns NONE if no new command) and check if there's a pending command
	InputCommand GetCommand();
	bool HasCommand();
};