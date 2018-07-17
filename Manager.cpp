#include "common.h"

#include "Manager.h"
#include "Utilities.h"

//-------------------------------------------
// A function that represents Manager_Thread
//-------------------------------------------
DWORD WINAPI Manager_Thread( LPVOID lpParam ) 
{
	Utilities Util;
    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;
    
    // Get Handle To screen. Else how will we print?
    if( (hStdout = 
         GetStdHandle(STD_OUTPUT_HANDLE)) == 
         INVALID_HANDLE_VALUE )  
    return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam); 

    for (count = 0; count <= 7; count++ )
    {
		Util.DisplayMessage (hStdout, "Manager_Thread", Data, count);
    }
    
    return 0; 
} 
