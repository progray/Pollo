/* 
��������cpp���������еĶ������ƺ����ͽӿ�
*/
#include "StdAfx.h"
#include "Action.h"

Action::Action(void)
{
	xLocation	= 500;
	yLocation	= 500;
	Speed_Pollo.xSpeed		= 1;
	Speed_Pollo.ySpeed		= -80;
	preCursor.x = 0;
	preCursor.y = 0;
	nowCursor.x = 0;
	nowCursor.y = 0;
	InCircleFlag = FALSE;
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

	Speed_Pollo.ySpeed += dGravity * dFrequency;	//��ǰ�ٶȵ��� t*a+v

	if(currpt.y >= cyClient - DIAMETER)
	{
		Speed_Pollo.xSpeed -= FRICTION * Speed_Pollo.xSpeed;
	}
	//��������ṩ��ײ
	double Distance = sqrt(double(pow((double)(nowCursor.x - currpt.x), 2) + pow((double)(nowCursor.y - currpt.y), 2)));

	//double Speed = sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2));

	if(MouseLBFlag)	//���������϶�
	{
		Speed_Pollo.ySpeed = Speed_Cursor.ySpeed;
		Speed_Pollo.xSpeed = Speed_Cursor.xSpeed;

		xLocation = nowCursor.x;
		yLocation = nowCursor.y;
	}

	else if(Distance <= DIAMETER)
	{
		if(InCircleFlag == FALSE)
		{
			Speed_Pollo = CalVectorSpeed();
			InCircleFlag = TRUE;
		}
	}

	if(Distance > DIAMETER)
	{
		InCircleFlag = FALSE;
	}
}

SPEED Action::CalVectorSpeed()
{
	double CursorAngle = atan((double)(nowCursor.y - currpt.y) / (nowCursor.x - currpt.x + 0.0001)); //ָ����pollo��ײʱ�ĽǶ�
	double RealCursorAngle = CursorAngle - PI;	//�õ�ָ������ٶȵĽǶ�
	//arctanֵ��Ϊ-2/PI��2/PI���޷�������нǶȣ����Ҫ�������λ�����Ӽ��Ƕȵõ���ʵ�Ƕ�
	if (nowCursor.x - currpt.x < 0 && nowCursor.y - currpt.y >= 0)
	{
		CursorAngle = CursorAngle + PI;
		RealCursorAngle = RealCursorAngle + PI;
	}
	else if (nowCursor.x - currpt.x < 0 && nowCursor.y - currpt.y < 0)
	{
		CursorAngle = CursorAngle - PI;
		RealCursorAngle = RealCursorAngle - PI;
	}

	double CircleAngle = atan((double)(Speed_Pollo.ySpeed / (Speed_Pollo.xSpeed + 0.0001)));//Ϊ�˷�ֹ����0 //pollo������ٶȽǶ�
	//arctanֵ��Ϊ-2/PI��2/PI���޷�������нǶȣ����Ҫ�������λ�����Ӽ��Ƕȵõ���ʵ�Ƕ�
	if (Speed_Pollo.xSpeed < 0 && Speed_Pollo.ySpeed >= 0)
	{
		CircleAngle = CircleAngle + PI;
	}
	else if (Speed_Pollo.xSpeed < 0 && Speed_Pollo.ySpeed < 0)
	{
		CircleAngle = CircleAngle - PI;
	}
	
	double CursorMoveAngle = atan((double)(Speed_Cursor.ySpeed) / (Speed_Cursor.xSpeed + 0.0001));	//ָ���ƶ�ʱ�ĽǶ�
	//arctanֵ��Ϊ-2/PI��2/PI���޷�������нǶȣ����Ҫ�������λ�����Ӽ��Ƕȵõ���ʵ�Ƕ�
	if (Speed_Cursor.xSpeed < 0 && Speed_Cursor.ySpeed >= 0)
	{
		CursorMoveAngle = CursorMoveAngle + PI;
	}
	else if (Speed_Cursor.xSpeed < 0 && Speed_Cursor.ySpeed < 0)
	{
		CursorMoveAngle = CursorMoveAngle - PI;
	}

	double CursorSpeedAngle = fabs(CursorMoveAngle - RealCursorAngle);	//ָ����ٶ�ͨ���ýǶȴ�����Ч�ٶ�

	double ResultAngle;

	SPEED ResultSpeed;	//��ײ������ٶ�����
	ResultSpeed.xSpeed = Speed_Pollo.xSpeed;
	ResultSpeed.ySpeed = Speed_Pollo.ySpeed;

	double MPolloSpeed;	//pollo Speed��ģ
	double MCursorSpeed;//ָ���ٶȵ�ģ
	ResultAngle = abs(CircleAngle - CursorAngle);

	//ֻ�е�pollo�ٶȽǶȺ�ָ����ײ�Ƕȵļн�С��90��ʱ�����������Ϊ�����������
	if(ResultAngle <= PI/2 && ResultAngle >= -PI/2)
	{
		MPolloSpeed = sqrt(pow(Speed_Pollo.xSpeed, 2) + pow(Speed_Pollo.ySpeed, 2));	//Pollo�����ٶȵ�ģ
		MCursorSpeed = MPolloSpeed * cos(ResultAngle) * 2;	//ͨ����ײ��ָ�����pollo���ٶȵ�ģ
		MCursorSpeed += sqrt(pow(Speed_Cursor.xSpeed, 2) + pow(Speed_Cursor.ySpeed, 2)) * cos(CursorSpeedAngle);	//ָ�����ṩ����Ч�ٶȼӳ�

		ResultSpeed.xSpeed = MCursorSpeed * cos(RealCursorAngle);	//ͨ���ٶȵ�ģ��ָ������ٶȵķ��򣬼���������������֮����ٶ�����
		ResultSpeed.ySpeed = MCursorSpeed * sin(RealCursorAngle);

		ResultSpeed.xSpeed = ResultSpeed.xSpeed + Speed_Pollo.xSpeed;	//ͨ����pollo�����ٶ�������ƽ��λ�ƣ��ó���ʵ���ٶ�����
		ResultSpeed.ySpeed = ResultSpeed.ySpeed + Speed_Pollo.ySpeed;
	}
	//����ײ�нǲ���������ĽǶ�ʱ����Ϊ������Ӽ���
	else
	{
		MCursorSpeed = sqrt(pow(Speed_Cursor.xSpeed, 2) + pow(Speed_Cursor.ySpeed, 2)) * cos(CursorSpeedAngle);		//ָ�����ṩ����Ч�ٶȼӳ�

		ResultSpeed.xSpeed = MCursorSpeed * cos(RealCursorAngle);	//ͨ��ָ���ṩ���ٶȵ�ģ��ָ����ײ�ķ��򣬼����ָ���ṩ���ٶȵ�����
		ResultSpeed.ySpeed = MCursorSpeed * sin(RealCursorAngle);

		ResultSpeed.xSpeed += Speed_Pollo.xSpeed;	//ͨ����pollo�����ٶ�����ƽ�Ƶ�ָ���ٶ������ϣ����������ӵĽ��
		ResultSpeed.ySpeed += Speed_Pollo.ySpeed;
	}

	return ResultSpeed;
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
	POINT OutPoint[PTNUM];		//���ڼ���ĵ�
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

	SelectObject(hdcEyes, hBitEyes);

	//HDC hdcRotateBuff;
	//Rotate(hBitEyes, 0, hdcBuffer, hdcRotateBuff);

	BitBlt(hdcBuffer, pt.x + 7, pt.y - 18, 14, 17, hdcEyes, 0, 0, SRCAND);
	BitBlt(hdcBuffer, pt.x + 23, pt.y - 28, 14, 17, hdcEyes, 0, 0, SRCAND);

	//BitBlt(hdcBuffer, pt.x + 7, pt.y - 18, 14, 17, hdcRotateBuff, 0, 0, SRCAND);


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

	Speed_Cursor.xSpeed = nowCursor.x - preCursor.x;
	Speed_Cursor.ySpeed = nowCursor.y - preCursor.y;
}

