/*Filename: harmonic.c *
*Created By: Ryan Paulsen *
*Created On: 5/14/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/14/2012 *
*/

#include <stdio.h>

int main() {
  /* Variables */
  int number;
  float harmonic, counter;
  
  /* Initialize to 0 */
  number = 0;
  
  /* Get the number from the user */
  printf("Enter a value to calculate the value of this harmonic series:\n");
  while (number <= 0)
    {
	scanf("%d", &number);
	  if (number < 0)
	    printf("Please enter a POSITIVE number:\n");
    } 
  
  /* Calculate the harmonic series */
  for (counter = 1.0; counter <= number; counter++)
    {
	  harmonic += 1/counter;
	}
  
  /* Print the value of the series */
  printf("The value for the series is: %f\n", harmonic);
  
  return(0);
}
