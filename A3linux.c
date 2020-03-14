//compile with -lpthread -lm
#include <pthread.h>	//includes pthread_t class and pthread methods
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *numberPrintThread(void *num) {
	int* curr = (int*)num;
	int min = (*curr>1) ? pow(10,*curr) : 0;

	printf("Start Thread - %d\n", *curr);

	for (int i = min+1; i <= min+50; i++)
		printf("%d\n", i);

	printf("Finish Thread - %d\n", *curr);

	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[4];
	pthread_attr_t attr;
	void *status;
	int number[4];

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	printf("Start Application\n");

	for (int i = 0; i < 4; i++)
	{
		number[i] = i+1;

		int curr = pthread_create(&threads[i], &attr, numberPrintThread, (void *)(&number[i]));

		if (curr) {
			printf("Error creating thread #%d\n", number[i]);
			exit(-1);
		}
	}

	pthread_attr_destroy(&attr);
	for (int i = 0; i < 4; i++)
  {
		int curr = pthread_join(threads[i], &status);
  }

	printf("Finish Application\n");
	pthread_exit(NULL);

	return 0;
}
