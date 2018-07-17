#include "common.h"
#include "Dispatcher.h"
#include "Manager.h"
#include "Driver.h"
#include "Utilities.h"

void main()
{
	Utilities MyQueue;
	/*
    // Data of Thread 1
    int Data_Of_Thread_1 = 1;
    // Data of Thread 2
    int Data_Of_Thread_2 = 2;
    // Data of Thread 3
    int Data_Of_Thread_3 = 3;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_1 = 0;
    // variable to hold handle of Thread 1 
    HANDLE Handle_Of_Thread_2 = 0;
    // variable to hold handle of Thread 1
    HANDLE Handle_Of_Thread_3 = 0;
    // Aray to store thread handles 
    HANDLE Array_Of_Thread_Handles[3];

    // Create Dispatcher_Thread.
    Handle_Of_Thread_1 = CreateThread( NULL, 0, 
           Dispatcher_Thread, &Data_Of_Thread_1, 0, NULL);  
    if ( Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);
    
    // Create Manager_Thread.
    Handle_Of_Thread_2 = CreateThread( NULL, 0, 
           Manager_Thread, &Data_Of_Thread_2, 0, NULL);  
    if ( Handle_Of_Thread_2 == NULL)
        ExitProcess(Data_Of_Thread_2);
    
    // Create Driver_Thread.
    Handle_Of_Thread_3 = CreateThread( NULL, 0, 
           Driver_Thread, &Data_Of_Thread_3, 0, NULL);  
    if ( Handle_Of_Thread_3 == NULL)
        ExitProcess(Data_Of_Thread_3);


    // Store Thread handles in Array of Thread
    // Handles as per the requirement
    // of WaitForMultipleObjects() 
    Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
    Array_Of_Thread_Handles[1] = Handle_Of_Thread_2;
    Array_Of_Thread_Handles[2] = Handle_Of_Thread_3;
    
    // Wait until all threads have terminated.
    WaitForMultipleObjects( 3, 
        Array_Of_Thread_Handles, TRUE, INFINITE);

    printf("Since All threads executed" 
           " lets close their handles \n");

    // Close all thread handles upon completion.
    CloseHandle(Handle_Of_Thread_1);
    CloseHandle(Handle_Of_Thread_2);
	CloseHandle(Handle_Of_Thread_3);
	*/
	MyQueue.Create_Empty_Image_Queue();

	MyQueue.Add_Image_To_ImageQueue("Rahul");

	printf("%s\n",MyQueue.pRear->pImageData);

	MyQueue.Add_Image_To_ImageQueue("Kumar");
	
	printf("%s\n",MyQueue.pRear->pImageData);
	
	MyQueue.Add_Image_To_ImageQueue("Bansal");

	printf("%s\n",MyQueue.pRear->pImageData);

	/*

	MyQueue.Add_Image_To_ImageQueue("HCL");

	MyQueue.Add_Image_To_ImageQueue("Technologies");

	MyQueue.Add_Image_To_ImageQueue("PvtLtd");

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();

	MyQueue.Remove_Image_From_The_ImageQueue();

	MyQueue.Display_Image_From_The_ImageQueue();*/


}