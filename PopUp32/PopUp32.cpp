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

	LONG_PTR foregroundWindowStyle = GetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE
	);

	LONG_PTR nForegroundWindowStyle = (foregroundWindowStyle & (~WS_OVERLAPPEDWINDOW)) | WS_POPUP;

	SetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE,
		nForegroundWindowStyle
	);

	HWND nForegroundWindow;

	while (1) {
		nForegroundWindow = GetForegroundWindow();

		if (nForegroundWindow != NULL && nForegroundWindow == consoleWindow) {
			break;
		}

		Sleep(0);
	}

	SetWindowLongPtr(
		foregroundWindow,
		GWL_STYLE,
		foregroundWindowStyle
	);

	return 0;
}
