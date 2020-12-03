typedef struct itemNode itemNode ;

struct itemNode {
    char id[16] ;
    unsigned short qty ;
    char desc[31] ;
    itemNode *next ;
} ;

int main(int argc, char *argv[])
{
    return 0;
}
