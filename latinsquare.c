/**
 * @file latinsquare.c
 * @brief Latin Square Game Implementation
 *
 * This program implements a Latin square game where players can fill in a grid 
 * while adhering to the rules of the Latin square. Each number must appear exactly 
 * once in each row and column. The program allows users to input values, clear 
 * cells, save their progress, and check for winning conditions.
 *
 * @details
 * The program provides the following functionalities:
 * - Reads a Latin square from a specified input file.
 * - Displays the current state of the Latin square.
 * - Accepts user commands for inserting and clearing values.
 * - Validates user input to ensure compliance with Latin square rules.
 * - Saves the current state of the game to an output file.
 *
 * @author Constantinos Koumas
 * @date 26/09/24
 * @version 1.0
 * @bug No known bugs.
 *
 * @par Example usage:
 * - Compile the program using a C compiler.
 * - Run the executable with the input file name as a command-line argument.

 */
#define N 9

#include <stdio.h>
#include <stdlib.h>

int readLatinSquare(const char *filename, int latinSquare[N][N]);

void displayLatinSquare(int arr[N][N], int size);

void displayInstructionDialogue();

void play(int arr[N][N], int size, int isDispNeeded, char *outFileName);

void writeLatinSquare (int arr[N][N],int size, char *fileNameOut);

/**
 * @brief Writes the current state of the Latin square to a file.
 *
 * This function saves the contents of the given Latin square array 
 * to a specified output file. It writes the size of the square followed 
 * by the elements of the square in a formatted manner.
 *
 * @param arr The Latin square array to be written to the file.
 * @param size The size of the Latin square.
 * @param fileNameOut The name of the file where the Latin square will be saved.
 */
void writeLatinSquare (int arr[N][N],int size, char *fileNameOut){
    FILE *fp = fopen (fileNameOut, "w");
    
    if (fp==NULL) {   //CHECK IF NULL
        printf("Error : Unable to generate file %s to save the game!\n",fileNameOut);
        return;
    }

    //write the latin square size at the first line of the file
    fprintf(fp,"%d\n",size);

    //print the latin square, seperate rows with \n and colunms with space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            
            if (j == size - 1) {
                fprintf(fp, "%d", arr[i][j]);
            } else {
                fprintf(fp, "%d ", arr[i][j]);
            }
        }
        
        fprintf(fp, "\n");
    }

    fclose(fp);

    printf("Saving to %s...\nDone\n",fileNameOut);


}

/**
 * @brief Displays the instructions for user commands.
 *
 * This function prints a set of instructions to the console, 
 * detailing how the user can input commands to interact with 
 * the Latin square game.
 */
void displayInstructionDialogue()
{
    printf("Enter your command in the following format:\n");
    printf("+ i,j=val: for entering val at position (i,j)\n");
    printf("+ i,j=0 : for clearing cell (i,j)\n");
    printf("+ 0,0=0 : for saving and ending the game\n");
    printf("Notice: i,j,val numbering is from [1..4]\n");
}

/**
 * @brief Handles the gameplay mechanics for the Latin square game.
 *
 * This function manages user input and updates the Latin square 
 * based on the commands received. It validates input, checks for 
 * win conditions, and controls the game flow including saving the game.
 *
 * @see displayLatinSquare(int (*arr)[9], int size)
 * @see displayInstructionDialogue()
 * @see writeLatinSquare(int (*arr)[9], int size, char *fileNameOut)
 * 
 * @param arr The Latin square array to be modified.
 * @param size The size of the Latin square.
 * @param isDispNeeded A flag indicating whether to display the square 
 *                     and instructions before taking input.
 * @param outFileName The name of the file to save the game state.
 */
