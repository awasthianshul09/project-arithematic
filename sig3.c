#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

int SIGINT_var;

void myhandle(int mysignal)
{
	SIGINT_var = 1;

	signal(SIGINT,myhandle);
}

int main(int argc, char const *argv[])
{
	int i=0;
	signal(SIGINT,myhandle);
	while(1){

		if (SIGINT_var == 1)
		{
			printf("pressed CTRL+C\n");
			SIGINT_var = 0;
		}

		printf("i = %d\n",i);
		i++;
		sleep(2);
	}

	return 0;
}