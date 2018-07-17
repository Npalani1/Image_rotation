#include "common.h"

#include "Utilities.h"

//------------------------------------------
// A function to Display the message
// indicating in which tread we are
//------------------------------------------
void Utilities::DisplayMessage (HANDLE hScreen, 
     char *ThreadName, int Data, int Count)
{

    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    // Print message using thread-safe functions.
    StringCchPrintf(msgBuf, BUF_SIZE, 
       TEXT("Executing iteration %02d of %s" 
       " having data = %02d \n"), 
       Count, ThreadName, Data); 
    StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
    WriteConsole(hScreen, msgBuf, cchStringSize, 
                 &dwChars, NULL);
    Sleep(1000);
}

// Save the bitmap to a bmp file  
void Utilities::SaveBitmapToFile( BYTE* pBitmapBits,  
                       LONG lWidth,  
                       LONG lHeight,  
                       WORD wBitsPerPixel, 
                       const unsigned long& padding_size,
                       LPCTSTR lpszFileName )  
{  
    // Some basic bitmap parameters  
    unsigned long headers_size = sizeof( BITMAPFILEHEADER ) +  
                                 sizeof( BITMAPINFOHEADER );  
 
    unsigned long pixel_data_size = lHeight * ( ( lWidth * ( wBitsPerPixel / 8 ) ) + padding_size );  
       
    BITMAPINFOHEADER bmpInfoHeader = {0};  
       
    // Set the size  
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);  
       
    // Bit count  
    bmpInfoHeader.biBitCount = wBitsPerPixel;  
       
    // Use all colors  
    bmpInfoHeader.biClrImportant = 0;  
       
    // Use as many colors according to bits per pixel  
    bmpInfoHeader.biClrUsed = 0;  
       
    // Store as un Compressed  
    bmpInfoHeader.biCompression = BI_RGB;  
       
    // Set the height in pixels  
    bmpInfoHeader.biHeight = lHeight;  
       
    // Width of the Image in pixels  
    bmpInfoHeader.biWidth = lWidth;  
       
    // Default number of planes  
    bmpInfoHeader.biPlanes = 1;  
       
    // Calculate the image size in bytes  
    bmpInfoHeader.biSizeImage = pixel_data_size;  
       
    BITMAPFILEHEADER bfh = {0};  
       
    // This value should be values of BM letters i.e 0x4D42  
    // 0x4D = M 0×42 = B storing in reverse order to match with endian  
    bfh.bfType = 0x4D42;  
    //bfh.bfType = 'B'+('M' << 8); 
     
    // <<8 used to shift ‘M’ to end  */  
       
    // Offset to the RGBQUAD  
    bfh.bfOffBits = headers_size;  
       
    // Total size of image including size of headers  
    bfh.bfSize =  headers_size + pixel_data_size;  
       
    // Create the file in disk to write  
    HANDLE hFile = CreateFile( lpszFileName,  
                                GENERIC_WRITE,  
                                0,  
                                NULL,  
                                CREATE_ALWAYS,  
                                FILE_ATTRIBUTE_NORMAL,  
                                NULL );  
       
    // Return if error opening file  
    if( !hFile ) return;  
       
    DWORD dwWritten = 0;  
       
    // Write the File header  
    WriteFile( hFile,  
                &bfh,  
                sizeof(bfh),  
                &dwWritten ,  
                NULL );  
       
    // Write the bitmap info header  
    WriteFile( hFile,  
                &bmpInfoHeader,  
                sizeof(bmpInfoHeader),  
                &dwWritten,  
                NULL );  
       
    // Write the RGB Data  
    WriteFile( hFile,  
                pBitmapBits,  
                bmpInfoHeader.biSizeImage,  
                &dwWritten,  
                NULL );  
       
    // Close the file handle  
    CloseHandle( hFile );  
}  
 
