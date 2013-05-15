/*Filename: strings.c *
*Created By: Ryan Paulsen *
*Created On: 5/16/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/16/2012 *
*/

#include <stdio.h>
#include <string.h>

void strings() {
  char mystring[11];
  char secondstring[10];
  int length;
  
  mystring[0]='G'; mystring[1]='r'; mystring[2]='e'; mystring[3]='e'; mystring[4]='t';
  mystring[5]='i'; mystring[6]='n'; mystring[7]='g'; mystring[8]='s'; mystring[9]='!';
  mystring[10]='\0';
  
  secondstring[0]='U'; secondstring[1]='n'; secondstring[2]='i'; secondstring[3]='v'; secondstring[4]='e';
  secondstring[5]='r'; secondstring[6]='s'; secondstring[7]='e'; secondstring[8]='!'; secondstring[9]='\0';
  
  printf("My first string says: %s\n",mystring);
  
  length = strlen(mystring);
  
  printf("The first string length is %i\n", length);
  
  int compare;
  
  compare = strcmp(mystring, secondstring);
  
  printf("The return value for comparing mysting to secondstring is: %i\n", compare);
  if (compare==0) {
    printf("not equal");
  }
  compare = strcmp(mystring, mystring);
  
  printf("The return value for comparing mystring to itself is: %i\n", compare);
  if (compare==0) {
	printf("equal");
  }
  //strcpy(copystring, mystring);
  
  //printf("My first string copy says: %s\n", copystring);
  
  //strcat(copystring, secondstring);
  
  //print strcat
  
}

void twodarray() {
  int a[3][2];
  a[0][1] = 7;
  a[1][0] = 14;
  
  printf("My 2d array prints out as: a[0][1] = %i, a[1][0] = %i", a[0][1],a[1][0]);
}

int main() {
  strings();
  return(0);
}