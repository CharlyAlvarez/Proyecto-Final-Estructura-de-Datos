/*
 * graficos.h
 *
 *  Created on: 08/05/2015
 *      Author: JUAN CARLOS
 */

#ifndef GRAFICOS_H_

#include <windows.h>

#define GRAFICOS_H_

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15


int gotoxy(int x, int y) {
	COORD scrn;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x;
	scrn.Y = y;
	SetConsoleCursorPosition(hOutput, scrn);
	return 0;
}

int textcolor(WORD wColor) {
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hHandle, wColor);
	return 0;
}

boolean keyHit() {
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD saveMode;
	GetConsoleMode(stdIn, &saveMode);
	SetConsoleMode(stdIn, ENABLE_PROCESSED_INPUT);
	boolean ret = FALSE;
	if (WaitForSingleObject(stdIn, 1) == WAIT_OBJECT_0)
		ret = TRUE;
	SetConsoleMode(stdIn, saveMode);
	return (ret);
}

#endif /* GRAFICOS_H_ */
