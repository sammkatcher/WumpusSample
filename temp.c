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


void updatesSurroundingMightBes(square my_grid[BOARDSIZE][BOARDSIZE], point cur_loc, char x){
	
	if (!isOutOfBounds(my_grid[cur_x+1][cur_y] && (my_grid[cur_x+1][cur_y].isUnknown)){
		updateMightBe(x, my_grid[cur_x+1][cur_y]);
	}
	if (!isOutOfBounds(my_grid[cur_x-1][cur_y] && (my_grid[cur_x-1][cur_y].isUnknown)){
		updateMightBe(x, my_grid[cur_x-1][cur_y]);
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y+1] && (my_grid[cur_x][cur_y+1].isUnknown)){
		updateMightBe(x, my_grid[cur_x][cur_y+1]);
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y-1] && (my_grid[cur_x][cur_y-1].isUnknown)){
		updateMightBe(x, my_grid[cur_x][cur_y-1]);
	}
}


void updateMightBe(char x, , square sqr){

	if (x == 'g'){ // mightBeGold
		sqr.mightBeGold = true;
	}

	if (x == 's'){ // might be wumpus
		sqr.mightBeWumpus = true;
	}
	if (x == 'b'){ // might be pit
		sqr.mightBePit = true;
	}
}

void foundGold(square mysqr){
	// do what you're supposed to do when you find gold
	mysqr.isGold = true;
	printf("Found gold!\n");
}

void foundGlimmer(square mysqr){
	//do what you're supposed to do when you find glimmer
	printf("Found glimmer!\n");
	// move safely around in glimmer squares until you find the gold
	// for each surrounding square except the ones you've visited, change mightBeGold to True
	updateMightBe(mysqr, 'g');
	// Figure out where to move next, probably to one of these spots
}

void foundStench(square mysqr){
	//do what you're supposed to do when you find a stench
	// mark the squares around as potential wumpus
	//go back and try a different something
	printf("Found stench!\n");
	updateMightBe(mysqr, 's');
}

void foundBreeze(square mysqr){
	//do what you're supposed to do when you find a breeze
	// mark the squares around as potential pit
	//go back and try a different something
	printf("Found breeze!\n");
	updateMightBe(mysqr, 'b');
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

void convertSenseNumber(int input, point cur_loc, square my_grid[BOARDSIZE][BOARDSIZE]){
	// given an input
	// given as a number that is a sum of the possible inputs
	// gold = 8, glimmer = 4, stench = 2, breeze = 1, nothing = 0
	// code does not keep track of the orientation of the robot
	// if the add is greater than 8, you're on the gold. cannot take more user input.
	//must go back to start.
	int cur_x = cur_loc.x;
	int cur_y = cur_loc.y;
	// Using a single ampersand does bitwise and to
    //   determine what the input is.
    if(input & 0x00000008){
    	// Input is: on gold
        printf("Gold! ");
        // do what needs to be done when found gold
    }  
    if(input & 0x00000004){
    	// Input is: near gold
        printf("Glimmer! ");
	}
    if(input & 0x00000002){
    	// Input is: near wumpus
        printf("Wumpus! ");
    	my_grid[cur_x+1][cur_y].mightBeWumpus = true;
    	my_grid[cur_x-1][cur_y].mightBeWumpus = true;
    	my_grid[cur_x][cur_y+1].mightBeWumpus = true;
    	my_grid[cur_x][cur_y-1].mightBeWumpus = true;

    }
    if(input & 0x00000001){
    	// Input is: near hole
    	printf("Breeze! ");	
    }
    
    printf("\n");
    fflush(stdout);
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