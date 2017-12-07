// only works on a square board
bool isOutofBounds(int x, int y, int max){
	if(x <= 0 && x < max){
		printf("X in Bounds");
		if (y <= 0 && y < max){
			printf("Y in Bounds\n");
			return false;
		}
	}
	else{
		printf("Out of Bounds\n");
		return true;
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

void updatesSurroundingMightBes(square my_grid[BOARDSIZE][BOARDSIZE], point cur_loc, char x){
	if (!isOutOfBounds(my_grid[cur_x+1][cur_y]) && (my_grid[cur_x+1][cur_y].isUnknown)){
		updateMightBe(x, my_grid[cur_x+1][cur_y]);
	}
	if (!isOutOfBounds(my_grid[cur_x-1][cur_y]) && (my_grid[cur_x-1][cur_y].isUnknown)){
		updateMightBe(x, my_grid[cur_x-1][cur_y]);
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y+1]) && (my_grid[cur_x][cur_y+1].isUnknown)){
		updateMightBe(x, my_grid[cur_x][cur_y+1]);
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y-1]) && (my_grid[cur_x][cur_y-1].isUnknown)){
		updateMightBe(x, my_grid[cur_x][cur_y-1]);
	}
}

///////////////////////////////////////////////////////////////////
void foundGlimmer(square mysqr){
	//do what you're supposed to do when you find glimmer
	printf("Found glimmer!\n");
	updatesSurroundingMightBes(mysqr, 'g');
	// Figure out where to move next, probably to one of these spots
}

void foundStench(square mysqr){
	//do what you're supposed to do when you find a stench
	// mark the squares around as potential wumpus
	//go back and try a different something
	printf("Found stench!\n");
	updatesSurroundingMightBes(mysqr, 's');
}

void foundBreeze(square mysqr){
	//do what you're supposed to do when you find a breeze
	// mark the squares around as potential pit
	//go back and try a different something
	printf("Found breeze!\n");
	updatesSurroundingMightBes(mysqr, 'b');
}

//////////////////////////////////////////////////////////////////
void foundGold(square mysqr){
	// do what you're supposed to do when you find gold
	mysqr.isGold = true;
	printf("Found gold!\n");
}

void foundWumpus(square mysqr){
	// do what you're supposed to do when you find gold
	mysqr.isWumpus = true;
	printf("Found wumpus!\n");
}

void foundPit(square mysqr){
	// do what you're supposed to do when you find gold
	mysqr.isPit = true;
	printf("Found pit!\n");
}

/////////////////////////////////////////////////////////////////
void processesInputAndUpdateSurrounding(int input, point cur_loc, square my_grid[BOARDSIZE][BOARDSIZE]){
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
        foundGold(my_grid[cur_x][cur_y]);
    }  
    if(input & 0x00000004){
    	// Input is: near gold
        printf("Glimmer! ");
        foundGlimmer(my_grid[cur_x][cur_y]);
	}
    if(input & 0x00000002){
    	// Input is: near wumpus
        printf("Wumpus Stench! ");
        foundWumpus(my_grid[cur_x][cur_y]);
    	
    }
    if(input & 0x00000001){
    	// Input is: near hole
    	printf("Breeze! ");	
    	foundBreeze(my_grid[cur_x][cur_y]);
    }
    
    printf("\n");
    fflush(stdout);
}


char decideWheretoMove(my_grid[BOARDSIZE][BOARDSIZE]){
	int optionSize = 0;
	char options[4];
	// find the single best location to go to of the four surrounding squares
	if (!isOutOfBounds(my_grid[cur_x+1][cur_y]) && (my_grid[cur_x+1][cur_y].isUnknown || my_grid[cur_x+1][cur_y].isSafe)){
		options[0] = 'E';
		optionSize++;
	}
	if (!isOutOfBounds(my_grid[cur_x-1][cur_y]) && (my_grid[cur_x-1][cur_y].isUnknown || my_grid[cur_x-1][cur_y].isSafe)){
		options[1] = 'W';
		optionSize++;	
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y+1]) && (my_grid[cur_x][cur_y+1].isUnknown || my_grid[cur_x][cur_y+1].isSafe)){
		options[2] = 'N';
		optionSize++;
	}
	if (!isOutOfBounds(my_grid[cur_x][cur_y-1]) && (my_grid[cur_x][cur_y-1].isUnknown || my_grid[cur_x][cur_y-1].isSafe)){
		options[3] = 'S';
		optionSize++;
	}

	int random = rand()%optionSize;
	char direction = options[random];
	//go in the random direction
	return direction;
}

point updateCurrentLocation(char direction, point cur_loc){
	int cur_x = cur_loc.x;
	int cur_y = cur_loc.y;
	// Move
	if (direction == 'E'){
		cur_loc.x = cur_x+1;
	}
	if (direction == 'W'){
		cur_loc.x = cur_x-1;
	}
	if (direction == 'N'){
		cur_loc.y = cur_y+1;
	}
	if (direction == 'S'){
		cur_loc.y = cur_y-1;
	}
	return cur_loc;
}

void moveToNewLocation(char, direction, point cur_loc){
	updateCurrentLocation(direction, cur_loc);
	if (direction == 'E'){
		turn_right();
		sensor_forward();
		turn_left();
	}
	if (direction == 'W'){
		turn_left();
		sensor_forward();
		turn_right();
	}
	if (direction == 'N'){
		sensor_forward();
	}
	if (direction == 'S'){
		sensor_backward();
	}
}