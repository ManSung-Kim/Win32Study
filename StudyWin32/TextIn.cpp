/*
	win 32 study. mansung kim
	jactlab@gmail.com
	github.com/mantdu
*/
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM, LPARAM);
HINSTANCE g_hInst;

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

	while(GetMessage(&Message,0,0,0) ) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc; // dc handle
	PAINTSTRUCT ps; // dc paint
	//static char str[256];
	//static LPCTSTR str;
	static TCHAR str[256];
	int len;
	switch(iMessage) {
	case WM_CHAR:
		/*len = lstrlen(str);
		str[len] = TCHAR(wParam);
		str[len+1]=0;
		InvalidateRect(hWnd,NULL,FALSE);*/
		{
			
			HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL,NULL,NULL);
			HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
			int x = GetDeviceCaps(hScreenDC, HORZRES);
			int y = GetDeviceCaps(hScreenDC, VERTRES);
			HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC,x,y);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
			BitBlt(hMemoryDC, 0, 0, x,y, hScreenDC, 0,0, SRCCOPY);

			//hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

			//wprintf("%d %d\n",x,y);
			//			
			hdc=BeginPaint(hWnd,&ps);
			BitBlt(hdc, 0, 0, x,y, hMemoryDC, 0,0, SRCCOPY);
			DeleteDC(hdc);
			EndPaint(hWnd,&ps);

			hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

			DeleteDC(hMemoryDC);
			DeleteDC(hScreenDC);

			

		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,str,lstrlen(str));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}