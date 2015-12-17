/* Version: v1.0
   Owner: Swell_Fish
   Remarks: Now I'm learning the Palette.But don't wantted stop
			commit new thing.So modify some Notes to make it looks better
*/
#include "StdAfx.h"
#include "Action.h"

Action::Action(void)
{
	xLocation	= 500;
	yLocation	= 500;
	Speed_Pollo.xSpeed		= 0;
	Speed_Pollo.ySpeed		= -80;
	preCursor.x = 0;
	preCursor.y = 0;
	nowCursor.x = 0;
	nowCursor.y = 0;
	InCircleFlag = 0;
}


Action::~Action(void)
{
}

void Action::CalSpeed()
{
	double dGravity = GRAVITY;
	double dFrequency = (double)TIMER_CLK/TPROPOR;

	if(yLocation < DIAMETER || yLocation > cyClient - DIAMETER)
	{
		Speed_Pollo.ySpeed = -(Speed_Pollo.ySpeed / ELASTICLOSS);
	}

	if(xLocation < DIAMETER || xLocation > cxClient - DIAMETER)
	{
		Speed_Pollo.xSpeed = -(Speed_Pollo.xSpeed / ELASTICLOSS);
	}

	Speed_Pollo.ySpeed += dGravity * dFrequency;	//当前速度等于 t*a+v

	//用鼠标来提供碰撞
	double Distance = sqrt(double(pow((double)(nowCursor.x - currpt.x), 2) + pow((double)(nowCursor.y - currpt.y), 2)));

	double CursorAngle = atan((double)(nowCursor.y - currpt.y) / (nowCursor.x - currpt.x));
	double CircleAngle = atan((double)(Speed_Pollo.ySpeed / Speed_Pollo.xSpeed));
	ResultAngle = PI - (CursorAngle * 2 - CircleAngle);
	if(ResultAngle > PI * 2)
	{
		ResultAngle = PI * 2;
	}
	if(ResultAngle < 0)
	{
		ResultAngle = 0.0001;
	}
	if(InCircleFlag == 0 && Distance <= DIAMETER)
	{
		if(nowCursor.x - currpt.x > 0)
		{
			Speed_Pollo.ySpeed = -sin(ResultAngle) * sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2)) + yCursorSpeed;
			Speed_Pollo.xSpeed = cos(ResultAngle) * sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2)) + xCursorSpeed;
		}
		else// if(nowCursor.x - currpt.x <= 0)
		{
			Speed_Pollo.ySpeed = sin(ResultAngle) * sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2)) + yCursorSpeed;
			Speed_Pollo.xSpeed = -cos(ResultAngle) * sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2)) + xCursorSpeed;
		}
		InCircleFlag = 1;
	}

	if(Distance > DIAMETER)
	{
		InCircleFlag = 0;
	}
}

void Action::CirCleMove(HBITMAP hBitMap)
{
	double dFrequency = (double)TIMER_CLK/TPROPOR;


	xLocation += Speed_Pollo.xSpeed * dFrequency;
	yLocation += Speed_Pollo.ySpeed * dFrequency;

	CalSpeed();

	if(yLocation > cyClient - DIAMETER)
	{
		yLocation = cyClient - DIAMETER;
	}

	if(xLocation > cxClient - DIAMETER)
	{
		xLocation = cxClient - DIAMETER;
	}

	if(yLocation < DIAMETER)
	{
		yLocation = DIAMETER;
	}

	if(xLocation < DIAMETER)
	{
		xLocation = DIAMETER;
	}

	currpt.x = (int)xLocation;
	currpt.y = (int)yLocation;

	DrawCirCle(hBitMap, currpt);
}

