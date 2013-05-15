/*Filename: bitwise.c *
*Created By: Ryan Paulsen *
*Created On: 5/23/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/23/2012 *
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

void leftbitshift();
void rightbitshift();
void binaryand();
void binaryor();
void binarynegation();
void binaryxor();
void showbits(int number);

int main() {
  /* Variables for the loop and input */
  int running = 1, input;
  
  while (running == 1) {
    /* Print the menu */
    printf("                Main Menu\n");
	printf("                ---------\n");
	printf("1. Perform Left Bit Shift Operation (one value)\n");
	printf("2. Perform Right Bit Shift Operation (one value)\n");
	printf("3. Perform Binary AND Operation (two values)\n");
	printf("4. Perform Binary OR Operation (two values)\n");
	printf("5. Perform Binary One's Complement (~) Operation (one value)\n");
	printf("6. Perform Binary XOR Operation (two values)\n");
	printf("7. Quit\n");
	
	/* Get input */
	scanf("%i", &input);
	
	/* Use a function base on the input */
	switch(input) {
	  case 1:
	    leftbitshift();break;
	  case 2:
	    rightbitshift();break;
	  case 3:
	    binaryand();break;
	  case 4:
        binaryor();break;
	  case 5:
	    binarynegation();break;
	  case 6:
	    binaryxor();break;
	  case 7:
	    running = 0;break;
	}
	
  }
  return(0);
}
/* Shift bits to the left */
void leftbitshift() {
  /* Variables */
  int number, shift;
  
  /* Get the number and the shift amount */
  printf("\nEnter a base 10 Integer: ");
  scanf("%i", &number);
  printf("\nEnter number of places to shift bit: ");
  scanf("%i", &shift);
  
  /* Print the original number with binary value */
  printf("\n        Entered Integer: ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  
  /* Shift */
  number = number << shift;

  /* Print shifted number with binary value */
  printf("        Left Shifted   : ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  printf("\n");
  
}

/* Shift bits to the right */
void rightbitshift() {
  /* Variables */
  int number, shift;
  
  /* Get the number and the shift amount */
  printf("\nEnter a base 10 Integer: ");
  scanf("%i", &number);
  printf("\nEnter number of places to shift bit: ");
  scanf("%i", &shift);
  
  /* Print the original number with the binary value */
  printf("\n        Entered Integer: ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  
  /* Shift */
  number = number >> shift;

  /* Print the shifted number with the binary value */
  printf("        Left Shifted   : ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  printf("\n");

}

/* Use the AND operator on two Integers */
void binaryand() {
  /* Variables */
  int num1, num2, result;
  
  /* Get the input */
  printf("\nEnter two base 10 Integers, separated by a space: ");
  scanf("%i %i", &num1, &num2);
  
  /* Print the input integers with binary values */
  printf("\n        Entered Integer 1: ");
  showbits(num1);
  printf("(base 10 %i)\n", num1);
  printf("        Entered Integer 2: ");
  showbits(num2);
  printf("(base 10 %i)\n", num2);
  
  /* AND operation */
  result = num1 & num2;
  
  /* Print the result with binary value */
  printf("        AND'ed           : ");
  showbits(result);
  printf("(base 10 %i)\n", result);
  printf("\n");
}

/* Use the OR operation on two Integers */
void binaryor() {
  /* Variables */
  int num1, num2, result;
  
  /* Get the input */
  printf("\nEnter two base 10 Integers, separated by a space: ");
  scanf("%i %i", &num1, &num2);
  
  /* Print the input integers with binary values */
  printf("\n        Entered Integer 1: ");
  showbits(num1);
  printf("(base 10 %i)\n", num1);
  printf("        Entered Integer 2: ");
  showbits(num2);
  printf("(base 10 %i)\n", num2);
  
  /* AND operation */
  result = num1 | num2;
  
  /* Print the result with binary value */
  printf("        OR'ed            : ");
  showbits(result);
  printf("(base 10 %i)\n", result);
  printf("\n");
  
}

/* Binary negation operation */
void binarynegation() {
  /* Variables */
  int number;
  
  /* Get input */
  printf("\nEnter a base 10 Integer: ");
  scanf("%i", &number);
  
  /* Print the original number with the binary value */
  printf("\n        Entered Integer: ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  
  /* Perform negation operation */
  number = ~number;
  
  /* Print the new number with the binary value */
  printf("        ~'ed           : ");
  showbits(number);
  printf("(base 10 %i)\n", number);
  printf("\n");
  
}

/* Binary XOR operation */
void binaryxor() {
  /* Variables */
  int num1, num2, result;
  
  /* Get the input */
  printf("\nEnter two base 10 Integers, separated by a space: ");
  scanf("%i %i", &num1, &num2);
  
  /* Print the input integers with binary values */
  printf("\n        Entered Integer 1: ");
  showbits(num1);
  printf("(base 10 %i)\n", num1);
  printf("        Entered Integer 2: ");
  showbits(num2);
  printf("(base 10 %i)\n", num2);
  
  /* XOR operation */
  result = num1 ^ num2;
  
  /* Print the result with binary value */
  printf("        XOR'ed           : ");
  showbits(result);
  printf("(base 10 %i)\n", result);
  printf("\n");
}

/* Funtion to print binary values */
void showbits(int number) { 
  /* Print the binary value one bit at a time */
  int count;
  for (count=31; count>=0; count--){
    /* Check for the negative */
    if (((number&(1<<count)) >> count) == -1)
	  printf("1");
	else
      printf("%d",(number&(1<<count)) >> count);
  }
  printf(" ");
}