/* Driver.h*/

#ifndef DRIVER_H
#define DRIVER_H

DWORD WINAPI Driver_Thread( LPVOID lpParam );

class Driver
{
public:

private:

	int ProcessImage(void);
};

#endif //DRIVER_H