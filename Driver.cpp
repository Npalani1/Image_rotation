#include "common.h"

#include "Driver.h"
#include "Utilities.h"

//-------------------------------------------
// A function that represents Driver_Thread
//-------------------------------------------
DWORD WINAPI Driver_Thread( LPVOID lpParam ) 
{
	Utilities Util;
    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;

    // Get Handle To screen. Else how will we print?
    if( (hStdout = 
         GetStdHandle(STD_OUTPUT_HANDLE)) 
         == INVALID_HANDLE_VALUE )  
    return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam); 

    for (count = 0; count <= 10; count++ )
    {
		Util.DisplayMessage (hStdout, "Driver_Thread", Data, count);
    }
    
    return 0; 
}

int Driver::ProcessImage( )
{
	Utilities Util;
    int imageWidth = 0;
    int imageHeight = 0;
    unsigned long imageSize = 0;
    unsigned long padding = 0;
     
	BYTE* bytes = NULL;
    // Load the bitmap file, amd put its data part into the BYTE array
   // BYTE* bytes = LoadBMP( &imageWidth, &imageHeight, &imageSize, "C:\\MyStuff\\shaunak.BMP" );
   
   if(Util.LoadBMP( &imageWidth, &imageHeight, &imageSize, "C:\\MyStuff\\shaunak.BMP", bytes )==true)
   {
		Util.Add_Image_To_ImageQueue((char*)bytes);
		std::reverse( bytes, bytes + imageSize );
 
		// Determine amount of padding required, if any, and create a new BYTE array from this
		std::unique_ptr<BYTE[]> newbuf2 = Util.CreateNewBuffer( padding, bytes, imageWidth, imageHeight );
     
		// Use the new array data to create the new bitmap file
		Util.SaveBitmapToFile( (BYTE*) &newbuf2[ 0 ],  
                      imageWidth,  
                      imageHeight,  
                      24,  
                      padding,
                      "C:\\MyStuff\\new_image.bmp" );  
	}
	else
	{
		printf("Load BMP Failed\n");
	}

    return 0;
}
