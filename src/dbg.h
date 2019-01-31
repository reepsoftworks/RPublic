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

#ifndef DBG_H
#define DBG_H
#if defined( _WIN32 )
#pragma once
#endif

enum SpewType_t
{
	SPEW_MESSAGE = 0,
	SPEW_WARNING,
	SPEW_ERROR,
	SPEW_PASS,
	SPEW_ABORT,

	SPEW_TYPE_COUNT
};

//-----------------------------------------------------------------------------
// Get the last output.
//-----------------------------------------------------------------------------
const char* GetLastSpew();

//-----------------------------------------------------------------------------
// Functions for printing.
//-----------------------------------------------------------------------------
void Msg(char const* pMsg, ...);
void Warning(char const* pMsg, ...);
void Error(char const* pMsg, ...);
void Pass(char const* pMsg, ...);
void Abort(char const* pMsg, ...);

//-----------------------------------------------------------------------------
// Functions for printing that'll only spew if DEBUG is defined.
//-----------------------------------------------------------------------------
void DMsg(char const* pMsg, ...);
void DWarning(char const* pMsg, ...);
void DError(char const* pMsg, ...);
void DPass(char const* pMsg, ...);
void DAbort(char const* pMsg, ...);

#if defined(_MSC_VER)
#define PRINT_HEADER(X,Y) Msg("%s - %s (%s)\n", X, Y, __DATE__)
#else
#define PRINT_HEADER(X,Y) Msg("%s - (%s)\n", X, Y)
#endif

#endif // DBG_H