#include "de_timer.h"

//���������������� ������
void deTimer::init()
{
	//�������� ������� ������� � ����� ����
	frequency = getFrequency();
	tickLength = 1.0 / frequency;
}

//������� ������� �������
double deTimer::getFrequency()
{
	LARGE_INTEGER freq;

	if (!QueryPerformanceFrequency(&freq))
		return  0;
	return (double)freq.QuadPart;
}

//������� ����� (�� ���������� �������)
double deTimer::readTimer()
{
	//������������ ������ ������ ���� ����������
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	//������ ������� �����
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	//������������ ����� ������������� ���� ����������
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	//������� ������� �����
	return (currentTime.QuadPart - start.QuadPart) * tickLength;
}

//��������� ������
void deTimer::startTimer()
{
	//���������������� ������
	init();
	//������������ ������ ������ ���� ����������
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
	//������ ������� �����
	QueryPerformanceCounter(&start);
	//������������ ����� ������������� ���� ����������
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	//���������������� ������� � ������� ����� �������
	lastCheckTime = currentCheckTime = readTimer();
	//���������������� ����������� (����� ������ �� ������ � ��������)
	srand((int)start.QuadPart);
}

//�������� ������
void deTimer::updateTimer()
{
	//������� ����� ���������� �������
	lastCheckTime = currentCheckTime;
	//������� ����������
	currentCheckTime = readTimer();
}