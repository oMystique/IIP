#ifndef __DE_TIMER_H
#define __DE_TIMER_H

#include <windows.h>

//класс таймера
class deTimer
{
	LARGE_INTEGER start; //начальное время
	double frequency; //частота таймера
	double tickLength; //длина одного тика таймера
	double currentCheckTime; //текущий замер времени
	double lastCheckTime; //предыдущий замер времени
						  //инициализировать таймер
	void init();
	//вернуть частоту таймера
	double getFrequency();
	//вернуть время (от начального времени)
	double readTimer();
public:
	//запустить таймер
	void startTimer();
	//обновить таймер
	void updateTimer();
	//получить временной отрезок между текущим замером и предыдущим
	//обратите внимание: время здесь не замеряется,
	// только лишь возвращается уже замерянный результат
	double getTimeInterval() { return currentCheckTime - lastCheckTime; }
};

#endif