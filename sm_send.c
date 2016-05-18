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
#define BUFF_SIZE 512

int main(int argc, char const *argv[])
{
	void *shared_memory = (void *)0;

	struct shared_mem *shared_stuff;
	char buffer[BUFF_SIZE];
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
	
	
	while(shared_stuff->written_by_you == 1 );
	{
		sleep(1);
		printf("waiting for the client\n");
	}

	printf("enter some text\n");
	fgets(buffer,BUFF_SIZE,stdin);

	strcpy(shared_stuff->mem_buff,buffer);

	shared_stuff->written_by_you =1;

	if (shmdt(shared_memory) == -1)
	{
		perror("shmdt failed");
		exit(EXIT_FAILURE);
	}

	return 0;
}

