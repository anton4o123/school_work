#include <stdio.h>

#define SIZE 3
#define SIZE2 (SIZE*SIZE)

int grid[9][9] = { 0 };

int check_hor_ver()
{
	int row_col, i, j;

    for(row_col = 0; row_col < SIZE2; ++row_col)
    {
        for(i = 0; i < SIZE2 - 1; ++i)
        {
            for(j = i + 1; j < SIZE2; ++j)
            {
                if(grid[i][row_col] == grid[j][row_col] && grid[i][row_col] != 0 && grid[j][row_col] != 0)
                {
                    return -1;
                }
                if(grid[row_col][i] == grid[row_col][j] && grid[row_col][i] != 0 && grid[row_col][j] != 0)
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

int check_box( )
{
    int i, j, row_offset, col_offset;

    for(row_offset = 0; row_offset < SIZE2; row_offset += SIZE)
    {
        for(col_offset = 0; col_offset < SIZE2; col_offset += SIZE)
        {
            for(i = 0; i < SIZE2 - 1; ++i)
            {
                for(j = i + 1; j < SIZE2; ++j)
                {
                    if(grid[i/SIZE + row_offset][i%SIZE + col_offset] == grid[j/SIZE + row_offset][j%SIZE + col_offset] && grid[i/SIZE + row_offset][i%SIZE + col_offset] != 0 && grid[j/SIZE + row_offset][j%SIZE + col_offset] != 0)
                    {
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

int check( )
{
	return check_hor_ver() + check_box();
}

int count_empty_cells( )
{
	int i, j, count = 0;

	for(i = 0; i < SIZE2; ++i)
	{
		for(j = 0; j < SIZE2; ++j)
		{
			if(grid[i][j] == 0)
			{
				++count;
			}
		}
	}
	return count;
}

void row_col_solve( int index, int digit )
{
	int i, fit_row = 0, fit_col = 0, temp_row, temp_col;

	for(i = 0; i < SIZE2; ++i)
	{
		if(grid[index][i] == 0)
		{
			grid[index][i] = digit;
			if(check() == 0)
			{
				++fit_row;
				temp_col = i;
			}
			grid[index][i] = 0;
		}
		
		if(grid[i][index] == 0)
		{
			grid[i][index] = digit;
			if(check() == 0)
			{
				++fit_col;
				temp_row = i;
			}
			grid[i][index] = 0;
		}
	}

	if(fit_row == 1)
	{
		grid[index][temp_col] = digit;
	}

	if(fit_col == 1)
	{
		grid[i][index] = digit;
	}
}

void constraint_solve( )
{
	int empty_cells = 0, digit, index;

	while(empty_cells != count_empty_cells())
	{
		empty_cells = count_empty_cells();
		for(digit = 1; digit <= SIZE2; ++digit)
		{
			for(index = 0; index < SIZE2; ++index)
			{
				row_col_solve(index, digit);
			}
		}
	}
}

void print_grid( )
{
	int i, j;

	for(i = 0; i < SIZE2; ++i)
	{
		for(j = 0; j < SIZE2; ++j)
		{
			if(j > 0 && j % 3 == 0)
			{
				printf("\t");
			}
			if(grid[i][j] == 0)
			{
				printf("- ");
			} else {
				printf("%d ", grid[i][j]);
			}
			if(j == 8)
			{
				printf("\n");
			}
		}
	}
}

int main( )
{
    grid[0][1] = 7;
    grid[0][2] = 8;
    grid[0][3] = 1;
    grid[0][7] = 2;
    grid[1][0] = 1;
    grid[1][4] = 6;
    grid[1][5] = 2;
    grid[1][8] = 3;
    grid[2][0] = 5;
    grid[2][4] = 9;
    grid[3][0] = 8;
    grid[3][6] = 4;
    grid[3][8] = 6;
    grid[4][1] = 6;
    grid[4][2] = 1;
    grid[4][4] = 7;
    grid[4][7] = 9;
    grid[5][1] = 9;
    grid[5][6] = 3;
    grid[6][3] = 5;
    grid[6][5] = 4;
    grid[6][6] = 2;
    grid[6][8] = 7;
    grid[7][0] = 6;
    grid[7][4] = 8;
    grid[7][7] = 3;
    grid[8][1] = 5;
    grid[8][3] = 7;
    grid[8][6] = 9;

	printf("%d\n", check());
	printf("%d\n", count_empty_cells());
	print_grid();
	constraint_solve();
	print_grid();
	return 0;
}
