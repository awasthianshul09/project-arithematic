#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>



#define BUFSIZE 1024


struct my_msg_st
{
	long int my_msg_type;
	char some_text[BUFSIZE];
};

int main(int argc, char const *argv[])
{
	int running = 1;
	int msgid;
 	char buffer[BUFSIZE];
 	struct my_msg_st some_data;

 	long int msg_to_recieve = 0;
 	msgid = msgget((key_t)1234,0666|IPC_CREAT);

 	if (msgid == -1)
 	{
 		perror("msgget_failed");
 		exit(EXIT_FAILURE);
 	}

 	printf("enter some text");
 	fgets(buffer,BUFSIZE,stdin);
 	some_data.my_msg_type = 1;
 	strcpy(some_data.some_text,buffer);

 	if (msgsnd(msgid,(void *)&some_data,512,0)== -1)
 	{
 		perror("msg send failed");
 		exit(EXIT_FAILURE);
 	}

	return 0;
}