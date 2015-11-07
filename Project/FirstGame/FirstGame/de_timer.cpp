#include "de_timer.h"

//инициализировать таймер
void deTimer::init()
{
	//получить частоту таймера и длину тика
	frequency = getFrequency();
	tickLength = 1.0 / frequency;
}

//вернуть частоту таймера
double deTimer::getFrequency()
{
	LARGE_INTEGER freq;

	if (!QueryPerformanceFrequency(&freq))
		return  0;
	return (double)freq.QuadPart;
}

//вернуть время (от начального времени)
double deTimer::readTimer()
{
	//использовать только первое ядро процессора
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	//засечь текущее время
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	//восстановить маску использования ядер процессора
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	//вернуть текущее время
	return (currentTime.QuadPart - start.QuadPart) * tickLength;
}

//запустить таймер
void deTimer::startTimer()
{
	//инициализировать таймер
	init();
	//использовать только первое ядро процессора
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	//засечь текущее время
	QueryPerformanceCounter(&start);
	//восстановить маску использования ядер процессора
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	//инициализировать текущий и прошлый замер времени
	lastCheckTime = currentCheckTime = readTimer();
	//инициализировать рандомайзер (можно убрать из класса в принципе)
	srand((int)start.QuadPart);
}

//обновить таймер
void deTimer::updateTimer()
{
	//текущий замер становится прошлым
	lastCheckTime = currentCheckTime;
	//текущий замеряется
	currentCheckTime = readTimer();
}