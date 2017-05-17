#include <stdio.h>
#include "maze.h"

/*intro:
this mp is to find a path for a maze by first find the starting point of the maze, solve the path using recursion, and check if the path is vaild or not, and print it*/

/*
 * findStart -- finds the x and y location of the start of the  maze
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- pointer to where x location should be stored
 *              y -- pointer to where y location should be stored
 * OUTPUTS: x and y will hold the values of the start
 * RETURN: none
 * SIDE EFFECTS: none
 */ 
void findStart(char ** maze, int width, int height, int * x, int * y)
{
int i, j,find=0;
char search;
for (i=0;i<height;i++) /* when i and j are inside the maze, increments*/
 {
 for (j=0;j<width;j++)
  {
   search=maze[i][j]; /* if there is a in the maze*/
   if(search == 'S')
   {
    *x=j; /* store the location into x and y as i and j*/
    *y=i;
     find++; /* set find to 1 when find S*/
   }
  }
 }
if (find == 0)
{
*x = -1;
*y = -1;
}
}

/*
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze 
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
void printMaze(char ** maze, int width, int height)
{
int i,j;
for (i=0;i<height;i++) /* while i and j is smaller than the width and height of the maze, increments*/
{
 for (j=0;j<width;j++)
 {
  printf("%c",maze[i][j]); /* print the maze*/
 }
printf("\n");
}
}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the current x position within the maze
 *                 yPos -- the current y position within the maze
 * OUTPUTS:        updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:        0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:   none
 */ 
int solveMazeDFS(char ** maze, int width, int height, int xPos, int yPos)
{
 if (xPos<0||yPos<0||xPos>(width-1)||yPos>(height-1)) /* if (x,y) is outside bounds of the maze return false*/
 {
 return 0;
 }
 if (maze[yPos][xPos] == 'E') /* if (x,y) is the end of the maze retun ture*/
 {
 return 1;
 }
 if (maze[yPos][xPos] != 'S' && maze[yPos][xPos] != ' ') /* if (x,y) is not an empty cell return false*/
 {
 return 0;
 }



 if (maze[yPos][xPos] == ' ') /* if (x,y) is space, fill in with '.'*/
 {
 maze[yPos][xPos] = '.';
 }

 if (solveMazeDFS(maze,width,height,xPos-1,yPos)==1) /* if left of the (x,y) is ture, return true*/
 {
 return 1;
 }
 if (solveMazeDFS(maze,width,height,xPos+1,yPos)==1) /* if right of the (x,y) is ture, return true*/
 {
 return 1;
 }
 if (solveMazeDFS(maze,width,height,xPos,yPos+1)==1) /* if up of the (x,y) is ture, return true*/
 {
 return 1;
 }
 if (solveMazeDFS(maze,width,height,xPos,yPos-1)==1) /* if down of the (x,y) is ture, return true*/
 {
 return 1;
 }

 if (maze[yPos][xPos] != 'S') /* unmark (x,y) as part of solution and mark as visited*/
 {
 maze[yPos][xPos] = '~';
 }

return 0;
}

/*
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */ 
int checkMaze(char ** maze, int width, int height, int x, int y)
{
int i,j;
for (i=0;i<height;i++) /* while inside the maze,*/
{
 for (j=0;j<width;j++)
 {

  int possible_dot=0; /* for the path to be true, if and only if there are two dots around the current dot*/
  if (maze[i][j] == '.') /* if the current location is a dot*/
  {
   if(maze[i+1][j] == '.' || maze[i+1][j] == 'S' || maze[i+1][j] == 'E') /* if right of this dot is a dot, increments possible_dot*/
   {
    possible_dot++;
   }
   if(maze[i-1][j] == '.' || maze[i-1][j] == 'S' || maze[i-1][j] == 'E') /* if left of this dot is a dot, increments possible_dot*/
   {
    possible_dot++;
   }
   if(maze[i][j+1] == '.' || maze[i][j+1] == 'S' || maze[i][j+1] == 'E') /* if up of this dot is a dot, increments possible_dot*/
   {
    possible_dot++;
   }
   if(maze[i][j-1] == '.' || maze[i][j-1] == 'S' || maze[i][j-1] == 'E') /* if down of this dot is a dot, increments possible_dot*/
   {
    possible_dot++;
   }
   if (possible_dot == 2) /* if the possible_dot is 2, then it is a vaild path*/
   {
    return 1; 
   }
  }
 }
}
    return 0;
}

/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */
int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
    return 0;
}

/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */ 
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}

