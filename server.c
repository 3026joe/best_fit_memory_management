#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char* p;																		//pointer to the entire memory block
int size;																		//keeping track of the block size

typedef struct book
{
	char status;																//'0' indicates a free block and '1' indicates an allocated block
	int block_size;																//keeping track of the size of the block
}book;

void allocate(int n)
{
	p=malloc(n);																//allocating the required amount of bytes using malloc
	size=n;																		//storing the allocated bytes
	book* b=(book*)p;															//creating the first book keeping structure for the free space
	b->status='0';																//labelling the block as free
	b->block_size=n-sizeof(book);												//storing the size of the first free block
}

void* mymalloc(int s)
{
	book* bp=(book*)p;															//pointer to iterate through the memory block
	book* min_bp=NULL;															//pointer to the block of minimum size block as per requirements
	int min=size;																//keeping track of the minimum size encountered
	void* point=NULL;															//pointer to the memory block to be returned
	int traversed=0;															//to keep track of how many bytes have been traversed
	int found=0;																//to help the loop terminate
	while(traversed<size && !found)												//iterating through the memory block
	{
		if(bp->status=='0')														//checking if the current block is free
		{
			if(bp->block_size==s)												//this is the minimum size block that meets the size requirement so the loop can terminate
			{
				min_bp=bp;														//storing the location of the book keeping of the block
				found=1;														//variable to stop the loop
			}
			else if(bp->block_size>s && bp->block_size<min)
			{
				min=bp->block_size;												//storing the location of the book keeping of the block
				min_bp=bp;														//changing the minimum size block that has been found
			}
		}
		traversed += sizeof(book) + bp->block_size;								//updating the number of bytes traversed
		bp += sizeof(book) + bp->block_size;									//moving the pointer to the next book keeping structure
	}
	if(min_bp!=NULL)															//if a block of appropriate size has been found
	{
		min_bp->status='1';														//changing the status of the block to "allocated"
		if(min_bp->block_size>s)												//if the block is bigger that required
		{
			if(min_bp->block_size - s > sizeof(book))							//if the block is big enough to accomodate another book keeping structure and memory
			{
				book* new_book=(book*)(min_bp + sizeof(book) + s);				//creating the new book keeping structure
				new_book->status='0';											//labelling it as a free block
				new_book->block_size=min_bp->block_size - sizeof(book)- s;		//storing the size of the new free block
				min_bp->block_size=s;											//storing the size of the allocated block
			}
		}
		point=(void*)(min_bp + sizeof(book));									//storing the address of the allocated block
	}
	return point;																//returning the pointer
}

void myfree(void *b)
{
	if(b!=NULL)																	//making sure the pointer is not NULL
	{
		book* bp=(book*)p;														//pointer to the book keeping structure of the block that before the one that is to be freed
		book* fbp=(book*)b - sizeof(book);										//pointer to the book keeping structure of the block that is to be freed
		book* nbp= fbp + sizeof(book) + fbp->block_size;						//pointer to the book keeping structure of the block that after the one that is to be freed
		while((bp + sizeof(book) + bp->block_size) < fbp)						//moving the pointer to the appropriate previous block
		{
			bp=bp + sizeof(book) + bp->block_size;
		}
		if(nbp!=NULL && nbp->status=='0')										//if the next block is also free
		{
			fbp->block_size += nbp->block_size + sizeof(book);					//changing the size of the block to include the next block
		}
		if(bp->status=='0')														//if the previous block is free
		{
			bp->block_size += fbp->block_size + sizeof(book);					//changing the size of the block to include the previous block
		}
		fbp->status='0';														//setting the status of the block to free
	}
}

void print_book()
{
	printf("%d",sizeof(book));													//printing the size of the book keeping structure
}

void display_mem_map()
{
	book* bp=(book*)p;															//pointer to the first book keeping structure
	int traversed=0;															//keeping track of the bytes traversed
	while(traversed<size)
	{
		printf("%d\t",(bp-(book*)p));											//printing the starting position of the current book keeping structure
		print_book();
		printf("\tbook\n");														//printing the size of the current boock keeping structure
		printf("%d\t",(bp + sizeof(book) - (book*)p));							//printing the starting position of the current block
		printf("%d\t",bp->block_size);											//printing the size of the current memory block
		if(bp->status=='0')														//checking if the block is free
			printf("free\n");
		else
			printf("allocated\n");
		traversed += sizeof(book) + bp->block_size;								//updating the number of bytes traversed
		bp += sizeof(book) + bp->block_size;									//moving the pointer to the next book keeping structure
	}
}
