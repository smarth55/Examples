/*Filename: deprec.c *
*Created By: Ryan Paulsen *
*Created On: 5/14/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/14/2012 *
*/

#include <stdio.h>

int main() {
  /* Variables for the input */
  float price, annual, value;
  int years;
  
  /* Get the input from the user */
  printf("Enter the purchase price, years of service, annual depreciation:\n");
  scanf("%f %d %f", &price, &years, &annual);
  
  /* Calculate the value and print */
  value = -((years*annual)-price);
  printf("The salvage value of the item is %f\n",value);
  
  return(0);
}
