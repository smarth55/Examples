/*Filename: prime.c *
*Created By: Ryan Paulsen *
*Created On: 5/14/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/14/2012 *
*/

#include <stdio.h>

int main() {
  /* Variables */
  int isPrime, number, counter;
  
  /* Get the number from the user */
  printf("Enter a number to check if it is a prime number:\n");
  scanf("%d", &number);
  
  /* Check if it is prime, set isPrime to 1 if it is */
  for (counter = 2; counter < number/2; counter++)
    {
	  if (number % counter == 0)
	    {
		  isPrime = 0;
		  break;
		}
	  else
	    {
		  isPrime = 1;
		}
	}
  
  /* Report the outcome of the check*/
  switch (isPrime)
    {
	  case 0:
	    printf("The number %d is NOT a prime number\n", number);break;
	  case 1:
	    printf("The number %d is a prime number\n", number);break;
	}
  
  return(0);
}
