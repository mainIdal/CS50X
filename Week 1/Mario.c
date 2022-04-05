#include <stdio.h>
#include <cs50.h>
int main(void)
{
	int height;
	do
	{
		height = get_int("Please, type a height length between [1,8]: ");
	}while(height < 1 || height > 8);
	int row,column;
	for(row=0;row<height;row++)
	{
		for(column=0;column<height;column++)
			if(row+column>= height-1)
				printf("#");
			else
				printf(" ");
		printf("\n");
	}
	return 0;
}