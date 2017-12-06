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



void UpdateBoard(int input){
	// given an input
	// given as a number that is a sum of the possible inputs
	// gold = 8, glimmer = 4, stench = 2, breeze = 1, nothing = 0
	// code does not keep track of the orientation of the robot
	// if the add is greater than 8, you're on the gold. cannot take more user input.
	//must go back to start.
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