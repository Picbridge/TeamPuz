#ifndef DEBUGE_H
#define DEBUGE_H

/******************************************************************************/
/*!
file    Debug.h
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Debugging tools
\date   2014/10/21

   Debugging tool functions.
*/
/******************************************************************************/
#include <windows.h>
#include <cstdio>
#include <cstring>

class DebugFunctions
{
public:
	static bool DebugAssert(bool express, const char* outputMsg,
		 const char* functionName,const char* fileName, unsigned lineNumber);
	static void DebugCreateConsole(void);
	static void DebugDestroyConsole(void);
};

#if defined(DEBUG) | defined(_DEBUG)
#include <cstdio>
/*! Use this macro instead of the function to print to the console in debug 
only*/
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
/*! Use this macro instead of the function to clear the console in debug only*/
#define DEBUG_CLEAR() system("cls")
/*! Use this macro instead of the function to ASSERT in debug only*/
#define DEBUG_ASSERT(exp, str) if(DebugFunctions::DebugAssert((exp),(str),      \
  __FUNCTION__,__FILE__, __LINE__))     \
{DebugBreak();} 
/*!Use this macro instead of the function to create a console in debug only*/
#define DEBUG_CREATE_CONSOLE() DebugFunctions::DebugCreateConsole();
/*!Use this macro instead of the function to destroy a console in debug only*/
#define DEBUG_DESTROY_CONSOLE() DebugFunctions::DebugDestroyConsole();
/*! Use this macro to draw debug text on the screen*/
#define DEBUG_DRAW_TEXT(text, tranform)    \
  GraphicsDrawText((text),(transform))
#else
/*! Use this macro instead of the function to print to the console in debug 
only*/
#define DEBUG_PRINT(...)
/*! Use this macro instead of the function to clear the console in debug only*/
#define DEBUG_CLEAR()
/*! Use this macro instead of the function to ASSERT in debug only*/
#define DEBUG_ASSERT(expression, outputMessage)
/*!Use this macro instead of the function to create a console in debug only*/
#define DEBUG_CREATE_CONSOLE()
/*!Use this macro instead of the function to destroy a console in debug only*/
#define DEBUG_DESTROY_CONSOLE()
/*! Use this macro to draw debug text on the screen*/
#define DEBUG_DRAW_TEXT(text, tranform) 
#endif


#endif /* DEBUG_H */