#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int ret ;

	printf("calling execl.....\n");

	ret = execl("client1","client1","localhost",NULL);

	printf("execL failed.....ret = %d\n",ret );

	return 0;
}