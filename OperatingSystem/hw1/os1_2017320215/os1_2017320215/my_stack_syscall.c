#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h> 
#include <linux/slab.h>	// for kmalloc & kfree functions

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

StackNodePtr stackPtr = NULL;

// stack push
// a: input
SYSCALL_DEFINE1(oslab_push, int, a)
{
	StackNodePtr printPtr = NULL;
	StackNodePtr newPtr;

	int flag = 1;
	
	printPtr = stackPtr;
	// if a same data already exists, then ignore this input.
	while (printPtr != NULL)
	{
		if(a == printPtr->data)
		{
			flag = 0;
			break;
		}
		printPtr = printPtr->nextPtr;
	}

	// flag=0 means that there is already a same date as input.
	if (flag)
	{
		// allocate memory for push
		newPtr = (struct stackNode*)kmalloc(sizeof(StackNode), GFP_KERNEL);
		if (newPtr == NULL)
		{
			return -1;
		}
		else	// push new input into stack
		{
			newPtr->data = a;
			newPtr->nextPtr = stackPtr;
			stackPtr = newPtr;
		}
	}
	// duplicate
	else
	{
		printf("Duplicate!\n");
	}

	// Print stack

	printPtr = stackPtr;
	printk("Stack Top----------");
	if (printPtr != NULL)
	{
		while (printPtr != NULL)
		{
			printk(KERN_INFO"%d", printPtr->data);
			printPtr = printPtr->nextPtr;
		}
	}
	printk("Stack Bottom-------");

	if(flag)
		return 1;
	else
		return 0;
}

// stack pop
SYSCALL_DEFINE0(oslab_pop){
	
	StackNodePtr tempPtr = NULL;
	int popValue;
	
	tempPtr = stackPtr;
	popValue = stackPtr->data;
	stackPtr = stackPtr->nextPtr;
	kfree(tempPtr);	// free the memory
	return popValue;
}