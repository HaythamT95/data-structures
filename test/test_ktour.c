#include <stdio.h>

#include "ktour.h"

enum state
{
	FAIL,
	SUCCESS
};

static int TestRunner();

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;
	int steps[64][2] = {0};
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int covert_steps_to_matrix[8][8];

	/*for(k = 0; k < 8; ++ k)
	{
		for(l = 0; l < 8; ++l)
		{
			state = KnightTour(k, l, steps);
			if(SUCCESS == state)
			{
				printf("%d %d\n",k,l);
			}
	
		}
	}*/

	state = KnightTour(x, y, steps);

	if(SUCCESS == state)
	{
		printf("Found path :)\n");

		for(i = 0; i < 64; ++i)
		{
			covert_steps_to_matrix[steps[i][0]][steps[i][1]] = i;
		}

		for(i = 0; i < 8; ++i)
		{
			for(j = 0; j < 8; ++j)
			{
				if(covert_steps_to_matrix[i][j] > 9)
				{
					printf("%d ", covert_steps_to_matrix[i][j]);
				}
				else
				{
					printf("%d  ", covert_steps_to_matrix[i][j]);					
				}
			}
			printf("\n");
		}

	}
	else
	{
		printf("Didn't find path :(\n");
	}

	return state;
}