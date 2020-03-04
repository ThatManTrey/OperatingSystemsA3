
#include <Windows.h>	//includes HANDLE class, WaitForSingleObject (duh :))
#include <process.h>	//includes beginthreadex method
#include <iostream>
#include <math.h>

unsigned int __stdcall numberPrintThread(void* num)
{
	int* curr = (int*)num;
	int min = (*curr>1) ? pow(10,*curr) : 0;

	printf("Start Thread - %d\n", *curr);

	for (int i = min+1; i <= min+50; i++)
		printf("%d\n", i);

	printf("Finish Thread - %d\n", *curr);

	return 0;
}

int main()
{
	HANDLE hndl[4];
	int number[4];

	printf("Start Application\n");

	for (int i = 0; i < 4; i++)
	{
		number[i] = i+1;
		hndl[i] = (HANDLE)_beginthreadex(NULL, 0, &numberPrintThread, &number[i], 0, NULL);
	}
	
	for (int i=0;i<4;i++)
		WaitForSingleObject(hndl[i], INFINITE);

	for (int i = 0; i < 4; i++)
		CloseHandle(hndl[i]);

	printf("Finish Application\n");

	getchar();
	return 0;
}