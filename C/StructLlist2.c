/*Filename: StructLlist.c *
*Created By: Ryan Paulsen *
*Created On: 5/30/2012 *
*Last Modified By: Ryan Paulsen *
*Last Modified On: 5/30/2012 *
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* Structures */
struct player {
  char name[32];
  char team[32];
  float avg;
};

struct NODE {
  int number;
  struct NODE *next;
};

/* Prototypes */
void cricket();
void linkedlist();
void insert_end(struct NODE *llist, int num);
void insert_front(struct NODE *llist, int num);
void delete_end(struct NODE *llist);
void delete_front(struct NODE *llist);
void insert_mid(struct NODE *llist, int num, int val);
void delete_mid(struct NODE *llist, int val);
void modify(struct NODE *llist, int num, int new);
void display_list(struct NODE *llist);

/* MAIN */
int main() {
  /* Input variable */
  int input = 1;
  
  /* Main Menu */
  while (input != 0) {
    printf("\n-- Main Menu --\n");
	printf("0) Exit Program\n");
	printf("1) Cricket\n");
	printf("2) Linked Lists\n");
	scanf("%d", &input);
	switch(input) {
	  case 0:
	    printf("Goodbye...\n"); /* Exit */
		input = 0;break;
	  case 1:
	    printf("\n-- CRICKET --\n"); /* Cricket Program */
	    cricket();break;
	  case 2:
	    printf("\n-- LINKED LISTS --\n"); /* Linked Lists Program */
	    linkedlist();break;
	  default:
	    printf("That is not a valid option.\n"); /* Catch invalid inputs */
		break;
	}
  }
  return(0);
} 
/*END MAIN*/

/* Cricket Program */
void cricket() {
  /* Variables */
  int numteams, numplayers, count, count2;
  char teams[5][32];
  
  /* Get number of teams */
  printf("\nEnter the number of teams you wish to record: ");
  scanf("%d", &numteams);
  
  /* Get names of the teams */
  for (count=0; count<numteams; count++) {
    printf("Enter the name(s) of the teams: ");
	scanf("%s", &teams[count]);
  }
  
  /* Get number of total players */
  printf("Enter the TOTAL number of players for all teams: ");
  scanf("%d", &numplayers);
  struct player players[numplayers]; /* Array of players */
  for (count=0; count<numplayers; count++) {
    /* Create new player and add them to the player array */
    struct player plyr; 
    printf("Enter the %d Player name, Team name, and batting average: ", count+1);
	scanf("%s %s %f", &plyr.name, &plyr.team, &plyr.avg);
	players[count] = plyr;
  }  
  
  /* Print the players in groups based on their teams */
  for (count=0; count<numteams; count++) {
    printf("%s-\n",teams[count]);
	for (count2=0; count2<numplayers; count2++) {
	  if (strcmp(players[count2].team, teams[count]) == 0) {
	    printf("\t%s \t%f\n", players[count2].name, players[count2].avg);
	  }
	}
  }
}

