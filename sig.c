#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

void myhandle(int mysignal)
{
	printf("myhandle with signal %d \n",mysignal);
	signal(SIGTERM,myhandle);
}

int main(int argc, char const *argv[])
{
	int i=0;
	signal(SIGTERM,myhandle);
	while(1){

		printf("i = %d\n",i);
		i++;
		sleep(2);
	}

	return 0;
}