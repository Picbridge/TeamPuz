/******************************************************************************/
/*!
file    Debug.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Debugging tools
\date   2014/10/21

   Debugging tools.
*/
/******************************************************************************/
#include "Debug.h"

/*Use a large message because we are crashing anyway*/
#define MAX_MESSAGE 1024 /*!< The max Assert message size*/
#define MAX_LINE 10 /*!< The Max line number size*/

/******************************************************************************/
/*!
This function is used to force a crash if a certain condition isn't met.
This will only work in DEBUG mode. In Release mode the code is removed.

\param express 
The expression to test. If it is false the program will crash.

\param outputMsg
The message to tell the user.

\param functionName
The name of the function that the Assert was located in.

\param fileName
The name of the file that the Assert was located in.

\param lineNumber 
The line number of the Assert.

\return
TRUE if the expression was false and the user clicks yes. False if the 
expression is true.
*/
/******************************************************************************/
bool DebugFunctions::DebugAssert(bool express, const char* outputMsg,
	const char* functionName,const char* fileName, unsigned lineNumber)
{
	if(!express)
	{
		int returnValue;
		char message[MAX_MESSAGE] = {0}; /* The message to print */
		wchar_t wMessage[MAX_MESSAGE] = {0}; /* To change char* to LPCWSTR */
		char lineString[MAX_LINE] = {0}; /* To convert the line to a string */

		/* Convert the line number to a string */
		sprintf_s(lineString, MAX_LINE, "%d", lineNumber);

		/* Set output message */
		strcat_s(message, MAX_MESSAGE, "ASSERTION FAILURE:");
		strcat_s(message, MAX_MESSAGE, "\nFile: ");
		strcat_s(message, MAX_MESSAGE, fileName);
		strcat_s(message, MAX_MESSAGE, "\nLine: ");
		strcat_s(message, MAX_MESSAGE, lineString);
		strcat_s(message, MAX_MESSAGE, "\nFunction: ");
		strcat_s(message, MAX_MESSAGE, functionName);
		strcat_s(message, MAX_MESSAGE, "\n\n Description: ");
		strcat_s(message, MAX_MESSAGE, outputMsg);
		strcat_s(message, MAX_MESSAGE, "\n\nYES: Break into the Debugger.");
		strcat_s(message, MAX_MESSAGE, "\nNO: Exit immediately");

		/* casting char* to LPCWSTR */
		mbstowcs(wMessage, message, MAX_MESSAGE);

		/* display a message to the user */
		returnValue = MessageBox(NULL, wMessage, L"ASSERT!", MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR); 

		if (returnValue == IDYES)
		{
			return true;
		}
		ExitProcess((unsigned)(-1));
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Create debugging window

\return
None.
*/
/******************************************************************************/
void DebugFunctions::DebugCreateConsole(void)
{
	FILE* pFile;
	AllocConsole();

	freopen_s(&pFile, "CONOUT$", "wt", stdout);
	freopen_s(&pFile, "CONOUT$", "wt", stderr);
	SetConsoleTitle(L"Debug Console");
}

/******************************************************************************/
/*!
\brief
Destroy debugging window

\return
None.
*/
/******************************************************************************/
void DebugFunctions::DebugDestroyConsole(void)
{
	FreeConsole();
}