void linkedlist() {
  /* Variables */
  int input=0, num=0, new=0, val=0;
  struct NODE *llist;
  
  llist = (struct NODE *)malloc(sizeof(struct NODE));
  llist->number = 0;
  llist->next = NULL;

  printf("This Program initializes a link list.\n");
  printf("It starts out empty, so the first thing you probably\n want to do is insert a node.\n\n");
  printf("Please note: This program is designed to accept integer values only.\n");
  
  /* Main Menu */
  while (input != 8) {
    printf("\nPlease enter you choice\n");
    printf("1. INSERT a node at the END of linklist\n");
    printf("2. INSERT a node at the BEGINNING of linklist\n");
    printf("3. DELETE a node at the END of linklist\n");
    printf("4. DELETE a node at the BEGINNING of linklist\n");
    printf("5. INSERT a node in the MIDDLE of linklist\n");
    printf("6. DELETE a node from the MIDDLE of linklist\n");
    printf("7. MODIFY any node in linklist\n");
    printf("8. EXIT\n");
    scanf("%d", &input);
    switch(input) {
      case 1:
	    /*insert_end*/
		printf("Enter your node in the list\n");
		scanf("%d", &num);
		insert_end(llist, num);
		display_list(llist);
	    break;
	  case 2:
	    /*insert_front*/
		printf("Enter the value for the node you want to insert at the beginning\n");
		scanf("%d", &num);
		insert_front(llist, num);
		display_list(llist);
	    break;
	  case 3:
	    /*delete_end*/
		delete_end(llist);
		display_list(llist);
	    break;
	  case 4:
	    /*delete_front*/
		delete_front(llist);
		display_list(llist);
	    break;
	  case 5:
	    /*insert_mid*/
		printf("Enter the value of the node after which you want to insert a new node\n");
		scanf("%d", &val);
		printf("Enter the value of the new node\n");
		scanf("%d", &num);
		insert_mid(llist, num, val);
		display_list(llist);
	    break;
	  case 6:
	    /*delete_mid*/
		printf("Enter the value of the node that precedes the node you want to delete\n");
		scanf("%d", &val);
		delete_mid(llist, val);
		display_list(llist);
	    break;
	  case 7:
	    /*modify*/
		printf("Enter the value of the node you want to modify\n");
		scanf("%d", &num);
		printf("Enter the new value for this node\n");
		scanf("%d", &new);
		modify(llist, num, new);
		display_list(llist);
	    break;
	  case 8:
	    /*exit*/
		printf("Goodbye ...\n");
        input = 8;
	    break;
	  default:
	    /*invalid*/
	    printf("That is not a valid option.\n");
	    break;
    }
  }
  free(llist);
}

/* Insert a node at the end of the list */
void insert_end(struct NODE *llist, int num) {
  if (llist->next == NULL) {
    llist->next = (struct NODE *)malloc(sizeof(struct NODE));
	llist->next->next = NULL;
	llist->number = num;
  } else {
    while (llist->next != NULL) {
	  llist = llist->next;
	}
	llist->next = (struct NODE *)malloc(sizeof(struct NODE));
	llist->next->next = NULL;
	llist->number = num;
  }
}

/* This is supposed to insert a node at the beginning of the list */
void insert_front(struct NODE *llist, int num) {
  struct NODE *new;  
  new=(struct NODE *)malloc(sizeof(struct NODE));  
  new->number = llist->number;
  new->next = llist->next;
  llist->number = num;
  llist->next = new;
}

/* Delete a node at the end of the list */
void delete_end(struct NODE *llist) {
  while(llist->next->next != NULL) {
    llist = llist->next;
  }
  free(llist->next);
  llist->next = NULL;
}

/* Delete a node from the front of the list */
void delete_front(struct NODE *llist) {
  struct NODE *temp;  
  temp=(struct NODE *)malloc(sizeof(struct NODE));
  temp = llist->next;
  
  llist->number = temp->number;
  llist->next = temp->next;
  free(temp);
}

/* Inserts a node in the middle of the list */
void insert_mid(struct NODE *llist, int num, int val) {
  while (llist->number != val) {
    llist = llist->next;
  }
  struct NODE *new;  
  new=(struct NODE *)malloc(sizeof(struct NODE));
  new->number = num;
  new->next = llist->next;
  llist->next = new;
}

/* Deletes a node in the middle of the list */
void delete_mid(struct NODE *llist, int val) {
  while (llist->number != val) {
    llist = llist->next;
  }
  struct NODE *temp;  
  temp=(struct NODE *)malloc(sizeof(struct NODE));
  temp = llist->next;
  llist->next = temp->next;
  free(temp);
}

/* Modify the value of a node */
void modify(struct NODE *llist, int num, int new) {
  while (llist->next != NULL) {
    if (llist->number == num) {
	  llist->number = new;
	}
	llist = llist->next;
  }
}

/* Prints all nodes in the list */
void display_list(struct NODE *llist) {
  while(llist->next != NULL) {
    printf("%d->", llist->number);
    llist = llist->next;
  }
}