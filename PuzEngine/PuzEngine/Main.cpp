/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <stdlib.h>  
#include <crtdbg.h> 
#endif 

#include <windows.h>
#include "PuzApp.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE /*prev*/, LPSTR /*commandLine*/, int /*show*/)
{
  /*This code will help find memory leaks in your code you should add
  this to main.*/
#if defined(DEBUG) | defined(_DEBUG)
  /* This will call _CrtDumpMemoryLeaks() on program exit.*/
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  /*To show memory leaks in the output window */
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

  /* If you have a leak, there is a number in curly braces next to the error.
     Put that number in this function and check the call stack to see when and
     where the allocation happened. Set it to -1 to have it not break.*/
  _CrtSetBreakAlloc(-1);
#endif
	App::Init(instance);
	App::AppUpdate();
	App::Shutdown();

	return 0;
}