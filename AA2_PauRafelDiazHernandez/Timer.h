#pragma once
#include <functional>

static class Timer
{
public:
	typedef std::function<bool()> BlockCheck;
	typedef std::function<void()> OnTimeElapsed;
	typedef std::function<bool()> OnTimeElapsedWithLoop;

	static void SleepThread(unsigned long timeRequiredMiliseconds);
	static void BlockThreadWhile(BlockCheck blockCheck, unsigned long timeRequiredMilisecondsToNextCheck = 0);
	static void StartTimer(unsigned long timeRequiredMiliseconds, OnTimeElapsed onTimeElapse);
	static void StartLoopTimer(unsigned long timeRequiredMiliseconds, OnTimeElapsedWithLoop onTimeElapse);
};