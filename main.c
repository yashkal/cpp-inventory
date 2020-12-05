#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct itemNode itemNode ;

struct itemNode {
    char id[16] ;
    unsigned short qty ;
    char desc[31] ;
    itemNode *next ;
} ;

int prompt(char **buff, size_t *len, FILE *fp);

int main(int argc, char *argv[])
{
    char *buff = NULL ;
    size_t len = 0 ;
    char input_string[10];
    FILE *fp;

    // Read database
    if ((fp = fopen("inv.dat", "r")) == NULL)
    {
	printf("Can't open inv.dat\n");
	exit(EXIT_FAILURE);
    }

    // Read one line of input from file
    // Review linked list on page 428 in book

    itemNode *first;
    itemNode *new_node;

    first = NULL;

    new_node = malloc(sizeof(itemNode));
    fscanf(fp, "%s:%hu:%s", new_node->id, &new_node->qty, new_node->desc);
    new_node->next = first;
    first = new_node;

    fclose(fp);
    fp = NULL;

    while( prompt( &buff, &len, stdin ) != -1 )
    {
	buff[ strlen(buff)-1 ] = '\0' ;  /* Overwrite the newline */
	sscanf(buff, "%s", input_string);

	if (strcmp(input_string, "print") == 0)
	{
	    // do something
	}
	else // default
	{
	    printf("Unrecognized command\n");
	}
    }
    return 0;
}

int prompt(char **buff, size_t *len, FILE *fp)
{
    printf("%% ");
    return getline( buff, len, fp );
}
