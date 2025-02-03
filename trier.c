#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
	int len;

	len = 1;
	while (len < argc)
	{
		printf("%d ", atoi(argv[len]) + 1);
		len++;
	}
	return (1);
}