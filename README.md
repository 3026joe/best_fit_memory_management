# best_fit_memory_management

This project is an implementation of the best fit memory management algorithm.
Implemented in C, the program initially allocates a block of memory using C's predefined malloc function. It then allocates and frees (using mymalloc and myfree) memory from this block as and when the user requires. The memory block is tracked using a book-keeping for each block of memory that is allocated. It also includes a function (display_mem_map) that can display the book-keeping.

void allocate(int n)
	*	The function takes a parameter n, that specifies the number of bytes to be allocated
	*	It uses malloc to allocate n bytes.
	*	It also creates a book keeping structure to keep track of the initially free space.


void* mymalloc(int s)
	*	It implements the best fit algorithm for memory allocation.
	*	A loop is used to iterate through the entire memory block.
	*	Once a free block of the same size is found, the loop is terminated
	*	If no such block is found, the smallest possible block that is greater than the required size is also kept track of.
	*	If the block is of same size as that is required, the block's status is changed to "1"
	*	If the block is bigger, there are two possiblities:
			i) The excecss space is enough to store another book keeping structure and has at least one more byte. In this case, a new book keeping stucture is created to keep track of the new block and all the block sizes are changed appropriately.
			ii) The excess space is not enough to store another book keeping structure, the excess space is also allocated to the same block, and the size is kept the same.
	* 	A pointer to the allocated block is returned. If no appropriately size is found, NULL is returned.


typedef struct book
{
	char status;
	int block_size;
}book;

	*	The book keeping structure has only two parts.
	*	char status keeps track of whether the block is free or allocated
	*	int block_size keeps track of the size of the block that it points to.


Key takeaway from this assignment:
	*	This assignment taught me a lot about the various memory allocation algorithms a computer uses.
	*	Deciding on a minimal book keeping structure was another learning experience.
	*	I initially planned to use pointers that point to the blocks of memory and to the next book keeping structure.
	*	But I realised that it would be a waste of memory as incrementing the pointer by the size of the block would automatically take it to the next book keeping structure.
