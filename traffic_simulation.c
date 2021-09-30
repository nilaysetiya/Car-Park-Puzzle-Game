#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define SPACE 0
#define WALL -1
#define EXIT -2

// Your function definitions should go here...
void InitialiseRoad(int road[NUM_ROWS][NUM_COLS], char side, int pos)
{

	int i;
	int j;
	int a;
	int b;

	// This nested for loop makes every space in the array a 0.
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {
			road[i][j] = SPACE;
		}
	}

	// This for loop creates the north and south walls.
	for (a = 0; a < NUM_COLS; a++) {
		road[0][a] = WALL;
		road[NUM_ROWS - 1][a] = WALL;
	}

	// This for loop creates the east and west walls.
	for (b = 0; b < NUM_ROWS; b++) {
		road[b][0] = WALL;
		road[b][NUM_COLS - 1] = WALL;
	}

	// These series of if statements prints out the exit on the specified wall.
	if (side == 'N') { // North wall
		road[0][pos] = EXIT;
	}
	else if (side == 'S') { // South wall
		road[NUM_ROWS - 1][pos] = EXIT;
	}
	else if (side == 'E') { // East wall
		road[pos][NUM_COLS - 1] = EXIT;
	}
	else if (side == 'W') { // West wall
		road[pos][0] = EXIT;
	}
}

void PrintRoad(int road[NUM_ROWS][NUM_COLS])
{
	int i, j;

	// This nested for loop goes through the whole road array and prints out
	// the spaces, walls, car letters, and exit.
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {
			if (road[i][j] == WALL) { // Prints the wall
				printf("#");
			}
			else if (road[i][j] == SPACE) { // Prints the spaces
				printf(" ");
			}
			else if (road[i][j] == EXIT) { // Prints the exit
				printf("O");
			}
			else if (road[i][j] >= 65 && road[i][j] <= 90) { // Prints the car letters
				printf("%c", road[i][j]);
			}
		}
		printf("\n"); // Prints a new line for each row
	}

}

double PercentUsed(int road[NUM_ROWS][NUM_COLS])
{
	double area;
	int i, j;
	int count = 0;
	double percentage;

	// Calculates the total road area. This excludes the walls on all sides.
	area = (NUM_ROWS - 2) * (NUM_COLS - 2);

	// This nested for loop goes through array and checks how many spaces are left.
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			if (road[i][j] != SPACE) { // Counts the number of spaces occupied by cars
				count++; 
			}
		}
	}

	percentage = (count / area) * 100; // Calculates the percentage of road used
	return percentage; // Returns the value of percentage.
}

void AddCar(int road[NUM_ROWS][NUM_COLS], int row, int col, int size)
{
	char letter = 'A';
	int i, j;
	int a, b, c, d, test1 = 0, test2 = 0;

	// This nested for loop goes through the array to find the highest letter for a car.
	// Once the highest letter is found, it adds one to that letter to get the next letter for
	// the new car being added.
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			if (road[i][j] >= letter && road[i][j] >= 65 && road[i][j] <= 90) {
				letter = (char)road[i][j] + 1;
			}
		}
	}
	
	// These two if statements add the car onto the road depending on if the car needs to be
	// vertical or horizontal.
	if (size > 0) { // If the car being added needs to be horizontal
		for (a = 0; a < size; a++) {

			// Checks for collisions before adding the car to make sure there is enough 
			// space for the car being added.

			if (road[row][col + a] == SPACE) {  
				test1++;                 
			}

			for (c = 0; c < size; c++) { 

				// If there is enough spaces and no collisions, this for loop prints the car.
				// This if statement makes sure the car is not printed on a wall or exit and is only
				// printed on SPACES.

				if (size == test1 && road[row][col + c] != WALL && road[row][col + c] != EXIT) {
					road[row][col + c] = letter;
				}
			}

		}
	}
	else if (size < 0) { // If the car being added needs to be vertical
		size = size * -1;
		for (b = 0; b < size; b++) {

			// Checks for collisions before adding the car to make sure there is enough 
			// space for the car being added.
			if (road[row + b][col] == SPACE) { 
				test2++;                
			}

			for (d = 0; d < size; d++) {

				// If there is enough spaces and no collisions, this for loop prints the car.
				// This if statement makes sure the car is not printed on a wall or exit and is only
				// printed on SPACES.

				if (size == test2 && road[row + d][col] != WALL && road[row + d][col] != EXIT) {
					road[row + d][col] = letter;
				}
			}
		}
	}

}

void FindCar(int road[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart, int* rowEnd, int* colEnd)
{
	int i, j;
	int first = 0;

	// This nested for loop goes through the array to find the first and last position of the car and store
	// those positions in variables rowStart, colStart, rowEnd, colEnd
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			if (road[i][j] == move && first == 0) { // Finds the first position of the car
				*rowStart = i;
				*colStart = j;
				first = 1;
			}
			else if (road[i][j] == move) { // Finds the last position of the car
				*rowEnd = i;
				*colEnd = j;
			}
		}
	}
}


