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
POINT ball; //структура мяча
RECT player; //структура платформы
int st=0; //счетчик попаданий по платформе
char sc[5];//строка счетчика для вывода на экран
char speed[2];//строка скорости игры для вывода на экран
bool isGameStart; //флаг процесса игры
int cx,cy; //скорость мяча по х и по у
int cxVector,cyVector; //направление мяча по х и по у
char scp[]="Points  ";//строка перед значением кол-ва попаданий мяча
char cxs[]="Speed= ";//строка перед значением скорости
char helpS[]="S – start/stop game";  //подсказки и горячие клавиши управления
char helpP[]="P – pause game";
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
	while (GetMessage(&msg, NULL, 0, 0)) //цикл обработки сообщений
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance) //регистрация класса главного окна
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW; //стиль окна
	wcex.lpfnWndProc	= (WNDPROC)WndProc; //оконная процедура
	wcex.cbClsExtra		= 0; //не используемые параметры
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //идентификатор приложения
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WTBBRAIN); //иконка
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); //курсор
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); //фон
	wcex.lpszMenuName	= (LPCSTR)IDC_WTBBRAIN;
	wcex.lpszClassName	= szWindowClass; //имя класса окна
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //функция создания окна
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_DLGFRAME /*для того, чтобы размеры окна не менялись*/|WS_SYSMENU|WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //оконная процедура
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc; //структура контекста
	HBRUSH brushBall,oldBrush; //цвет кисти
	int key; //для определения клавиши клавиатуры
	RECT r; //структура, в которой содержиться размер клиентской области программы
	switch (message) //проверка сообщения
	{
	case WM_CREATE: //при создании окна
		GetClientRect(hWnd,&r); //получение размера клиентской области и занесение ее в структуру r
		ball.x=r.right/2-15; //начальные координаты мяча
		ball.y=r.bottom/2-15;
		player.left=r.right/2-40; //начальные координаты платформы
		player.top=r.bottom-50;
		player.right=player.left+80;
		player.bottom=player.top+20;
		isGameStart=false; //флаг начала игры

		break;
	case WM_KEYUP: //сообщения отпускания клавиши
		key=(int) wParam; //проверка клавиши
		switch (key) //перебор клавиш
		{
		case 0x53://если S key
			if (isGameStart==false) //если игра не начата
			{
				GetClientRect(hWnd,&r); //получаем контекст
				ball.x=r.right/2-15; //начальные координаты мяча
				ball.y=r.bottom/2-15;
				player.left=r.right/2-40; //...платформы
				player.top=r.bottom-50;
				player.right=player.left+80;
				player.bottom=player.top+20;
				isGameStart=true; //установка флага начала игры в true
				cx=10; //начальная скорость мяча по х и по у
				cy=10;
				if (rand()%2==1)//случайное значение, или 0 или 1, если 1, то
				{
					cxVector=-1; //направление мяча влево
				}
				else
				{
					cxVector=1; //вправо
				}
				if (rand()%2==1)//случайное значение для вертикального направления
				{
					cyVector=-1; //вверх
				}
				else
				{
					cyVector=1; //вниз
				}
				SetTimer(hWnd,0,25,NULL); //установка таймера, который срабатывает каждые 25 милисекунд
			}
			else //иначе, сброс на начальное положение
			{
				GetClientRect(hWnd,&r); //получение контекста
				ball.x=r.right/2-15; //начальное положение мяча
				ball.y=r.bottom/2-15;
				player.left=r.right/2-40; //...платформы
				player.top=r.bottom-50;
				player.right=player.left+80;
				player.bottom=player.top+20;
				cx=0; //начальная скорость мяча
				cy=0;
				isGameStart=false; //установка флага начала игры в false
				KillTimer(hWnd,0); //удаление таймера
				InvalidateRect(hWnd,0,true); //перерисовка клиентской области
			}
			break;
		case 0x50://если P key
			if (isGameStart==true) //если игра начата
			{
				KillTimer(hWnd,0); //удаление таймера
				isGameStart=false; //остановка игры
			}
			else //иначе
			{
				isGameStart=true; //начало игры
				SetTimer(hWnd,0,25,NULL); //установка таймера
			}
			break;
		case VK_UP: //если нажата клавиша "ВВЕРХ"
			if (cx<50) //если скорость меньше 50
			{
				cx+=5; //увеличить скорость по оси Х и У на 5
				cy+=5;
			}
			break;
		case VK_DOWN://если нажата клавиша "ВНИЗ"
			if (cx>5) //если скорость больше 5
			{
				cx-=5; //уменьшить скорость на 5
				cy-=5;
			}
			break;
		}
		break;


		case WM_KEYDOWN: //сообщение нажатия клавиши
			key=(int) wParam;
			switch (key)  //проверка клавиши
			{
			case VK_LEFT: //клавиша "ВЛЕВО"
				GetClientRect(hWnd,&r); //получение контекста
				if (player.left>0) //если платформа не у границы экрана слева
				{
					player.left-=15; //перемещение платформы влево
					player.right-=15;
					InvalidateRect(hWnd,0,true); //перерисовка клиентской области
				}
				break;
			case VK_RIGHT: //клавиша "ВПРАВО"
				GetClientRect(hWnd,&r); //получение контекста
				if (player.right<r.right) //если платформа не у границы экрана справа
				{
					player.left+=15; //перемещение платформы вправо
					player.right+=15;
					InvalidateRect(hWnd,0,true); //перерисовка области
				}
				break;
			}
			break;

			case WM_MOUSEMOVE: //сообщение перемещения курсора
				{
					SetCursor(LoadCursor(NULL,NULL)); //невидимый курсор
					GetClientRect(hWnd,&r); //размер клиентской области
					if((LOWORD(lParam)>r.left) && (LOWORD(lParam)<(r.right-80))) //если курсор не левее левой границы окна и не правее правой границы
					{
					player.left=LOWORD(lParam); //перемещение платформы по оси Х в точку текущего положения курсора по Х
					player.right=player.left+80;
					InvalidateRect(hWnd,0,true); //перерисовка области
					}
				}
				break;


			case WM_TIMER: //ообщения таймера
				RECT temp, temp2; //временные переменные
				SetRect(&temp,ball.x,ball.y,ball.x+30,ball.y+30);//границы мяча
				GetClientRect(hWnd,&r); //получение контекста
				if (ball.x<=0 || ball.x+30>r.right) //столкновение мяча с левой или правой границами окна
				{
					cxVector*=(-1); //изменение направления мяча по Х
				}
				if (ball.y<=0  || IntersectRect(&temp2,&player,&temp)==true) //столкновение с верхней границей или платформой
				{
					cyVector*=(-1); //изменение направления по У
				}
				if (IntersectRect(&temp2,&player,&temp)==true) //увеличение на 1 счетчика при попадании мяча на платформу
				{
					st+=1;
					wsprintf ((LPSTR)sc,"%d",st);
				}
				else if (ball.y+60>r.bottom) //если мяч ниже платформы, то
				{
					KillTimer(hWnd,0); //удаление таймера
					isGameStart=false; //остановка игры
					GetClientRect(hWnd,&r); //получение контекста
					ball.x=r.right/2-15; //начальные координаты мяча
					ball.y=r.bottom/2-15;
					player.left=r.right/2-40; //...платформы
					player.top=r.bottom-50;
					player.right=player.left+80;
					player.bottom=player.top+20;
					cx=10; //скорость мяча
					cy=10;
					MessageBox(hWnd,"Try again :)","Game over",MB_OK); //сообщение о проигрыше
				}
				ball.x+=cx*cxVector; //изменение координат мяча в соответствии со скростью и направлением
				ball.y+=cy*cyVector;
				InvalidateRect(hWnd,0,true); //перерисовка области
				break;
			case WM_PAINT: //прорисовка клиентской области
				hdc = BeginPaint(hWnd, &ps); //начать прорисовку
				brushBall = CreateSolidBrush(RGB(255,0,0)); //создать кисть
				oldBrush = (HBRUSH)SelectObject(hdc,brushBall);//выбрать кисть, дальнейшие фигуры будут закрашены красным
				Ellipse(hdc,ball.x,ball.y,ball.x+30,ball.y+30); //нарисовать мяч
				Rectangle(hdc,player.left,player.top,player.right,player.bottom); //нарисовать платформу
				if (isGameStart==false) //если игра остановлена
				{
					TextOut(hdc,30,130,helpS,strlen(helpS)); //показать подсказки
					TextOut(hdc,30,150,helpP,strlen(helpP));
					TextOut(hdc,30,170,helpSp,strlen(helpSp));
				}
				TextOut(hdc,5,5,scp,strlen(scp));//вывод слова "POINTS"
				TextOut(hdc,5,25,cxs,strlen(cxs));//вывод слова "SPEED"
				TextOut(hdc,65,5,sc,strlen(sc));//вывод значения счетчика попаданий по платформе
				wsprintf ((LPSTR)speed,"%d",cx);
				TextOut(hdc,65,25,speed,strlen(speed));//вывод значения скорости мяча
				SelectObject(hdc,oldBrush); //выбор и удаление созданной кисти
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
