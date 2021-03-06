#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK
WindowProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage (0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint (hwnd, &ps);

			FillRect (hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

			EndPaint (hwnd, &ps);
		}
		return 0;
	}

	return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

int WINAPI
wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASS wc;

	const wchar_t CLASS_NAME[] = L"MBTool Window Class";

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass (&wc);

	hwnd = CreateWindowEx (
			0,
			CLASS_NAME,
			L"MBTool",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			(HWND) NULL,
			(HMENU) NULL,
			hInstance,
			NULL);
	if (!hwnd)
	{
		printf ("CreateWindow failed with error: %d\n", GetLastError ());
		return 1;
	}

	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return 0;
}

int
main (int argv, char *argc[])
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	PWSTR pCmdLine;
	int nCmdShow;

	return wWinMain (hInstance, hPrevInstance, pCmdLine, nCmdShow);
}
