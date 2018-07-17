/* Utilities.h*/

#ifndef UTILITIES_H
#define UTILITIES_H

#include "common.h"

#define BUF_SIZE 255

typedef struct MessageQueue
{
	char *pImageData;
	char ImageBuff[1024];
	struct MessageQueue *NextMessage;
}ImageQueue;

class Utilities
{
public:

	void DisplayMessage (HANDLE hScreen, char *ThreadName, int Data, int Count);

	void SaveBitmapToFile( BYTE* pBitmapBits,  
                       LONG lWidth,  
                       LONG lHeight,  
                       WORD wBitsPerPixel, 
                       const unsigned long& padding_size,
                       LPCTSTR lpszFileName );

	bool LoadBMP ( int* width, 
					int* height, 
					unsigned long* size, 
					LPCTSTR bmpfile, 
					BYTE* Buffer);

	std::unique_ptr<BYTE[]> CreateNewBuffer( unsigned long& padding,
                                         BYTE* pmatrix, 
                                         const int& width,
                                         const int& height );
	void Create_Empty_Image_Queue(void);

	ImageQueue *Create_Image_Element_In_ImageQueue(char *ImageData);

	void Add_Image_To_ImageQueue(char *Image);

	void Remove_Image_From_The_ImageQueue(void);

	void Display_Image_From_The_ImageQueue();

	char * Read_Image_Data_From_ImageQueue(void);

	ImageQueue *pFront;
	ImageQueue *pRear;

private:
	
	

};


#endif //UTILITIES_H