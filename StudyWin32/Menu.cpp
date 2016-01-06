/*
	win 32 study. mansung kim
	jactlab@gmail.com
	github.com/mantdu
*/
#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;

LPCTSTR lpszClass=TEXT("Key");
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	,LPSTR lpszCmdParam, int nCmdShow) 
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL, IDC_ARROW);
	//WndClass.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIcon=LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1)); // icon resource add
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // menu resource add
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while(GetMessage(&Message,0,0,0) ) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc; // dc handle
	PAINTSTRUCT ps; // dc paint
	//static char str[256];
	//static LPCTSTR str;
	//static TCHAR str[256];
	//int len;
	switch(iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) { // wParam의 low word에 resource id값이 날라온다.
		case ID_FILE_MENU1:
			MessageBox(hWnd,TEXT("Menu 1"),TEXT("Menu1 Caption"),MB_OK);
			break;
		case ID_FILE_MENU2:
			MessageBox(hWnd,TEXT("Menu 1"),TEXT("Menu1 Caption"),MB_OK);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;		
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}