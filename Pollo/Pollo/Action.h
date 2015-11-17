#pragma once
#include <windows.h>
#include <math.h>

#define PTNUM		100					//�滭�ĵ������
#define DIAMETER	50					//�뾶
#define PI			3.1415926			//��
#define AREA        DIAMETER*DIAMETER*PI//���
#define GRAVITY     10					//����
#define TIMER_CLK   10					//��ʱ������
#define TPROPOR		41					//����ʵʱ��ı������������ص�����ʵ�������������ʱ�����������ٶ�
#define ELASTICLOSS 1.3					//������ʧ

class Action
{
public:
	Action(void);
	~Action(void);
	void DrawCirCle(HBITMAP, POINT);	//��Pollo~
	void CirCleMove(HBITMAP, POINT);	//Pollo�ƶ�
	void SurfaceChange(int, int);	//����߽�仯
	void CalSpeed();
	void GetEyesBitMap(HINSTANCE);
private:
	POINT currpt;		//��ǰλ��
	double xLocation;	//����POINT���������ƶ�����double������ʵ��λ��
	double yLocation;
	int cxClient;		//�����С
	int cyClient;
	double xSpeed;		//�ٶ�
	double ySpeed;
	HBITMAP hBitEyes;	//�۾�
};
