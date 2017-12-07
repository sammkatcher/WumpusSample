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



void goldNearPitEdgeCase(){
	// Given: 3 squares around you. 1 is safe, 1 is a pit (location known), 1 is unknown.
	// Sense: Breeze and Glimmer

	// you will still get the breeze from the pit and no matter what you will be unable to go to the gold
	// EDGE CASE! So..
	// if (total number of  surrounding squares - 1) does not contain Uknown, Gold, Potential Gold, 
	// then the Unknown must be the Gold.
}

void triangulateDanger(){
	// if you know 4 squares around an object has a sense, then the something in the middle is defininte
	//if you know 3 squares around an object that also is on an edge, it's something definite
	// if oyu know 2 squares arond a corner has something, then it's definite
}



int main(){
	// Sample grid
	#ifndef ROBOT_CONNECTED
	char testgrid [4][4];
	testgrid[0][0] = 's';
	testgrid[0][1] = 's';
	testgrid[0][2] = 's';
	testgrid[0][3] = 'w';
	testgrid[1][0] = 's';
	testgrid[1][1] = 's';
	testgrid[1][2] = 'p';
	testgrid[1][3] = 's';
	testgrid[2][0] = 's';
	testgrid[2][1] = 's';
	testgrid[2][2] = 's';
	testgrid[2][3] = 's';
	testgrid[3][0] = 's';
	testgrid[3][1] = 's';
	testgrid[3][2] = 'g';
	testgrid[3][3] = 'p';
	
	int senseNumber = getSenseNumber(char testgrid, int x, int y, int BOARDSIZE);

	#endif
}