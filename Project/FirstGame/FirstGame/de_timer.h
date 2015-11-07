#ifndef __DE_TIMER_H
#define __DE_TIMER_H

#include <windows.h>

//����� �������
class deTimer
{
	LARGE_INTEGER start; //��������� �����
	double frequency; //������� �������
	double tickLength; //����� ������ ���� �������
	double currentCheckTime; //������� ����� �������
	double lastCheckTime; //���������� ����� �������
						  //���������������� ������
	void init();
	//������� ������� �������
	double getFrequency();
	//������� ����� (�� ���������� �������)
	double readTimer();
public:
	//��������� ������
	void startTimer();
	//�������� ������
	void updateTimer();
	//�������� ��������� ������� ����� ������� ������� � ����������
	//�������� ��������: ����� ����� �� ����������,
	// ������ ���� ������������ ��� ���������� ���������
	double getTimeInterval() { return currentCheckTime - lastCheckTime; }
};

#endif