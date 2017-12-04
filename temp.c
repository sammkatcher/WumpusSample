int getSenseNumber(char[BOARDSIZE][BOARDSIZE] grid, int x, int y, BOARDSIZE)
{
	int sense = 0;
	// x - 1, y
	if(!isOutOfBounds(x - 1, y, BOARDSIZE))
	{
		sense |= getObjectInfo(grid[x - 1][y]);
	}
	
	// x + 1, y
	if(!isOutOfBounds(x + 1, y, BOARDSIZE))
	{
		sense |= getObjectInfo(grid[x + 1][y]);
	}
	
	// x, y - 1
	if(!isOutOfBounds(x, y - 1, BOARDSIZE))
	{
		sense |= getObjectInfo(grid[x][y - 1]);
	}
	
	// x, y + 1
	if(!isOutOfBounds(x, y + 1, BOARDSIZE))
	{
		sense |= getObjectInfo(grid[x][y + 1]);
	}
	
	// Check x, y for gold
	if(grid[x][y] == 'g')
	{
		sense |= 8;
	}
	
	return sense;
}


int getObjectInfo(char object)
{
	switch(object)
	{
		case 'p':
			return 1;
			break;
		
		case 'w':
			return 2;
			break;
		
		case 'g':
			return 4;
			break;
	}
	
	return 0;
}