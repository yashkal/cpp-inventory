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
    fscanf(fp, "%[^:]:%hu:%[^:\n]", new_node->id, &new_node->qty, new_node->desc);
    new_node->next = first;
    first = new_node;

    fclose(fp);
    fp = NULL;

    // Get max size for string fields to adjust printing size
    int max_desc_length = strlen(first->desc) + 1;
    int max_id_length = strlen(first->id) + 1;

    while( prompt( &buff, &len, stdin ) != -1 )
    {
	buff[ strlen(buff)-1 ] = '\0' ;  /* Overwrite the newline */
	sscanf(buff, "%s", input_string);

	if (strcmp(input_string, "print") == 0)
	{
	    // print header
	    printf("%-*s  %-6s  %-*s\n", max_desc_length, "  DESC", "  QTY", max_id_length + 6, "  ID");
	    int i;
	    for (i = 0; i < max_desc_length; ++i) putc('-', stdout);
	    printf("  ");
	    for (i = 0; i < 6; ++i) putc('-', stdout);
	    printf("  ");
	    for (i = 0; i < max_id_length + 1; ++i) putc('-', stdout);
	    putc('\n', stdout);

	    // print items in database
	    printf("%-.*s   %5hu    %-.*s\n", max_desc_length, first->desc, first->qty, max_id_length, first->id);
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
