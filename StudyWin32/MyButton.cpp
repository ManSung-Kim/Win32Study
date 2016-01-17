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

#define BTN_1 0x0E
#define BTN_2 0x0F

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	HDC hdc; // dc handle
	PAINTSTRUCT ps; // dc paint
	//static char str[256];
	//static LPCTSTR str;
	//static TCHAR str[256];
	//int len;
	switch(iMessage) {
	case WM_CREATE: // 이곳에 BN_CLICKED 날라옴
		CreateWindow( 
			TEXT("button"), // class name
			TEXT("Hello"), // btn label
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // pushbtn으로 사용함을 알림
			20,20,100,25, // x,y,w,h
			hWnd, // parent window
			(HMENU)BTN_1, // btn id
			g_hInst,
			NULL
			);
		CreateWindow( 
			TEXT("button"), // class name
			TEXT("World"), // btn label
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // pushbtn으로 사용함을 알림
			20,50,100,25, // x,y,w,h
			hWnd, // parent window
			(HMENU)BTN_2, // btn id
			g_hInst,
			NULL
			);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) { // wParam의 word low에 id날라옴
			//case menu1_id: /*do*/ break;
			//case menu2_id: /*do*/ break;
			//case accel_id: /*do*/ break;
			case BTN_1:
				switch(HIWORD(wParam)) {
				case BN_CLICKED: // push 
					MessageBox(hWnd,TEXT("Hello"),TEXT("Button"),MB_OK);
					break;
				}
				break;
			case BTN_2:
				switch(HIWORD(wParam)) {
				case BN_CLICKED: // push
					MessageBox(hWnd,TEXT("World"),TEXT("Button"),MB_OK);
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