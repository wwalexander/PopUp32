// PopUp32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	HWND consoleWindow = GetConsoleWindow();

	if (consoleWindow == NULL) {
		return 1;
	}

	HWND foregroundWindow;

	while (1) {
		foregroundWindow = GetForegroundWindow();

		if (foregroundWindow != NULL && foregroundWindow != consoleWindow) {
			break;
		}

		Sleep(0);
	}

	RECT foregroundWindowRect;

	if (GetWindowRect(
		foregroundWindow,
		&foregroundWindowRect
	) == FALSE) {
		return 1;
	}

	LONG_PTR foregroundWindowStyle = GetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE
	);

	LONG_PTR foregroundWindowStyleFullScreen = foregroundWindowStyle;
	foregroundWindowStyleFullScreen &= ~WS_OVERLAPPEDWINDOW;
	foregroundWindowStyleFullScreen |= WS_POPUP;

	SetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE,
		foregroundWindowStyleFullScreen
	);

	UINT dpi = GetDpiForWindow(foregroundWindow);
	RECT foregroundWindowClientRect;
	foregroundWindowClientRect.left = foregroundWindowRect.left;
	foregroundWindowClientRect.top = foregroundWindowRect.top;
	foregroundWindowClientRect.right = foregroundWindowRect.right;
	foregroundWindowClientRect.bottom = foregroundWindowRect.bottom;
	BOOL bMenu = GetMenu(foregroundWindow) != NULL;

	if (AdjustWindowRect(
		&foregroundWindowClientRect,
		(DWORD)foregroundWindowStyleFullScreen,
		bMenu
	) == FALSE) {
		return 1;
	}

	int nWidth = foregroundWindowClientRect.right - foregroundWindowClientRect.left;
	int nHeight = foregroundWindowClientRect.bottom - foregroundWindowClientRect.top;

	if (MoveWindow(
		foregroundWindow,
		foregroundWindowClientRect.left,
		foregroundWindowClientRect.top,
		nWidth,
		nHeight,
		TRUE
	) == FALSE) {
		return 1;
	}


	HWND newForegroundWindow;

	while (1) {
		newForegroundWindow = GetForegroundWindow();

		if (newForegroundWindow != NULL && newForegroundWindow == consoleWindow) {
			break;
		}

		Sleep(0);
	}

	SetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE,
		foregroundWindowStyle
	);

	nWidth = foregroundWindowRect.right - foregroundWindowRect.left;
	nHeight = foregroundWindowRect.bottom - foregroundWindowRect.top;

	if (MoveWindow(
		foregroundWindow,
		foregroundWindowRect.left,
		foregroundWindowRect.top,
		nWidth,
		nHeight,
		TRUE
	) == FALSE) {
		return 1;
	}

	return 0;
}
