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
		MemDC=CreateCompatibleDC(hdc); // Memory DC �����(Hdc�� ȣȯ�Ǵ� background dc�����,���۸�)
		MyBitMap = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1)); // bitmap �ҷ�����
		OldBitMap = (HBITMAP)SelectObject(MemDC,MyBitMap); 
			// slect object�� arg2�� gdiHandle�� ���� dc�� handle�� �����ϰ�
			// ������ ���õǾ��ִ� handle�� �����Ѵ�. 
			// select�� handle�� �������ϸ� �ȵǹǷ� ���߿� oldhandle�� ������ myhandle�� ����.
			// (���� handle���� �����س��� �׸� ���� ���� �ڵ�� �����Ҽ��ֱ⶧��)
		//BitBlt(hdc,0,0, 100,100,MemDC,0,0,SRCCOPY); 
		BitBlt(hdc,0,0, 100,100,MemDC,0,0,MERGECOPY); // ����ũ���� �������
		BitBlt(hdc,100,100, 100,200,MemDC,0,0,MERGECOPY); // ���ļ� �� �׸�
		StretchBlt(hdc,300,300,100,300,MemDC,0,0,500,500,MERGECOPY); // ����� ũ�� ���ؼ� �������
			// bitblt�� DC�� ��Ӻ��� ������.
			// hdc, stX,stY,edX,edY
			// hdcSrc(MemDC) : hdc�� �����ϰ����ϴ� back DC
			// MemDc�� �׷����ִ� bitmap�� ������ǥ
			// dwRop(SRCCOPY) : ������, srccopy�� �����״�κ���
			//		SRCCOPY,BLACKNESS,DSTINVERT,MERGECOPY(AND),MERGEPAINT(OR),WHITENESS �����ִ�.
		SelectObject(MemDC, OldBitMap); // MyBitmap������ ���� handle�� old�� �ٽ� �ٲ㼱���Ѵ�.
		DeleteObject(MyBitMap); // MyBitmap�� �����Ѵ�.
		DeleteDC(MemDC); // Back���� �����  MemDC�� �����Ѵ�.

		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}