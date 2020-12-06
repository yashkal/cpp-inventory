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
int get_desc_column_size(itemNode *first);
int get_id_column_size(itemNode *first);
void print(itemNode *first);
void add(itemNode *first, char *buff);
void remove_(itemNode *first, char *buff);
void quit(itemNode *first);
itemNode *read_db(void);

int main(int argc, char *argv[])
{
    itemNode *first = read_db();

    char *buff = NULL;
    size_t len = 0 ;
    char input_string[100];

    while( prompt( &buff, &len, stdin ) != -1 )
    {
	buff[ strlen(buff)-1 ] = '\0' ;  /* Overwrite the newline */
	sscanf(buff, "%s", input_string);

	if (strcmp(input_string, "print") == 0) print(first);
	else if (strcmp(input_string, "add") == 0) add(first, buff);
	else if (strcmp(input_string, "remove") == 0) remove_(first, buff);
	else if (strcmp(input_string, "quit") == 0) quit(first);
	else printf("Unrecognized command\n");
    }
    return 0;
}

int prompt(char **buff, size_t *len, FILE *fp)
{
    printf("%% ");
    return getline( buff, len, fp );
}

int get_desc_column_size(itemNode *first)
{
    itemNode *p;
    int max_size = 0;
    int size;
    for (p = first; p != NULL; p = p->next)
    {
	size = strlen(p->desc);
	if ( size > max_size ) max_size = size;
    }
    return max_size + 1;
}

int get_id_column_size(itemNode *first)
{
    itemNode *p;
    int max_size = 0;
    int size;
    for (p = first; p != NULL; p = p->next)
    {
	size = strlen(p->id);
	if ( size > max_size ) max_size = size;
    }
    return max_size + 1;
}

void print(itemNode *first)
{
    int max_desc_length = get_desc_column_size(first);
    int max_id_length = get_id_column_size(first);

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
    itemNode *p;
    for (p = first; p != NULL; p = p->next)
	printf("%-*s  %5hu    %-*s\n", max_desc_length, p->desc, p->qty, max_id_length, p->id);
}

void add(itemNode *first, char *buff)
{
    char *token = NULL;
    char id[16];
    unsigned short qty;

    // Throwaway token for command
    token = strtok(buff, " ");

    // Token for id
    token = strtok(NULL, ":");
    if (token == NULL)
    {
	printf("NAK Incorrect syntax.\n");
	return;
    }
    sscanf(token, "%s", id);

    // Token for quantity
    token = strtok(NULL, ":");
    if (token == NULL)
    {
	printf("NAK Incorrect syntax.\n");
	return;
    }
    sscanf(token, "%hu", &qty);

    // Search in linked list to add quantity
    itemNode *p;
    for (p = first; p != NULL; p = p->next)
    {
	if (strcmp(p->id, id) == 0)
	{
	    p->qty += qty;
	    printf("ACK\n");
	    return;
	}
    }
    printf("NAK Unknown Item\n");
}

void remove_(itemNode *first, char *buff)
{
    char *token = NULL;
    char id[16];
    unsigned short qty;

    // Throwaway token for command
    token = strtok(buff, " ");

    // Token for id
    token = strtok(NULL, ":");
    if (token == NULL)
    {
	printf("NAK Incorrect syntax.\n");
	return;
    }
    sscanf(token, "%s", id);

    // Token for quantity
    token = strtok(NULL, ":");
    if (token == NULL)
    {
	printf("NAK Incorrect syntax.\n");
	return;
    }
    sscanf(token, "%hu", &qty);

    // Search in linked list to add quantity
    itemNode *p;
    for (p = first; p != NULL; p = p->next)
    {
	if (strcmp(p->id, id) == 0)
	{
	    if ( p->qty < qty )
	    {
		printf("NAK Insufficient Quantity\n");
		return;
	    }
	    p->qty -= qty;
	    printf("ACK\n");
	    return;
	}
    }
    printf("NAK Unknown Item\n");
}

void quit(itemNode *first)
{
    FILE *fp;
    itemNode *p;

    if ((fp = fopen("inv.dat", "w")) == NULL)
    {
	printf("Can't open inv.dat\n");
	exit(EXIT_FAILURE);
    }

    // Write file to disk
    for (p = first; p != NULL; p = p->next)
	fprintf(fp, "%s:%hu:%s\n", p->id, p->qty, p->desc);

    // Clear linked list
    while (first != NULL)
    {
	p = first;
	first = first->next;
	free(p);
    }

    fclose(fp);
    fp = NULL;
    p = NULL;

    // Exit program
    exit(EXIT_SUCCESS);
}

itemNode* read_db(void)
{
    FILE *fp;

    if ((fp = fopen("inv.dat", "r")) == NULL)
    {
	printf("Can't open inv.dat\n");
	exit(EXIT_FAILURE);
    }

    char id[16], desc[31];
    unsigned short qty;
    itemNode *first;
    itemNode *new_node;

    first = NULL;
    while( fscanf(fp, "%[^:]:%hu:%[^:\n]\n", id, &qty, desc) != EOF )
    {
	new_node = malloc(sizeof(itemNode));
	strcpy(new_node->id, id);
	new_node->qty = qty;
	strcpy(new_node->desc, desc);
	new_node->next = first;
	first = new_node;
    }

    fclose(fp);
    fp = NULL;
    new_node = NULL;

    return first;
}
