#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

void myhandle(int mysignal)
{
	
	signal(SIGINT,SIG_IGN);
}

int main(int argc, char const *argv[])
{
	int i=0;
	signal(SIGINT,myhandle);
	while(1){

		printf("i = %d\n",i);
		i++;
		sleep(2);
	}

	return 0;
}