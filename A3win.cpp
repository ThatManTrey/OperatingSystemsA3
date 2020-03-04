
#include <Windows.h>	//includes HANDLE class, WaitForSingleObject (duh :))
#include <process.h>	//includes beginthreadex method
#include <iostream>
#include <math.h>

volatile int counter = 0;

int isPrime(int n)
{
	for (int i = 2; i < (int)(sqrt((float)n) + 1.0); i++) {
		if (n % i == 0) return 0;
	}
	return 1;
}

unsigned int __stdcall mythread(void*)
{
	char* s;
	while (counter < 25) {
		int number = counter++;
		s = "No";
		if (isPrime(number)) s = "Yes";
		printf("Thread %d value = %d is prime = %s\n",
			GetCurrentThreadId(), number, s);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	HANDLE myhandleA, myhandleB;

	myhandleA = (HANDLE)_beginthreadex(0, 0, &mythread, (void*)0, 0, 0);
	myhandleB = (HANDLE)_beginthreadex(0, 0, &mythread, (void*)0, 0, 0);

	WaitForSingleObject(myhandleA, INFINITE);
	WaitForSingleObject(myhandleB, INFINITE);

	CloseHandle(myhandleA);
	CloseHandle(myhandleB);

	getchar();

	return 0;
}