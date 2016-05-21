/*this program demonstrates the use pipes to wait for a sibling process */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	pid_t pid,pid_c1,pid_c2;
	int ret,status;
	int mypipefd[2];
	char buf[32];

	ret = pipe(mypipefd);

	if (ret == -1)
	{
		perror("pipe");
		exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
		/*child process 1*/

		close(mypipefd[1]);
		pid_c1 = getpid();

		printf("child process 1 with pid %d\n",pid_c1);
		printf("child1 waiting for child2\n");

		read(mypipefd[0],buf,20);
		printf("buf:%s\n",buf);

		printf("child process 1 is exiting\n");

	}

	else		/*parent process*/
	{	
		pid = fork();
		if (pid == 0)
		{
			/*child process 2*/

			close(mypipefd[0]);
			pid_c2 = getpid();
			printf("child process 2 with pid %d \n",pid_c2);
			sleep (5);
			write(mypipefd[1],"child 2 has finished its work",32);
			printf("child process 2 is exiting\n");
		}

		else
		{
				/*parent process*/

			 while ((pid = wait(&status)) > 0)
    			{
        			printf("Exit status of %d was %d (%s)\n", (int)pid, status,(status >=0) ? "accept" : "reject");
    			}

			printf("parent exiting\n");

		}
	}	
			
			


	return 0;
}