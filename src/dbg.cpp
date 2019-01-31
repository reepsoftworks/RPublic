/*
MIT License

Copyright (c) 2019 Reep Softworks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include "platform.h"
#include "macros.h"
#include "dbg.h"

#define CLR_NORMAL		0
#define CLR_RED			1
#define CLR_RED_I		2
#define CLR_GREEN		3
#define CLR_GREEN_I		4
#define CLR_YELLOW		5
#define CLR_YELLOW_I	6
#define CLR_BLUE		7
#define CLR_NAGENTA		8
#define CLR_NAGENTA_I	9
#define CLR_CYAN		10
#define CLR_CYAN_I 		11
#define CLR_WHITE		12
#define CLR_RESET 		CLR_NORMAL

/*
#define CLR_NORMAL   "\x1B[0m"
#define CLR_RED      "\x1B[31m"
#define CLR_RED_I     "\033[0;31m"
#define CLR_GREEN    "\x1B[32m"
#define CLR_GREEN_I  "\033[1;32m"
#define CLR_YELLOW   "\x1B[33m"
#define CLR_YELLOW_I  "\033[1;33m"
#define CLR_BLUE     "\x1B[34m"
#define CLR_NAGENTA  "\x1B[35m"
#define CLR_NAGENTA_I "\033[0;35m"
#define CLR_CYAN     "\x1B[36m"
#define CLR_CYAN_I 	 "\033[0;36m"
#define CLR_WHITE    "\x1B[37m"
#define CLR_RESET 	 "\033[0m"
*/

#if defined (SYSTEM_WINDOWS)
#include <ShlObj.h>
#include <direct.h>
WORD GetConsoleTextAttribute(HANDLE hCon)
{
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}
#endif

//-----------------------------------------------------------------------------
// Purpose: Place the varible infront of the message to make the message a 
//			diffrent color. This method seems to be the simplist way to 
//			colored text on multiplat cleanly.
//-----------------------------------------------------------------------------
void SetTextColor(const int rMode)
{
#if defined (SYSTEM_WINDOWS)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (rMode)
	{
	case CLR_NORMAL:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;

	case CLR_RED:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		break;

	case CLR_RED_I:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;

	case CLR_GREEN:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		break;

	case CLR_GREEN_I:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;

	case CLR_CYAN:
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE /*| FOREGROUND_INTENSITY*/);
		break;

	case CLR_CYAN_I:
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE );
		break;

	case CLR_YELLOW:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		break;

	case CLR_YELLOW_I:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;

	case CLR_NAGENTA:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
		break;

	case CLR_NAGENTA_I:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	}
#else
	switch (rMode)
	{
	case CLR_NORMAL:
		printf("\x1B[0m");
		break;

	case CLR_RED:
		printf("\x1B[31m");
		break;

	case CLR_RED_I:
		printf("\033[0;31m");
		break;

	case CLR_GREEN:
		printf("\x1B[32m");
		break;

	case CLR_GREEN_I:
		printf("\033[1;32m");
		break;

	case CLR_CYAN:
		printf("\x1B[36m");
		break;

	case CLR_CYAN_I:
		printf("\033[0;36m");
		break;

	case CLR_YELLOW:
		printf("\x1B[33m");
		break;

	case CLR_YELLOW_I:
		printf("\033[1;33m");
		break;

	case CLR_NAGENTA:
		printf("\x1B[35m");
		break;

	case CLR_NAGENTA_I:
		printf("\033[0;35m");
		break;
	}
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Get the last output. Useful for external loggers.
//-----------------------------------------------------------------------------
const char* lastspew;
const char* GetLastSpew()
{
	return lastspew;
}

//-----------------------------------------------------------------------------
// Purpose: Set the color, print the message, and reset the console color.
//-----------------------------------------------------------------------------
void clr_out(const char* pStr, const int clr)
{
	SetTextColor(clr);
	printf(pStr);
	SetTextColor(CLR_RESET);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void SpewMessage(SpewType_t type, char const* pMsgFormat, va_list args)
{
	char pTempBuffer[1024];
	R_vsprintf(pTempBuffer, pMsgFormat, args);
	lastspew = pTempBuffer;

	switch (type)
	{
	case SPEW_MESSAGE:
		clr_out(GetLastSpew(), CLR_NORMAL);
		break;

	case SPEW_WARNING:
		clr_out(GetLastSpew(), CLR_YELLOW_I);
		break;

	case SPEW_ERROR:
		clr_out(GetLastSpew(), CLR_RED_I);
		break;

	case SPEW_PASS:
		clr_out(GetLastSpew(), CLR_GREEN_I);
		break;

	case SPEW_ABORT:
		clr_out(GetLastSpew(), CLR_RED_I);
		exit(0);
		break;

	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window.
//-----------------------------------------------------------------------------
void Msg(char const* pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_MESSAGE, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in yellow.
//-----------------------------------------------------------------------------
void Warning(char const* pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_WARNING, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in red.
//-----------------------------------------------------------------------------
void Error(char const* pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_ERROR, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in green.
//-----------------------------------------------------------------------------
void Pass(char const* pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_PASS, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in red and terminate.
//-----------------------------------------------------------------------------
void Abort(char const* pMsgFormat, ...)
{
	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_ABORT, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window. (Debug only)
//-----------------------------------------------------------------------------
void DMsg(char const* pMsgFormat, ...)
{
	if (IsDebug() == false)
		return;

	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_MESSAGE, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in yellow. (Debug only)
//-----------------------------------------------------------------------------
void DWarning(char const* pMsgFormat, ...)
{
	if (IsDebug() == false)
		return;

	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_WARNING, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in red. (Debug only)
//-----------------------------------------------------------------------------
void DError(char const* pMsgFormat, ...)
{
	if (IsDebug() == false)
		return;

	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_ERROR, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in green. (Debug only)
//-----------------------------------------------------------------------------
void DPass(char const* pMsgFormat, ...)
{
	if (IsDebug() == false)
		return;

	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_PASS, pMsgFormat, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
// Purpose: Print to the console window in red and terminate. (Debug only)
//-----------------------------------------------------------------------------
void DAbort(char const* pMsgFormat, ...)
{
	if (IsDebug() == false)
		return;

	va_list args;
	va_start(args, pMsgFormat);
	SpewMessage(SPEW_ABORT, pMsgFormat, args);
	va_end(args);
}