void Action::GetMouseLButton(bool LBStatus)
{
	MouseLBFlag = LBStatus;
}

void Action::Rotate(HBITMAP hBmpSrc, float angle, HDC hdcSrc, HDC &hdcDst)	//���Ƕ���תͼ��
{
	HBITMAP hBmpDst;

	hdcDst = CreateCompatibleDC(hdcSrc);
	hBmpDst = CreateCompatibleBitmap(hdcDst, 14, 17);
	SelectObject(hdcDst, hBmpDst);

	pBGR src, dst, dstLine;
	src = MyGetDibBits(hdcSrc, hBmpSrc, 14, 17);
	dst = MyGetDibBits(hdcDst, hBmpDst, 14, 17);

	dstLine = dst;
	for(int i = 0; i < 14 * 17; ++i)
	{
		dstLine[i] = src[i];
	}

	// Set the new Bitmap	
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = 14;
	bi.bmiHeader.biHeight = 17;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 14 * 4 * 17;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	SetDIBits(hdcDst, hBmpDst, 0, 100, dst, &bi, DIB_RGB_COLORS);
	DeleteObject(hBmpDst);

	free(dst);
	free(src);
}

pBGR Action::MyGetDibBits(HDC hdcSrc, HBITMAP hBmpSrc, int nx, int ny)
{
	BITMAPINFO bi;
	BOOL bRes;
	pBGR buf;

	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = nx;
	bi.bmiHeader.biHeight = - ny;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = nx * 4 * ny;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buf = (pBGR) malloc(nx * 4 * ny);
	bRes = GetDIBits(hdcSrc, hBmpSrc, 0, ny, buf, &bi, DIB_RGB_COLORS);
	if (!bRes) {
		free(buf);
		buf = 0;
	}
	return buf;
}

