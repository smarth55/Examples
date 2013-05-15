/*Filename: StructsLlist.c *
*Created By: Ryan Paulsen *
*Created On: 5/29/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/29/2012 *
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* Structure for a person */
struct person {         /* "person" is name for structure type */
  char first[32];       /* first field of structure is array of char */
  char last[32];        /* second field is array of char */
  int year;             /* third field is int */
  double ppg;           /* fourth field is double */
};

/*Basic linked list example .. interactive*/
struct NODE {
  int number;
  struct NODE *next;
};

/* Declare function prototypes */
int structs_function();
void display_stats();
void linked_lists();
void append_node(struct NODE *llist, int num);
void delete_node(struct NODE *llist, int num);
int  search_value(struct NODE *llist, int num);
void display_list(struct NODE *llist);    

/* MAIN */
int main() {
  structs_function();
  linked_lists();
  return (0);
}

/* Example of an array of structs */
int structs_function() {
  /* array of "person" structs */
  struct person class[7];
  
  /* Fill class with structs */
  class[0].year=2004; 
  class[0].ppg=5.2;
  strcpy(class[0].first,"Jane");
  strcpy(class[0].last,"Doe");
  
  class[1].year=2012; 
  class[1].ppg=6;
  strcpy(class[1].first,"Ryan");
  strcpy(class[1].last,"Paulsen");
  
  class[2].year=2008; 
  class[2].ppg=4;
  strcpy(class[2].first,"Link");
  strcpy(class[2].last,"Dog");
  
  class[3].year=2010; 
  class[3].ppg=5;
  strcpy(class[3].first,"Aiko");
  strcpy(class[3].last,"Dog");
  
  class[4].year=2006; 
  class[4].ppg=4.8;
  strcpy(class[4].first,"Yorda");
  strcpy(class[4].last,"Pants");
  
  class[5].year=2002; 
  class[5].ppg=3.6;
  strcpy(class[5].first,"Asuka");
  strcpy(class[5].last,"Cat");
  
  class[6].year=2009; 
  class[6].ppg=4.3;
  strcpy(class[6].first,"Dakota");
  strcpy(class[6].last,"Cat");
  
  /* Display all  of the 'persons' */
  display_stats(class);
}

/* Displaying an array of people */
void display_stats(struct person class[]) {
	int count = 0;
	for (count; count<7; count++) {
		printf("%s, %s: %lf PPG in %d\n", class[count].last, class[count].first, class[count].ppg, class[count].year);
	}
}

void linked_lists() {
  int num = 0;
  int input = 1;
  int retval = 0;
  struct NODE *llist;
   
  /*Intitialing the list using malloc and make sure we have one node 
    and a pointer to the next node */
  /*NOTE: The "->" operator is how we address the two parts of our linked
    list "struct". Below we are initializing the "number" component to "0"
    and the second component, which is the pointer to the next struct, is
    set to NULL.*/
  llist = (struct NODE *)malloc(sizeof(struct NODE));
  llist->number = 0;
  llist->next = NULL;
  
  /*Setup our menu system so we can make some basic changes to the nodes
    in our linked list*/ 
  while(input != 0) {
    printf("\n-- Menu Selection --\n");
    printf("0) Quit\n");
    printf("1) Insert\n");
    printf("2) Delete\n");
    printf("3) Search\n");
    printf("4) Display\n");
    scanf("%d", &input);
    switch(input) {
      /*Exit the menu gracefully */
      case 0: 
        printf("Goodbye ...\n");
        input = 0;
        break;

	  /*Insert a value by creating a node at the end of the list */
      case 1:
        printf("Your choice: 'Insertion'\n");
        printf("Enter the value which should be inserted: ");
        scanf("%d", &num);
        append_node(llist, num);
        break;
      /*Remove a value by removing the node with that value */
      case 2:
        printf("Your choice: 'Deletion'\n");
        printf("Enter the value which should be deleted: ");
        scanf("%d", &num);
        if((retval = search_value(llist, num)) == -1)
          printf("Value '%d' not found\n", num);
        else
          delete_node(llist, num);
        break;
      /*Search for a value, if not found, notify, if found
        state what node "position" it has in the list */
      case 3:
        printf("Your choice: 'Search'\n");
        printf("Enter the value you want to find: ");
        scanf("%d", &num);
        if((retval = search_value(llist, num)) == -1)
          printf("Value '%d' not found\n", num);
        else
          printf("Value '%d' located at position '%d'\n", num, retval);
        break;
      /*Display the current contents of the list */
      case 4:
        printf("You choice: 'Display'\n");
        display_list(llist);
        break;
      /*Catch all unmanaged input and return to menu */
      default:
        printf("That is not a valid menu option\n");
        break;
	} /*end of switch-case */
  } /*end of while loop */
  free(llist); /*BE SURE YOU FREE UP YOUR MALLOC when you are done!!! */
}

/*All the functions that we proto-typed and then called from within our menu */
/*Add/append a node. Have to use malloc and have to "move" pointers */
void append_node(struct NODE *llist, int num) {
  while(llist->next != NULL)
    llist = llist->next;
  llist->next = (struct NODE *)malloc(sizeof(struct NODE));
  llist->next->number = num;
  llist->next->next = NULL;
}
/*Remove a node. Have to use a temp to store pointer if we find the node,
and have to "move" pointers. Note we have to deal with a node in the "middle" 
differently than a node at the "end" DON'T FORGET TO "FREE" */
void delete_node(struct NODE *llist, int num) {
  struct NODE *temp;
  temp = (struct NODE *)malloc(sizeof(struct NODE));
  if(llist->number == num) {
    /* remove the node */
    temp = llist->next;
    free(llist); /*FREE UP THAT MEMORY!! */
    llist = temp;
  } else {
    while(llist->next->number != num)
      llist = llist->next;
    temp = llist->next->next;
    free(llist->next); /*FREE UP THAT MEMORY!! */
    llist->next = temp;
  }   
}
/*Search for a node with a value using basic while loop and increments.*/
int search_value(struct NODE *llist, int num) {
  int retval = -1;
  int i = 1;
  while(llist->next != NULL) {
    if(llist->next->number == num)
      return i;
    else
      i++;
    llist = llist->next;
  }
  return retval;
}
/*Display the current contents of the list */
void display_list(struct NODE *llist) {
  while(llist->next != NULL) {
    printf("%d ", llist->number);
    llist = llist->next;
  }
  printf("%d", llist->number);
}