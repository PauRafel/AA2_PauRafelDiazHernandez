#include "Timer.h"
#include <thread>
#include <windows.h>

void Timer::SleepThread(unsigned long timeRequiredMiliseconds)
{
	Sleep(timeRequiredMiliseconds);
}

void Timer::BlockThreadWhile(BlockCheck blockCheck, unsigned long timeRequiredMilisecondsToNextCheck)
{
	bool checkSuccess = false;

	while (!checkSuccess)
	{
		if (timeRequiredMilisecondsToNextCheck != 0)
		{
			Sleep(timeRequiredMilisecondsToNextCheck);
		}
		checkSuccess = blockCheck();
	}
}

void Timer::StartTimer(unsigned long timeRequiredMiliseconds, OnTimeElapsed onTimeElapse)
{
	std::thread* thread = new std::thread([timeRequiredMiliseconds, onTimeElapse]() {
		Sleep(timeRequiredMiliseconds);
		onTimeElapse();
		});

	thread->detach();
}

void Timer::StartLoopTimer(unsigned long timeRequiredMiliseconds, OnTimeElapsedWithLoop onTimeElapse)
{
	std::thread* thread = new std::thread([timeRequiredMiliseconds, onTimeElapse]() {
		bool continueLoop = true;
		while (continueLoop)
		{
			Sleep(timeRequiredMiliseconds);
			continueLoop = onTimeElapse();
		}
		});

	thread->detach();
}