void Action::DrawCirCle(HBITMAP hBitMap, POINT pt)
{
	POINT OutPoint[PTNUM];		//用于计算的点
	POINT InPoint[PTNUM];
	int ptNum;
	HDC hdcBuffer, hdcEyes, hdcShadow;
	HBRUSH hBrush;
	static int i = 1000;

	hdcBuffer = CreateCompatibleDC(NULL);
	hdcEyes = CreateCompatibleDC(NULL);
	hdcShadow = CreateCompatibleDC(NULL);

	SelectObject(hdcBuffer, hBitMap);
	PatBlt(hdcBuffer, 0, 0, cxClient, cyClient, WHITENESS);
	for(ptNum=0; ptNum<PTNUM; ptNum++)
	{
		OutPoint[ptNum].x = (int)(DIAMETER * cos(2 * PI * ((double)ptNum+1) / (double)PTNUM)) + pt.x;
		OutPoint[ptNum].y = (int)(DIAMETER * sin(2 * PI * ((double)ptNum+1) / (double)PTNUM)) + pt.y;
		InPoint[ptNum].x = (int)((DIAMETER - 1) * cos(2 * PI * ((double)ptNum+1) / (double)PTNUM)) + pt.x;
		InPoint[ptNum].y = (int)((DIAMETER - 1) * sin(2 * PI * ((double)ptNum+1) / (double)PTNUM)) + pt.y;
		if(InPoint[ptNum].y < pt.y)
		{
			InPoint[ptNum].y = pt.y;
		}
	}
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	SelectObject(hdcBuffer,GetStockObject(NULL_BRUSH));
	Polygon(hdcBuffer, OutPoint, PTNUM);
	SelectObject(hdcBuffer, GetStockObject(NULL_PEN));
	hBrush = CreateSolidBrush(RGB(100, 255, 0));
	//SelectObject(hdcBuffer, GetStockObject(LTGRAY_BRUSH));
	SelectObject(hdcBuffer, hBrush);
	Polygon(hdcBuffer, InPoint, PTNUM);
	SelectObject(hdcBuffer, GetStockObject(BLACK_PEN));
	//CalBezierPoint(hdcBuffer, 1, 10, 1, pt);

	SelectObject(hdcEyes, hBitEyes);
	BitBlt(hdcBuffer, pt.x + 7, pt.y - 18, 14, 17, hdcEyes, 0, 0, SRCAND);
	BitBlt(hdcBuffer, pt.x + 23, pt.y - 28, 14, 17, hdcEyes, 0, 0, SRCAND);

	SelectObject(hdcShadow, hBitShadow);
	BLENDFUNCTION Blendfunction;
	Blendfunction.BlendOp = AC_SRC_OVER;
	Blendfunction.BlendFlags = 0;
	Blendfunction.SourceConstantAlpha = 50;
	Blendfunction.AlphaFormat = 0x00;

	AlphaBlend(hdcBuffer, pt.x - DIAMETER, pt.y - DIAMETER, DIAMETER * 2, DIAMETER * 2, hdcShadow, 0, 0, DIAMETER * 2, DIAMETER * 2, Blendfunction);
	DeleteDC(hdcBuffer);
	DeleteDC(hdcEyes);
	DeleteDC(hdcShadow);
}

void Action::SurfaceChange(int txClient, int tyClient)
{
	cxClient = txClient;
	cyClient = tyClient;
}

void Action::GetBitMap(HINSTANCE hInstance)
{
	hBitEyes = LoadBitmap(hInstance, TEXT("Eyes"));
	hBitShadow = LoadBitmap(hInstance, TEXT("Shadow"));
}

void Action::GetCurrCursor(POINT currCursor)
{
	preCursor = nowCursor;
	nowCursor = currCursor;

	xCursorSpeed = nowCursor.x - preCursor.x;
	yCursorSpeed = nowCursor.y - preCursor.y;
}
//******iStatus 表示在目前震动的状态，数值为1-50***************//
//******iStrength表示目前震动的强度，数值范围待定**************//
//int Action::CalBezierPoint(HDC hdcBuffer, int xPoint, int iStrength, int iStatus, POINT pt)
//{
//	POINT CtrlPoint[4];
//	static int i = 10;
//	static int flag = 0;
//	static int k = 80;
//
//	CtrlPoint[0].x = pt.x - DIAMETER;
//	CtrlPoint[0].y = pt.y;
//
//	CtrlPoint[1].x = pt.x - DIAMETER + iStrength;
//	CtrlPoint[1].y = pt.y - i;
//	
//	CtrlPoint[2].x = pt.x + DIAMETER - iStrength;
//	CtrlPoint[2].y = pt.y + i;
//
//	CtrlPoint[3].x = pt.x + DIAMETER;
//	CtrlPoint[3].y = pt.y;
//
//	PolyBezier(hdcBuffer, CtrlPoint, 4);
//
//	/*
//	double t = 0.3;
//	int y = (int)((pt.x - DIAMETER) * pow((1-t),3) + 
//			3 * CtrlPoint[0].x * t * pow((1-t),2) +
//			3 * CtrlPoint[1].x * pow(t, 2)*(1-t) +
//			pt.x + DIAMETER * pow(t,3));
//	*/
//
//	if(flag == 1)
//	{
//		i += 6;
//		if(i >= k)
//		{
//			flag = 0;
//			k -= 2;
//			return 0;
//		}
//	}
//
//	if(flag == 0)
//	{
//		i -= 6;
//		if(i <= -k)
//		{
//			flag = 1;
//			k -= 2;
//		}
//	}
//	return 0;
//}
