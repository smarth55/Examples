/*Filename: ArraysMatricesCalc.c *
*Created By: Ryan Paulsen *
*Created On: 5/17/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/17/2012 *
*/

#include <stdio.h>

/* This function gets two arrays from the user and prints the 
intersection and the union of the arrays. */
void arraycompare() {
  /* Variables */
  int size, count, count2;
  
  /* Get the size of the arrays */
  printf("Enter the size of the arrays:\n");
  scanf("%d", &size);
  int ary1[size], ary2[size], aunion[size+size];
  
  /* Get the elements in the arrays - ary1 first then ary2 */
  printf("Enter the elements of the first array:\n");
  for (count=0; count<size; count++) {
    scanf("%d", &ary1[count]);
  }
  
  printf("Enter the elements of the second array:\n");
  for (count=0; count<size; count++) {
    scanf("%d", &ary2[count]);
  }
  
  /* Print the intersection of the arrays */  
  printf("The intersection of two arrays is: ");
  for (count=0; count<size; count++) {
    for (count2=0; count2<size;count2++) {
	  if (ary1[count] == ary2[count2]) {
	    printf("%d", ary1[count]);
	  }
	}
  } 
  printf("\n");
  
  /* Print the union of the arrays - this could be cleaner, but it works */
  printf("The union of two arrays is: ");
  int contains = 0, pos = 0;
  for (count=0;count<size;count++) {
    for (count2=0;count2<size*2;count2++) {
	  if (ary1[count] == aunion[count2]) {
	    contains = 1;
		break;
	  }
	}
	if (contains == 0) {
	  printf("%d",ary1[count]);
	  aunion[pos] = ary1[count];
	  pos++;
	} else {
	  contains = 0;
	}
  }
  for (count=0;count<size;count++) {
    for (count2=0;count2<size*2;count2++) {
	  if (ary2[count] == aunion[count2]) {
	    contains = 1;
		break;
	  }
	}
	if (contains == 0) {
	  printf("%d",ary2[count]);
	  aunion[pos] = ary2[count];
	  pos++;
	} else {
	  contains = 0;
	}
  }   
  printf("\n");
}

/* This function takes a two-dimensional array and transposes it */
void invertmatrix(int m[4][5], int n[5][4]) {
  /* Take the values of m and put them in n */
  int row, col;
  for (row=0; row<4; row++) {
    for (col=0; col<5; col++) {
	  n[col][row] = m[row][col];
	}
  }
  
  /* Print the original matrix */
  printf("The original matrix was: \n");
  for (row=0; row<4; row++) {
    for (col=0; col<5; col++) {
	  printf("%d ", m[row][col]);
	}
	printf("\n");
  }
  
  /* Print the transposed array */
  printf("The transposed matrix is: \n");
  for (row=0; row<5; row++) {
	for (col=0; col<4; col++) {
	  printf("%d ", n[row][col]);
	}
	printf("\n");
  }
}

/* A simple calculator function */
void calculator() {
  float acc=0.0,number=0.0;
  char opr;
  printf("Initialize your Accumulator with data of the form\n \"number\" \"S\" which sets the Accumulator to the value of your number\n");
  scanf("%f %c", &number, &opr);
  while (opr != 'E') {
    if (opr == 'S') { //Restart with new value
	  acc = number;
	} else if (opr == '+') { //Addition
	  acc += number;
	} else if (opr == '-') { //Subtraction
	  acc -= number;
	} else if (opr == '*') { //Multiplication
	  acc *= number;
	} else if (opr == '/') { //Division
	  if (number == 0) {
	    printf("Can not divide by 0.\n");
	  } else {
	    acc /= number;
	  }
	} else {
	  printf("Unknown Operator.\n");
	}
    /* Print the new value and repeat */
	printf("Value in the Accumulator = %f\n", acc);
	scanf("%f %c", &number, &opr);
  }
  printf("Value in the Accumulator = %f\n", acc);
  printf("End of Calculations.\n");
}

int main() {
  /* Compare two arrays */
  arraycompare();
  printf("\n\n");
  
  /* Invert a matrix */
  int matrixM[4][5] = {{1,2,3,4,5},{6,7,8,9,10},{10,9,8,7,6},{5,4,3,2,1}};
  int matrixN[5][4];
  invertmatrix(matrixM, matrixN);
  printf("\n\n");
    
  /* Calculator */
  calculator();
  return(0);
}