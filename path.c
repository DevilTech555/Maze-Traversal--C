/* Dillon Mabry Student ID: 800854402 */
#include <stdio.h>

int canMove(char array[200][200],int x, int y);
void printMaze(char array[200][200], int rows, int cols);

main()
{
  /* generate user input for displaying maze */
  int rows, cols;
  printf("Enter the row size:\n");
  scanf("%d",&rows);
  printf("Enter the column size:\n");
  scanf("%d",&cols);

  /* generate fixed 2D array size of 200x200 to display maze */
  char field[200][200]={0};

  FILE *fptr;
  char c;
  char file_name[20];
  int i,j;
  int start_x, start_y;
  
  /* begin file parsing and input ASCII file */
  printf("Type in the name of the file containing the Field\n");
  scanf("%s",file_name);
  fptr=fopen(file_name,"r");
  for (i=0; i<rows; i++) 
    for (j=0; j<cols; j++){
        c=fgetc(fptr); 
        while ( !((c == '1')||(c =='0')) ) c=fgetc(fptr);
            field[i][j]=c;
    } /* end maze setup and finding startX, startY locations */

    fclose(fptr);
    
    /* traverse across 2D array left side, bottom, right, then top finding
    the entrance point */
	i=rows-1; 
	for (j=cols-1; i>0; i--){
		if (field[i][j] == '0'){
		 	start_x = i;
		 	start_y = j;         
			break;
		}
	} /* end right side traverse */
		
	j=cols-1; 
	for (i=0; j>0; j--){
		if (field[i][j] == '0'){
			start_x = i;
			start_y = j; 
		 	break;
		}
	} /* end top traverse */
			
	for(j=0; i < rows-1; i++) {
		if(field[i][j] == '0') {    
		 	start_x = i;
		 	start_y =j;
		 	break;
		}
	} /* end left side traverse */
			
	j=1; 
	for (i=rows-1; j<cols-1; j++){
		if (field[i][j] == '0'){
		 	start_x = i;
			start_y = j;        
			break;
		}
	} /* end bottom traverse */
      
    printf("Entrance is at:[%d][%d]\n", start_x, start_y);
      
    /* if pointer can move then print field, otherwise print the
    field anyway to display results */
    if(canMove(field, start_x,start_y)) {
        /* print maze */
        printMaze(field, rows, cols);
      } else {
          /* print maze */
        printMaze(field, rows, cols);
      }
      
	/* create counter to keep track of if the maze has an 
      entry or exit point, if the maze has both an entry and exit return 
      solution found display, else return no solution */
      int count;
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)  {
            if ( j == 0 && field[i][j] == 'X') {
                    count+=1;
            } else if (i == rows-1 && field[i][j]=='X') {
                    count+=1;
            } else if (j == cols-1 && field[i][j]=='X') {
                    count+=1;
            } else if( i==0 && field[i][j] == 'X') {
                    count+=1;
            } else {
                    //do nothing
            }
        }
    
    if(count>1) {
        printf("Solution found!\n");
    } else {
        printf("No solution!\n");
    }
 
    return 0;
      
} /* end of main function */

/* Function to determine if a path is available to move by placing
a character symbol of 'X' over the traversed paths. If a path is found 
return 1 otherwise return 0. If the path successfully exits the bounds
of the generated 2D array (200x200) then return 1 */
int canMove(char array[200][200],int x, int y) {

    /* set symbol for traversing paths */
    array[x][y]='X';
    
    /* for troubleshooting*/
    // printf("x: %d | y: %d\n", x, y);
    
    /* series of checks to determine counter-clockwise if a 
    path is open then move forward */
    if(array[x][y+1] == '0' && canMove(array, x, y+1)) {
        return 1;
    } else if(array[x+1][y] == '0' && canMove(array, x+1, y)) { 
        return 1;
    } else if(array[x][y-1] == '0' && canMove(array, x, y-1)) {
        return 1;
    }  else if(array[x-1][y] == '0' && canMove(array, x-1, y)) {
        return 1;
    /* else backtrack and return false */
    } else {
        array[x][y]='X';
        return 0;
    }
} 

/* Function to display the desired maze size based on user input of
rows and columns */
void printMaze(char array[200][200], int rows, int cols) {
    int i,j;
    for (i=0; i<rows; i++)
            for (j=0; j<cols; j++)  {
                if (j == 0) printf("\n");                
            printf("%c  ", array[i][j]);
        }
        printf("\n");
}

