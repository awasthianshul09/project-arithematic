#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int ret ;

	printf("calling execl.....\n");

	ret = execl("/bin/ls","ls","-1",NULL);

	printf("execL failed.....ret = %d\n",ret );

	return 0;
}