void play(int arr[N][N], int size, int isDispNeeded, char *outFileName)
{
    if (isDispNeeded == 1)
    {
        displayLatinSquare(arr, size);
        displayInstructionDialogue();
    }

    int i, j, val;
    if (scanf("%d,%d=%d", &i, &j, &val) != 3)
    {
        while (getchar() != '\n')
        {
        };
        printf("Error: wrong format of command\n\n");
        play(arr, size, 0,outFileName);
        return; // prevent further execution in case of bad input
    }

    
    
    
    // Check for game termination command (0,0=0)
    if ((i == 0) && (j == 0) && (val == 0))
    {
        writeLatinSquare(arr,size,outFileName);
        return;
    }

    // Check if i, j are within allowed range
    if (((i < 1) || (i > size)) || ((j < 1) || (j > size)) || ((val < 0) || (val > size)))
    {
        printf("Error: i,j or val are outside the allowed range [1..%d]!\n\n", size);
        play(arr, size, 0,outFileName);
        return; // avoid continuing after invalid input
    }

    // Check if the cell is occupied
    if (arr[i - 1][j - 1] != 0)
    {
        // Cell is occupied by a positive or negative value
        if (arr[i - 1][j - 1] < 0)
        {
            // Check if trying to clear a negative value
            if (val == 0)
            {
                printf("Error: illegal to clear cell!\n\n");
                play(arr, size, 0,outFileName);
                return;
            }
        }
        else
        {
            // Cell is occupied by a positive value
            if (val == 0)
            {
                // Clearing the cell
                arr[i - 1][j - 1] = 0;
                printf("\nValue Cleared!\n\n");
                play(arr, size, 1,outFileName);
                return;
            }
            else
            {
                // Trying to insert in an occupied cell
                printf("Error: cell is already occupied!\n\n");
                play(arr, size, 0,outFileName);
                return;
            }
        }
    }

    // Check Latin square rules for duplicate values in row/column
    int areRulesBroken = 0;

    // Check the row for the same value
    for (int t = 0; t < size; t++)
    {
        if (arr[i - 1][t] == 0)
        {
            continue;
        }
        if (abs(arr[i - 1][t]) == val)
        {
            areRulesBroken = 1;
            break;
        }
    }

    // Check the column for the same value
    for (int t = 0; t < size; t++)
    {
        if (arr[t][j - 1] == 0)
        {
            continue;
        }
        if (abs(arr[t][j - 1]) == val)
        {
            areRulesBroken = 1;
            break;
        }
    }

    //print rule violation message
    if (areRulesBroken == 1)
    {
        printf("Error: Illegal value insertion!\n\n");
        play(arr, size, 0,outFileName);
        return;
    }

    // Insert or clear the value
    arr[i - 1][j - 1] = val;
    if (val == 0)
    {
        printf("\nValue Cleared!\n\n");
    }
    else
    {
        printf("\nValue Inserted!\n\n");
    }

    //check whether we have winning conditions
    int isGameWon = 1;   //flag to determine if the game is won or not 1 => WON  , 0 => NOT WON YET 
    
    //if ANT empty cells are found it means the game has yet to be won by the player. 
    for (int i=0;i<size;i++){
        if (isGameWon==0) {
            break;
        }
        for (int j=0;j<size;j++){
            if (arr[i][j]==0){
                isGameWon = 0 ;
                break;
            }
        }
    }

    // game not won => recursion call to play function and start over waiting for new input.
    if (isGameWon==0){
    play(arr, size, 1,outFileName);
    return;
    } else if (isGameWon==1) {    // gama is won because isGameWon = 1 !!! Ending the game and calling writeLatinsquare function to save the game
        printf("Game completed!!!\n");
        displayLatinSquare(arr,size);   //display winning latin square
        writeLatinSquare(arr,size,outFileName);
        return;
    }
}

/**
 * @brief Reads a Latin square from a specified file.
 *
 * This function attempts to read a Latin square from the given file 
 * and populates the provided array. It checks for file accessibility 
 * and validates the input format.
 *
 * @param filename The name of the file to read the Latin square from.
 * @param latinSquare The array to populate with the Latin square data.
 * @return The size of the Latin square if successful, or -1 on error.
 */
int readLatinSquare(const char *filename, int latinSquare[N][N])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)  //check if null and return error code -1
    {
        printf("Error! Unable to access file %s\n", filename);
        return -1;
    }

    int n; // latinsquare user picked size

    //check latin square size legitimacy
    if (fscanf(fp, "%d", &n) != 1 || n <= 0 || n > N)
    {
        printf("Error: Detected invalid size of latin square in the file...\nMaximum size is %d", N);
        fclose(fp);
        return -1;
    }
    
    // first set all values of the array to zero
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            latinSquare[i][j] = 0;
        }
    }

    // Read,check and transfer latinSquare from file to array latinSquare[][]

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(fp, "%d", &latinSquare[i][j]) != 1)
            { // Check if fscanf successfully reads an integer
                printf("Error: Invalid input detected in the Latin square data...\n");
                fclose(fp);
                return -1;
            }
        }
    }

    fclose(fp);
    return n;
}

/**
 * @brief Displays the current state of the Latin square in a formatted manner.
 *
 * This function prints the Latin square to the console, showing 
 * the values in a grid format. Negative numbers are displayed 
 * within parentheses.
 *
 * @param arr The Latin square array to be displayed.
 * @param size The size of the Latin square.
 */
void displayLatinSquare(int arr[N][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Print the top border of the row
        for (int j = 0; j < size; j++)
        {
            printf("+-----");
        }
        printf("+\n");

        // Print the contents of the row
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] < 0)
            {
                // Print negative numbers inside parentheses
                printf("| (%d) ", abs(arr[i][j]));
            }
            else
            {
                // Print zeros and positive numbers as they are
                printf("|  %d  ", arr[i][j]);
            }
        }
        printf("|\n");
    }

    // Print the bottom border of the last row
    for (int j = 0; j < size; j++)
    {
        printf("+-----");
    }
    printf("+\n");
}

/**
 * @brief Main function to run the Latin square game.
 *
 * This function serves as the entry point of the program. It 
 * processes command-line arguments to obtain the input file name, 
 * reads the Latin square from the file, and starts the gameplay 
 * loop.
 *
 * @see readLatinSquare(const char *filename, int (*latinSquare)[9])
 * @see play(int (*arr)[9], int size, int isDispNeeded, char *outFileName)
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return Exit status code: 0 on success, non-zero on error.
 */
int main(int argc, char *argv[])
{
    //check if no input file was provided
    if (argc < 2)
    {
        printf("Usage: %s <filename>\nError code: 1 => FileName not provided \n", argv[0]);
        return 1;
    }

    //Initialize latin square array with 0
    int latinSquare[N][N] = {0};

    //call function to read latin square date from file 
    int n = readLatinSquare(argv[1], latinSquare);

    //if -1 is returned, print message saying something went wrong while reading the file
    if (n == -1)
    {
        printf("Error: Something went wrong while reading the file %s\n", argv[1]);
        return 0;
    }

     // Generate the output file name dynamically
    char outFileName[50];
    snprintf(outFileName, sizeof(outFileName), "out-%s", argv[1]);

    // start the gameplay loop
    play(latinSquare, n, 1,outFileName);

    //successdfull execution code
    return 0;
}
