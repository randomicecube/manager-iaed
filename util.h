/*
 * File: util.h
 * Author: Diogo Gaspar, 99207
 * Description: Header file containing general macros and prototypes, structs
 */

/* ------------------------------MACROS/DEFINES----------------------------- */

/* the command can have at most 6 characters + '\0' */
#define MAX_COMMAND_SIZE 7
/* initial "to-be stored" memory amount for the input */
#define MEM_AMOUNT 4096 

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
#define FIND_ERROR 0
#define NOT_FIND_ERROR 1

/* ---------------------------------STRUCTS--------------------------------- */

struct treeAVL;
struct Dlist;

/* AVL node struct */
struct nodeAVL{
  char *value, *dirName;
  int height;
  struct Dlist *subDirectories;
  struct treeAVL *tree;
  struct nodeAVL *prev, *next;
};

/* AVL tree struct */
struct treeAVL{
  struct treeAVL *left;
  struct treeAVL *right;
  struct nodeAVL *node;
};

typedef struct treeAVL* linkAVL;

/* DLL struct */
typedef struct Dlist{
  struct nodeAVL *head, *tail;
}Dlist;

/* -------------------------------PROTOTYPES-------------------------------- */

/* functions related to redirecting commands/reading input */
int commandHub();
void readValue(char *s);
void readPath(char *s);

/* command "main" functions */
void help();
void set(linkAVL tree, Dlist *dll);
void print(char *s, linkAVL tree, Dlist *dll);
void find();
void list();
void search();
void del();

/* command aux functions */
struct nodeAVL* setAux(char *dir, linkAVL x, Dlist *dll);
void traverseListSubPath(linkAVL x);

/* general DLL-related function prototypes */
void insertTailDLL(Dlist *dll, struct nodeAVL *nodeDir);
struct nodeAVL* lookupDLL(struct nodeAVL *head, char *s);
struct nodeAVL* deleteNodeDLL(struct nodeAVL *head, char *s);
void printDLL(struct nodeAVL *head);
void freeNodeDLL(struct nodeAVL *x);
void freeDLL(struct nodeAVL *head);
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
struct nodeAVL* traverse(int func, char *dir, linkAVL x);
void freeAVL(linkAVL node);
linkAVL initializeAVL();
/*
void freeNodeAVL(struct nodeAVL *node); */