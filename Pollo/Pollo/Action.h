#pragma once
#include <atlimage.h>
#include <windows.h>
#include <math.h>

#define PTNUM		100					//�滭�ĵ������
#define DIAMETER	50					//�뾶
#define PI			3.1415926			//��
#define AREA        DIAMETER*DIAMETER*PI//���
#define GRAVITY     1					//����
#define TIMER_CLK   16					//��ʱ������
#define TPROPOR		41					//����ʵʱ��ı������������ص�����ʵ�������������ʱ�����������ٶ�
#define ELASTICLOSS 3					//������ʧ
#define FRICTION	0.1					//����Ħ��

typedef struct			//�ƶ��ٶ�
{
	double xSpeed;
	double ySpeed;
}SPEED;

typedef struct ssBGR {	//ÿһ�����ص�Ĳ���
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char pad;
}sBGR, *pBGR;	

class Action
{
public:
	Action(void);
	~Action(void);
	void DrawCirCle(HBITMAP, POINT);	//��Pollo~	
	void SurfaceChange(int, int);		//����߽�仯
	void CirCleMove(HBITMAP);			//Pollo�ƶ�
	void CalSpeed();					//�����µ��ٶȵļ���
	double CalVectorAngle(SPEED);		//����������ˮƽ�ߵļн�
	SPEED CalVectorSpeed();				//��ײ�������
	void GetBitMap(HINSTANCE);
	void GetCurrCursor(POINT);
	void GetMouseLButton(bool);			//��ȡ������״̬
	void Rotate(HBITMAP, float, HDC, HDC &);
	pBGR MyGetDibBits(HDC hdcSrc, HBITMAP hBmpSrc, int nx, int ny);
	//int CalBezierPoint(HDC, int, int, int, POINT);	//���㱴�������ߣ�����ǿ�������������ͨ������������״̬
private:
	SPEED Speed_Pollo;	//�ƶ��ٶ�
	SPEED Speed_Cursor;	//����ٶ�

	POINT currpt;		//��ǰλ��
	POINT preCursor;	//���ǰһ��λ��
	POINT nowCursor;	//��굱ǰλ��
	double xLocation;	//����POINT���������ƶ�����double������ʵ��λ��
	double yLocation;
	int cxClient;		//�����С
	int cyClient;
	HBITMAP hBitEyes;	//�۾�
	HBITMAP hBitShadow;	//��Ӱ
	bool InCircleFlag;
	bool MouseLBFlag;	//��¼���LB״̬ 1Ϊ���£�0Ϊ�ͷ�
};

