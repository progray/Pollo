#pragma once
#include <atlimage.h>
#include <windows.h>
#include <math.h>

#define PTNUM		100					//�滭�ĵ������
#define DIAMETER	50					//�뾶
#define PI			3.1415926			//��
#define AREA        DIAMETER*DIAMETER*PI//���
#define GRAVITY     10					//����
#define TIMER_CLK   16					//��ʱ������
#define TPROPOR		41					//����ʵʱ��ı������������ص�����ʵ�������������ʱ�����������ٶ�
#define ELASTICLOSS 1.3					//������ʧ

class Action
{
public:
	Action(void);
	~Action(void);
	void DrawCirCle(HBITMAP, POINT);	//��Pollo~
	void CirCleMove(HBITMAP);	//Pollo�ƶ�
	void SurfaceChange(int, int);	//����߽�仯
	void CalSpeed();
	void GetBitMap(HINSTANCE);
	void GetCurrCursor(POINT);

	double ResultAngle;

	//int CalBezierPoint(HDC, int, int, int, POINT);	//���㱴�������ߣ�����ǿ�������������ͨ������������״̬
private:
	POINT currpt;		//��ǰλ��
	POINT preCursor;	//���ǰһ��λ��
	POINT nowCursor;	//��굱ǰλ��
	double xLocation;	//����POINT���������ƶ�����double������ʵ��λ��
	double yLocation;
	int cxClient;		//�����С
	int cyClient;
	double xSpeed;		//�ٶ�
	double ySpeed;
	double xCursorSpeed;//����ٶ�
	double yCursorSpeed;
	HBITMAP hBitEyes;	//�۾�
	HBITMAP hBitShadow;
	char InCircleFlag;
};