int MoveCar(int road[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1)
{
	char letter = (char)road[r0][c0];
	int size = 0;
	int i, j;
	int a = 1, b = 1, c = 1, d = 1;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	int r_exit = 0, c_exit = 0;
	int m, n;

	// This nested for loop goes through the array to find the size of the car beign moved
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			if (road[i][j] == letter) {
				size++;
			}
		}
	}

	if (r0 == r1) { // Determines that the car being moved is horizontal

		if (road[r0][c0 - 1] == SPACE) { // Checks if there is space on the left

			for (i = 0; i < size; i++) { // This for loop replaces the car being moved with spaces
				road[r0][c0 + i] = SPACE;
			}
			while (road[r0][c0 - a] == SPACE) { // Counts the number of spaces the car needs to be moved
				count1++;
				a++;
			}
			c0 = c0 - count1; // Changes the starting position of the car depending on the number of spaces

			for (j = 0; j < size; j++) { // This for loop reprints the car in its new (moved) location
				road[r0][c0 + j] = letter;
			}
		}
		else if (road[r0][c1 + 1] == SPACE) { // Checks if there is space on the right

			for (i = 0; i < size; i++) { // This for loop replaces the car being moved with spaces
				road[r0][c0 + i] = SPACE;
			}
			while (road[r0][c1 + b] == SPACE) { // Counts the number of spaces the car needs to be moved
				count2++;
				b++;
			}
			c0 = c0 + count2; // Changes the starting position of the car depending on the number of spaces

			for (j = 0; j < size; j++) { // This for loop reprints the car in its new (moved) location
				road[r0][c0 + j] = letter;
			}
		}
	}
	else if (c0 == c1) { // Determines that the car being moved is vertical 

		if (road[r0 - 1][c0] == SPACE) { // Checks if there are spaces above

			for (i = 0; i < size; i++) { // This for loop replaces the car being moved with spaces
				road[r0 + i][c0] = SPACE;
			}
			while (road[r0 - c][c0] == SPACE) { // Counts the number of spaces the car needs to be moved
				count3++;
				c++;
			}
			r0 = r0 - count3; // Changes the starting position of the car depending on the number of spaces

			for (j = 0; j < size; j++) { // This for loop reprints the car in its new (moved) location
				road[r0 + j][c0] = letter;
			}
		}
		else if (road[r1 + 1][c0] == SPACE) { // Checks if there are spaces underneath

			for (i = 0; i < size; i++) { // This for loop replaces the car being moved with spaces
				road[r0 + i][c0] = SPACE;
			}
			while (road[r1 + d][c0] == SPACE) { // Counts the number of spaces the car needs to be moved
				count4++;
				d++;
			}
			r0 = r0 + count4; // Changes the starting position of the car depending on the number of spaces

			for (j = 0; j < size; j++) { // This for loop reprints the car in its new (moved) location
				road[r0 + j][c0] = letter;
			}
		}
	}

	// This nested for loop goes through the whole road array in order to find the positions of the exit
	for (m = 0; m < NUM_ROWS; m++) {
		for (n = 0; n < NUM_COLS; n++) {
			if (road[m][n] == EXIT) {
				r_exit = m;
				c_exit = n;
			}
		}
	}

	// This nested for loop goes through the whole road array in order to check if the car being moved is 
	// aligned with the exit and returns 1.
	for (m = 0; m < NUM_ROWS; m++) {
		for (n = 0; n < NUM_COLS; n++) {

			// Checks if the car is aligned with the exit on the east wall
			if (c_exit == NUM_COLS - 1 && road[r_exit][c_exit - 1] == letter && road[r_exit][c_exit - 2] == letter) {
				return 1;
			}
			// Checks if the car is aligned with the exit on the west wall
			else if (c_exit == 0 && road[r_exit][c_exit + 1] == letter && road[r_exit][c_exit + 2] == letter) {
				return 1;
			}
			// Checks if the car is aligned with the exit on the north wall
			else if (r_exit == 0 && road[r_exit + 1][c_exit] == letter && road[r_exit + 2][c_exit] == letter) {
				return 1;
			}
			// Checks if the car is aligned with the exit on the south wall
			else if (r_exit == NUM_ROWS - 1 && road[r_exit - 1][c_exit] == letter && road[r_exit - 2][c_exit] == letter) {
				return 1;
			}
		}
	}

	// Returns 0 if the moved car is not aligned with the exit
	return 0;
}


/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove car: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Traffic Jam simulation */
int main(void)
{
	int gameOver = 0;
	int road[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf(" _____           __  __ _            _                                        \n");
	printf("|_   _| __ __ _ / _|/ _(_) ___      | | __ _ _ __ ___           ____          \n");
	printf("  | || '__/ _` | |_| |_| |/ __|  _  | |/ _` | '_ ` _ \\  --   __/  |_\\_      \n");
	printf("  | || | | (_| |  _|  _| | (__  | |_| | (_| | | | | | | --- |  _     _``-.    \n");
	printf("  |_||_|  \\__,_|_| |_| |_|\\___|  \\___/ \\__,_|_| |_| |_| --  '-(_)---(_)--'\n\n");

	/* Initialise the road and add cars */
	InitialiseRoad(road, 'E', 3);
	AddCar(road, 3, 3, 2);
	AddCar(road, 1, 1, 2);
	AddCar(road, 2, 1, 3);
	AddCar(road, 3, 2, -2);
	AddCar(road, 5, 2, -2);
	AddCar(road, 4, 4, -2);
	AddCar(road, 6, 3, 3);
	AddCar(road, 1, 5, -3);
	AddCar(road, 2, 6, -2);

	/* Print status */
	printf("ENGGEN131 2020 - C Project\nTraffic Jam!  There is a lot of traffic on the road!\n");
	printf("In fact, %.2f%% of the road is cars!\n\n", PercentUsed(road));

	/* Main simulation loop */
	while (!gameOver) {
		PrintRoad(road);
		input = GetMove();
		FindCar(road, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveCar(road, rowStart, colStart, rowEnd, colEnd);
	}

	/* A car has exited - the simulation is over */
	PrintRoad(road);
	printf("\nCongratulations, you're on your way again!");

	return 0;
}
