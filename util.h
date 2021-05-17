/*
 * File: util.h
 * Author: Diogo Gaspar, 99207
 * Description: Header file containing general macros and prototypes, structs
 */

/* the command can have at most 6 characters + '\0' */
#define MAX_COMMAND_SIZE 7
/* initial "to-be stored" memory amount for the input */
#define MEM_AMOUNT 1024 

/* the program must stop - the command was quit */
#define EXIT 0
/* the program can continue - the command wasn't quit */
#define CONTINUE 1

/* command strings */
#define HELP "help"
#define QUIT "quit"
#define SET "set"
#define PRINT "print"
#define FIND "find"
#define LIST "list"
#define SEARCH "search"
#define DELETE "delete"

/* command information - used in help */
#define HELP_INFO "help: Imprime os comandos disponíveis.\n"
#define QUIT_INFO "quit: Termina o programa.\n"
#define SET_INFO "set: Adiciona ou modifica o valor a armazenar.\n"
#define PRINT_INFO "print: Imprime todos os caminhos e valores.\n"
#define FIND_INFO "find: Imprime o valor armazenado.\n"
#define LIST_INFO "list: Lista todos os componentes de um caminho.\n"
#define SEARCH_INFO "search: Procura o caminho dado um valor.\n"
#define DELETE_INFO "delete: Apaga um caminho e todos os subcaminhos.\n"

/* error messages */
#define NO_DATA "no data\n"
#define NOT_FOUND "not found\n"

/* DLL node struct */
struct nodeDLL{
  char *value;
  struct nodeDLL *prev, *next;
};

typedef struct nodeDLL* link;

/* DLL struct */
typedef struct Dlist{
  link head, tail;
}Dlist;

struct treeAVL;

/* AVL node struct */
struct nodeAVL{
  char *value, *dirName;
  int height;
  Dlist *subDirectories;
  struct treeAVL *tree;
};

/* AVL tree struct */
struct treeAVL{
  struct treeAVL *left;
  struct treeAVL *right;
  struct nodeAVL *node;
};

typedef struct treeAVL* linkAVL;

/* Function prototypes */

void help();
void set(linkAVL tree, Dlist *dll);
void print(linkAVL tree, Dlist *dll);
void find();
void list();
void search();
void del();

int commandHub();
void readValue(char *s);
void readPath(char *s);
struct nodeAVL* setAux(char *dir, linkAVL x, Dlist *dll);
struct nodeAVL* traverseFind(char *dir, linkAVL x);

/* general DLL-related function prototypes */
link createNodeDLL(char *s);
void insertTailDLL(link head, link tail, char *s);
link lookupDLL(link head, char *s);
link deleteNodeDLL(link head, char *s);
void printDLL(link head);
void freeNodeDLL(link x);
void freeDLL(link head);
Dlist* initializeDLL();

/* general AVL-tree-related function prototypes */
struct nodeAVL* createNodeAVL(char *s, char *name);
int height(struct nodeAVL *node);
linkAVL rotL(linkAVL node);
linkAVL rotR(linkAVL node);
linkAVL rotLR(linkAVL node);
linkAVL rotRL(linkAVL node);
void updateHeight(linkAVL node);
int balanceNode(linkAVL node);
linkAVL balanceAVL(linkAVL x);
linkAVL insertAVL(linkAVL x, struct nodeAVL *newNode);
void freeAVL(linkAVL node);
linkAVL initializeAVL();
/*
void freeNodeAVL(struct nodeAVL *node); */