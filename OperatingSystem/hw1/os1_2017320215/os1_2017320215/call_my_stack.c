#include <stdio.h>
#include <unistd.h>

#define my_stack_push 335
#define my_stack_pop 336
#define loop 3

int main(void)
{
	int r;
	int n;
	int j;
	int reduce = 0;					// if a duplicate input, then the number of pop times minus 1

	for (j = 0; j < loop; j++)		// push
	{
		printf("Push: ");
		scanf("%d", &n);
		r = syscall(my_stack_push, n);
		if (r == 0)					// r==0 means that there is already a same data exists
			reduce++;
	}

	j = 0;							// reset j
	j = j + reduce;

	for (; j < loop; j++)			// pop
	{
		printf("Pop: ");
		r = syscall(my_stack_pop);
		printf("%d\n", r);
	}
	return 0;
}