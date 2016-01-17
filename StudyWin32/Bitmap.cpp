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
	WndClass.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
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

	HDC MemDC;
	HBITMAP MyBitMap, OldBitMap;

	switch(iMessage) {
	case WM_CREATE:
		return 0;
	case WM_PAINT:

		hdc=BeginPaint(hWnd,&ps);
		MemDC=CreateCompatibleDC(hdc); // Memory DC 만들기(Hdc에 호환되는 background dc만들기,버퍼링)
		MyBitMap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1)); // bitmap 불러오기
		OldBitMap = (HBITMAP)SelectObject(MemDC,MyBitMap); 
			// slect object는 arg2의 gdiHandle을 현재 dc의 handle로 선택하고
			// 이전에 선택되어있던 handle을 리턴한다. 
			// select된 handle은 삭제를하면 안되므로 나중에 oldhandle로 복귀후 myhandle을 삭제.
			// (이전 handle값을 저장해놔야 그린 이후 이전 핸들로 복귀할수있기때문)
		//BitBlt(hdc,0,0, 100,100,MemDC,0,0,SRCCOPY); 
		BitBlt(hdc,0,0, 100,100,MemDC,0,0,MERGECOPY); // 원본크기대로 복사수행
		BitBlt(hdc,100,100, 100,200,MemDC,0,0,MERGECOPY); // 겹쳐서 또 그림
		StretchBlt(hdc,300,300,100,300,MemDC,0,0,500,500,MERGECOPY); // 복사될 크기 정해서 복사수행
			// bitblt는 DC간 고속복사 수행함.
			// hdc, stX,stY,edX,edY
			// hdcSrc(MemDC) : hdc로 복사하고자하는 back DC
			// MemDc에 그려져있는 bitmap의 시작좌표
			// dwRop(SRCCOPY) : 복사모드, srccopy는 원본그대로복사
			//		SRCCOPY,BLACKNESS,DSTINVERT,MERGECOPY(AND),MERGEPAINT(OR),WHITENESS 등이있다.
		SelectObject(MemDC, OldBitMap); // MyBitmap삭제를 위해 handle을 old로 다시 바꿔선택한다.
		DeleteObject(MyBitMap); // MyBitmap을 삭제한다.
		DeleteDC(MemDC); // Back에서 사용한  MemDC는 삭제한다.

		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}