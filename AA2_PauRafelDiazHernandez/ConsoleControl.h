#pragma once
#include <mutex>
#include <iostream>
#include <sstream>
#include <Windows.h>

static class ConsoleControl {
private:
	HANDLE _console = GetStdHandle(STD_OUTPUT_HANDLE);
	std::mutex* _consoleMutex = new std::mutex();
	static ConsoleControl GetInstance();
	static HANDLE GetConsole();

public:
	enum ConsoleColor {
		BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, LIGHTGREY,
		DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
	};

	//Change color of text and background / Change position and where the next write start
	static void SetColor(ConsoleColor TextColor = WHITE, ConsoleColor BackgroundColor = BLACK);
	static void SetPosition(short int x, short int y);
	static void Clear();

	//Fill console with specific character
	static void FillWithCharacter(char character, ConsoleColor ForeColor, ConsoleColor BackColor);

	//Delete buffer
	static void ClearKeyBuffer();

	//Try to read the currently pressed key, not blocks the code
	static int ReadNextKey();

	//Reads the next key pressed / Reads the next character pressed and blocks the code until a key is pressed
	static int WaithForReadNextKey();
	static char WaitForReadNextChar();

	//Lock/Unlock private mutex
	static void Lock();
	static void Unlock();
};

using CC = ConsoleControl;