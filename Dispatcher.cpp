#include "common.h"

#include "Dispatcher.h"
#include "Utilities.h"

//-------------------------------------------
// A function that represents Dispatcher_Thread
//-------------------------------------------
DWORD WINAPI Dispatcher_Thread( LPVOID lpParam ) 
{
	Utilities Util;
    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;
    
    // Get Handle To screen.
    // Else how will we print?
    if( (hStdout = 
         GetStdHandle(STD_OUTPUT_HANDLE)) 
         == INVALID_HANDLE_VALUE )  
    return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam); 

    for (count = 0; count <= 4; count++ )
    {
       Util.DisplayMessage (hStdout, "Dispatcher_Thread", Data, count);
    }
    
    return 0; 
} 