bool Utilities::LoadBMP ( int* width, 
						  int* height, 
						  unsigned long* size, 
						  LPCTSTR bmpfile, 
						  BYTE* Buffer)
{
    BITMAPFILEHEADER bmpheader;
    BITMAPINFOHEADER bmpinfo;
    // value to be used in ReadFile funcs
    DWORD bytesread;
    // open file to read from
    HANDLE file = CreateFile ( bmpfile , 
                               GENERIC_READ, 
                               FILE_SHARE_READ,
                               NULL, 
                               OPEN_EXISTING, 
                               FILE_FLAG_SEQUENTIAL_SCAN, 
                               NULL );
    if ( NULL == file )
        return false;
     
    if ( ReadFile ( file, &bmpheader, sizeof ( BITMAPFILEHEADER ), &bytesread, NULL ) == false )
    {
        CloseHandle ( file );
        return false;
    }
 
    // Read bitmap info
    if ( ReadFile ( file, &bmpinfo, sizeof ( BITMAPINFOHEADER ), &bytesread, NULL ) == false )
    {
        CloseHandle ( file );
        return false;
    }
     
    // check if file is actually a bmp
    if ( bmpheader.bfType != 'MB' )
    {
        CloseHandle ( file );
        return false;
    }
 
    // get image measurements
    *width   = bmpinfo.biWidth;
    *height  = abs ( bmpinfo.biHeight );
 
    // Check if bmp iuncompressed
    if ( bmpinfo.biCompression != BI_RGB )
    {
        CloseHandle ( file );
        return false;
    }
 
    // Check if we have 24 bit bmp
    if ( bmpinfo.biBitCount != 24 )
    {
        CloseHandle ( file );
        return false;
    }
     
    // create buffer to hold the data
    *size = bmpheader.bfSize - bmpheader.bfOffBits;
  
    // move file pointer to start of bitmap data
    SetFilePointer ( file, bmpheader.bfOffBits, NULL, FILE_BEGIN );
    // read bmp data
    if ( ReadFile ( file, Buffer, *size, &bytesread, NULL ) == false )
    {
        CloseHandle ( file );
        return false;
    }
 
    // everything successful here: close file and return buffer
     
    CloseHandle ( file );
 
    return true;
}
 
std::unique_ptr<BYTE[]> Utilities::CreateNewBuffer( unsigned long& padding,
                                         BYTE* pmatrix, 
                                         const int& width,
                                         const int& height )
{
    padding = ( 4 - ( ( width * 3 ) % 4 ) ) % 4;  
    int scanlinebytes = width * 3;
    int total_scanlinebytes = scanlinebytes + padding;
    long newsize = height * total_scanlinebytes;
    std::unique_ptr<BYTE[]> newbuf( new BYTE[ newsize ] );
 
    // Fill new array with original buffer, pad remaining with zeros
    std::fill( &newbuf[ 0 ], &newbuf[ newsize ], 0 );
    long bufpos = 0;   
    long newpos = 0;
    for ( int y = 0; y < height; y++ )
    {
        for ( int x = 0; x < 3 * width; x+=3 )
        {
            // Determine positions in original and padded buffers
            bufpos = y * 3 * width + ( 3 * width - x );     
            newpos = ( height - y - 1 ) * total_scanlinebytes + x; 
             
            // Swap R&B, G remains, swap B&R
            newbuf[ newpos ] = pmatrix[ bufpos + 2 ]; 
            newbuf[ newpos + 1 ] = pmatrix[ bufpos + 1 ];  
            newbuf[ newpos + 2 ] = pmatrix[ bufpos ];       
        }
    }
 
    return newbuf;
}

void Utilities::Create_Empty_Image_Queue(void)
{
   pFront = NULL;
   pRear  = NULL;
}

ImageQueue* Utilities::Create_Image_Element_In_ImageQueue(char *ImageData)
{
   ImageQueue *NewImage = (struct MessageQueue*)malloc(sizeof(struct MessageQueue));
   
   if(NewImage != NULL)
   {
       NewImage->pImageData = ImageData;
	   
	   NewImage->NextMessage = NULL;
   }
   
   return(NewImage);
}

void Utilities::Add_Image_To_ImageQueue(char *Image)
{
   ImageQueue *NewImage = Create_Image_Element_In_ImageQueue(Image);
   
   if(NewImage == NULL)
   {
		printf("Memory Allocation Failed to store the Image\r\n");
		
		return;
   }
   else
   {
     if(pFront == NULL)
	 {
	    pFront = pRear = NewImage;
		pFront->NextMessage = NULL;
	 }
	 else
	 {
		pRear->NextMessage = NewImage;
        pRear = NewImage;
        pRear->NextMessage = NULL;
	 }
   }
   
}

void Utilities::Remove_Image_From_The_ImageQueue(void)
{
     if(pFront == NULL)
	 {
	    printf("The Image Queue Is Empty, Nothing to Remove\r\n");
		
	 }
	 else
	 {
	    ImageQueue *TempImage = pFront;
		
		pFront = pFront->NextMessage;
		
		free(TempImage);
	 }
}

void Utilities::Display_Image_From_The_ImageQueue()
{
    if(pFront==NULL)
        printf("Queue is empty\n");
    else
    {
        ImageQueue *TempImage = pFront;
        while(TempImage!=NULL)
        {
            printf("%s->",TempImage->pImageData);
            TempImage=TempImage->NextMessage;
        }      
		printf("\n");
    }
} 

/*
char * Utilities::Read_Image_Data_From_ImageQueue(void)
{
	if(pRear==NULL)
	{
		printf("Queue is empty\n");
	}
	else
	{

	}
}*/