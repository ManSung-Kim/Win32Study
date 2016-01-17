/*
	win 32 study. mansung kim
	jactlab@gmail.com
	github.com/mantdu
*/
#include <Windows.h>

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

#define EDIT_1 0x0e

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc; // dc handle
	PAINTSTRUCT ps; // dc paint
	//static char str[256];
	//static LPWSTR str;
	//static TCHAR str[256];
	//int len;
	static HWND hEdit1;
	static TCHAR str[128];

	switch(iMessage) {
	case WM_CREATE: // 이곳에 BN_CLICKED 날라옴
		hEdit1 = CreateWindow( // checkbox handle을 hChk1에 저장
			TEXT("edit"), // class name
			TEXT(""), // btn label
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL  | ES_AUTOVSCROLL, 
			20,20,100,25, // x,y,w,h
			hWnd, // parent window
			(HMENU)EDIT_1, // chkbox id
			g_hInst,
			NULL
			);		
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) { // wParam의 word low에 id날라옴
			//case menu1_id: /*do*/ break;
			//case menu2_id: /*do*/ break;
			//case accel_id: /*do*/ break;
			case EDIT_1:
				switch(HIWORD(wParam)) {
				case EN_CHANGE:
					GetWindowText(hEdit1,str,128);
					//MessageBox(hWnd,str,TEXT("Button"),MB_OK);
					SetWindowText(hWnd,str);
					break;
				}
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