#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;					// current instance
TCHAR szTitle[]="Game";			// The title bar text
TCHAR szWindowClass[]="MyClass";	// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


////////////////////////////
POINT ball; //��������� ����
RECT player; //��������� ���������
int st=0; //������� ��������� �� ���������
char sc[5];//������ �������� ��� ������ �� �����
char speed[2];//������ �������� ���� ��� ������ �� �����
bool isGameStart; //���� �������� ����
int cx,cy; //�������� ���� �� � � �� �
int cxVector,cyVector; //����������� ���� �� � � �� �
char scp[]="Points  ";//������ ����� ��������� ���-�� ��������� ����
char cxs[]="Speed= ";//������ ����� ��������� ��������
char helpS[]="S � start/stop game";  //��������� � ������� ������� ����������
char helpP[]="P � pause game";
char helpSp[]="Use UP and DOWN arrows to change ball speed";
////////////////////////////


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WTBBRAIN);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) //���� ��������� ���������
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance) //����������� ������ �������� ����
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //����� ����
	wcex.lpfnWndProc	= (WNDPROC)WndProc; //������� ���������
	wcex.cbClsExtra		= 0; //�� ������������ ���������
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //������������� ����������
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WTBBRAIN); //������
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //������
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); //���
	wcex.lpszMenuName	= (LPCSTR)IDC_WTBBRAIN;
	wcex.lpszClassName	= szWindowClass; //��� ������ ����
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //������� �������� ����
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_DLGFRAME /*��� ����, ����� ������� ���� �� ��������*/|WS_SYSMENU|WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //������� ���������
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc; //��������� ���������
	HBRUSH brushBall,oldBrush; //���� �����
	int key; //��� ����������� ������� ����������
	RECT r; //���������, � ������� ����������� ������ ���������� ������� ���������
	switch (message) //�������� ���������
	{
	case WM_CREATE: //��� �������� ����
		GetClientRect(hWnd,&r); //��������� ������� ���������� ������� � ��������� �� � ��������� r
		ball.x=r.right/2-15; //��������� ���������� ����
		ball.y=r.bottom/2-15;
		player.left=r.right/2-40; //��������� ���������� ���������
		player.top=r.bottom-50;
		player.right=player.left+80;
		player.bottom=player.top+20;
		isGameStart=false; //���� ������ ����

		break;
	case WM_KEYUP: //��������� ���������� �������
		key=(int) wParam; //�������� �������
		switch (key) //������� ������
		{
		case 0x53://���� S key
			if (isGameStart==false) //���� ���� �� ������
			{
				GetClientRect(hWnd,&r); //�������� ��������
				ball.x=r.right/2-15; //��������� ���������� ����
				ball.y=r.bottom/2-15;
				player.left=r.right/2-40; //...���������
				player.top=r.bottom-50;
				player.right=player.left+80;
				player.bottom=player.top+20;
				isGameStart=true; //��������� ����� ������ ���� � true
				cx=10; //��������� �������� ���� �� � � �� �
				cy=10;
				if (rand()%2==1)//��������� ��������, ��� 0 ��� 1, ���� 1, ��
				{
					cxVector=-1; //����������� ���� �����
				}
				else
				{
					cxVector=1; //������
				}
				if (rand()%2==1)//��������� �������� ��� ������������� �����������
				{
					cyVector=-1; //�����
				}
				else
				{
					cyVector=1; //����
				}
				SetTimer(hWnd,0,25,NULL); //��������� �������, ������� ����������� ������ 25 ����������
			}
			else //�����, ����� �� ��������� ���������
			{
				GetClientRect(hWnd,&r); //��������� ���������
				ball.x=r.right/2-15; //��������� ��������� ����
				ball.y=r.bottom/2-15;
				player.left=r.right/2-40; //...���������
				player.top=r.bottom-50;
				player.right=player.left+80;
				player.bottom=player.top+20;
				cx=0; //��������� �������� ����
				cy=0;
				isGameStart=false; //��������� ����� ������ ���� � false
				KillTimer(hWnd,0); //�������� �������
				InvalidateRect(hWnd,0,true); //����������� ���������� �������
			}
			break;
		case 0x50://���� P key
			if (isGameStart==true) //���� ���� ������
			{
				KillTimer(hWnd,0); //�������� �������
				isGameStart=false; //��������� ����
			}
			else //�����
			{
				isGameStart=true; //������ ����
				SetTimer(hWnd,0,25,NULL); //��������� �������
			}
			break;
		case VK_UP: //���� ������ ������� "�����"
			if (cx<50) //���� �������� ������ 50
			{
				cx+=5; //��������� �������� �� ��� � � � �� 5
				cy+=5;
			}
			break;
		case VK_DOWN://���� ������ ������� "����"
			if (cx>5) //���� �������� ������ 5
			{
				cx-=5; //��������� �������� �� 5
				cy-=5;
			}
			break;
		}
		break;


		case WM_KEYDOWN: //��������� ������� �������
			key=(int) wParam;
			switch (key)  //�������� �������
			{
			case VK_LEFT: //������� "�����"
				GetClientRect(hWnd,&r); //��������� ���������
				if (player.left>0) //���� ��������� �� � ������� ������ �����
				{
					player.left-=15; //����������� ��������� �����
					player.right-=15;
					InvalidateRect(hWnd,0,true); //����������� ���������� �������
				}
				break;
			case VK_RIGHT: //������� "������"
				GetClientRect(hWnd,&r); //��������� ���������
				if (player.right<r.right) //���� ��������� �� � ������� ������ ������
				{
					player.left+=15; //����������� ��������� ������
					player.right+=15;
					InvalidateRect(hWnd,0,true); //����������� �������
				}
				break;
			}
			break;

			case WM_MOUSEMOVE: //��������� ����������� �������
				{
					SetCursor(LoadCursor(NULL,NULL)); //��������� ������
					GetClientRect(hWnd,&r); //������ ���������� �������
					if((LOWORD(lParam)>r.left) && (LOWORD(lParam)<(r.right-80))) //���� ������ �� ����� ����� ������� ���� � �� ������ ������ �������
					{
					player.left=LOWORD(lParam); //����������� ��������� �� ��� � � ����� �������� ��������� ������� �� �
					player.right=player.left+80;
					InvalidateRect(hWnd,0,true); //����������� �������
					}
				}
				break;


			case WM_TIMER: //�������� �������
				RECT temp, temp2; //��������� ����������
				SetRect(&temp,ball.x,ball.y,ball.x+30,ball.y+30);//������� ����
				GetClientRect(hWnd,&r); //��������� ���������
				if (ball.x<=0 || ball.x+30>r.right) //������������ ���� � ����� ��� ������ ��������� ����
				{
					cxVector*=(-1); //��������� ����������� ���� �� �
				}
				if (ball.y<=0  || IntersectRect(&temp2,&player,&temp)==true) //������������ � ������� �������� ��� ����������
				{
					cyVector*=(-1); //��������� ����������� �� �
				}
				if (IntersectRect(&temp2,&player,&temp)==true) //���������� �� 1 �������� ��� ��������� ���� �� ���������
				{
					st+=1;
					wsprintf ((LPSTR)sc,"%d",st);
				}
				else if (ball.y+60>r.bottom) //���� ��� ���� ���������, ��
				{
					KillTimer(hWnd,0); //�������� �������
					isGameStart=false; //��������� ����
					GetClientRect(hWnd,&r); //��������� ���������
					ball.x=r.right/2-15; //��������� ���������� ����
					ball.y=r.bottom/2-15;
					player.left=r.right/2-40; //...���������
					player.top=r.bottom-50;
					player.right=player.left+80;
					player.bottom=player.top+20;
					cx=10; //�������� ����
					cy=10;
					MessageBox(hWnd,"Try again :)","Game over",MB_OK); //��������� � ���������
				}
				ball.x+=cx*cxVector; //��������� ��������� ���� � ������������ �� �������� � ������������
				ball.y+=cy*cyVector;
				InvalidateRect(hWnd,0,true); //����������� �������
				break;
			case WM_PAINT: //���������� ���������� �������
				hdc = BeginPaint(hWnd, &ps); //������ ����������
				brushBall = CreateSolidBrush(RGB(255,0,0)); //������� �����
				oldBrush = (HBRUSH)SelectObject(hdc,brushBall);//������� �����, ���������� ������ ����� ��������� �������
				Ellipse(hdc,ball.x,ball.y,ball.x+30,ball.y+30); //���������� ���
				Rectangle(hdc,player.left,player.top,player.right,player.bottom); //���������� ���������
				if (isGameStart==false) //���� ���� �����������
				{
					TextOut(hdc,30,130,helpS,strlen(helpS)); //�������� ���������
					TextOut(hdc,30,150,helpP,strlen(helpP));
					TextOut(hdc,30,170,helpSp,strlen(helpSp));
				}
				TextOut(hdc,5,5,scp,strlen(scp));//����� ����� "POINTS"
				TextOut(hdc,5,25,cxs,strlen(cxs));//����� ����� "SPEED"
				TextOut(hdc,65,5,sc,strlen(sc));//����� �������� �������� ��������� �� ���������
				wsprintf ((LPSTR)speed,"%d",cx);
				TextOut(hdc,65,25,speed,strlen(speed));//����� �������� �������� ����
				SelectObject(hdc,oldBrush); //����� � �������� ��������� �����
				DeleteObject(brushBall);
				EndPaint(hWnd, &ps);
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
