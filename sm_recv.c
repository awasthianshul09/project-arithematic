#define TEXT_SIZE 2048

struct shared_mem
{
	int written_by_you;
	char mem_buff[TEXT_SIZE];
};
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
	void *shared_memory = (void *)0;

	struct shared_mem *shared_stuff;
	int shmid;

	shmid = shmget((key_t)1234,sizeof(struct shared_mem),0666|IPC_CREAT);

	if (shmid == -1)
	{
		perror("shmget failed");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid,(void *)0,0);

	if (shared_memory == (void*)-1)
	{
		perror("shmat failed");
		exit(EXIT_FAILURE);
	}

	printf("memory attached at %X\n",(int)shared_memory );

	shared_stuff = (struct shared_mem *)shared_memory;
	shared_stuff->written_by_you = 0;

	if (shared_stuff->written_by_you ==0)
	{
		printf("you wrote: %s\n",shared_stuff->mem_buff );
		sleep(rand()%4);
		shared_stuff->written_by_you = 0;

	}

	if (shmdt(shared_memory) == -1)
	{
		perror("shmdt failed");
		exit(EXIT_FAILURE);
	}

	if (shmctl(shmid,IPC_RMID,0) == -1)
	{
		perror("shared memory deletion failed");
		exit(EXIT_FAILURE);
	}



	return 0;
}

