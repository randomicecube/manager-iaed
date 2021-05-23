/*
 * File: util.h
 * Author: Diogo Gaspar, 99207
 * Description: Header file containing general macros and prototypes, structs
 */

/* ----------------------------------------------------------------------------

General explanation of the data structures implemented

The idea was to utilize 2 data structures together - a doubly-linked list and
an AVL tree. The AVL tree is sorted aplhabetically, and it has "layers" - a
node in the tree points to another tree, and so on, to aid in the hierarchy
aspect of the project. Each node (and the "root" itself) has a DLL associated,
which stores the pointers to each node of the AVL, but with a twist: here, they
are sorted by when they were introduced. This way, in "search" and "print",
when the goal is to look up items by depth and creation order, it's much easier
(and more efficient) to do so!

---------------------------------------------------------------------------- */

/* ------------------------------MACROS/DEFINES----------------------------- */

/* the command can have at most 6 characters + '\0' */
#define MAX_COMMAND_SIZE 7
/* initial "to-be stored" memory amount for the input */
#define MEM_AMOUNT 66000

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
#define LIST_INFO "list: Lista todos os componentes imediatos de um sub-caminho.\n"
#define SEARCH_INFO "search: Procura o caminho dado um valor.\n"
#define DELETE_INFO "delete: Apaga um caminho e todos os subcaminhos.\n"

/* error messages */
#define NO_DATA "no data\n"
#define NOT_FOUND "not found\n"
#define FIND_ERROR 0
#define FAIL 0
#define NOT_FIND_ERROR 1
#define SUCCESS 1

/* ---------------------------------STRUCTS--------------------------------- */

struct treeAVL;
struct Dlist;

/* AVL node struct */
struct nodeAVL{
  char *value, *dirName;
  struct Dlist *subDirectories;
  struct treeAVL *tree;
  struct nodeAVL *prev, *next;
};

/* AVL tree struct */
struct treeAVL{
  int height;
  struct treeAVL *left, *right;
  struct nodeAVL *node;
};

typedef struct treeAVL* linkAVL;

/* DLL struct */
typedef struct Dlist{
  struct nodeAVL *head, *tail;
}Dlist;

/* -------------------------------PROTOTYPES-------------------------------- */

/* functions related to redirecting commands/reading input */
linkAVL commandHub(linkAVL tree, Dlist **dll, char*s);
void readValue(char *s);

/* command "main" functions */
void help();
linkAVL set(linkAVL x, Dlist *dll, char *s);
void print(char *s, linkAVL x, Dlist *dll);
void find(linkAVL x, char *s);
void list(linkAVL x);
void search(linkAVL x, Dlist *dll, char *s);
linkAVL del(linkAVL x, Dlist *dll);

/* command "aux" functions */
linkAVL set_r(linkAVL x, Dlist *dll, char* path, char* value);
struct nodeAVL *setAux(char *dir, linkAVL x, Dlist *dll);
void traverseListSubPath(linkAVL x);
int searchAux(char *bleh, char *s, linkAVL x, Dlist *dll);

/* general DLL-related function prototypes */
struct nodeAVL *insertTailDLL(Dlist *dll, struct nodeAVL *nodeDir);
Dlist* deleteNodeDLL(Dlist *dll, char *s);
Dlist* initializeDLL();

/* general AVL-tree-related function prototypes */
linkAVL initializeAVL(struct nodeAVL* node);
struct nodeAVL* createNodeAVL(char *s, char *name);
int height(linkAVL x);
linkAVL max(linkAVL tree);
linkAVL rotL(linkAVL node);
linkAVL rotR(linkAVL node);
linkAVL rotLR(linkAVL node);
linkAVL rotRL(linkAVL node);
linkAVL updateHeight(linkAVL node);
int balanceNode(linkAVL node);
linkAVL balanceAVL(linkAVL x);
linkAVL insertAVL(linkAVL x, struct nodeAVL *newNode);
struct nodeAVL* traverse(int func, char *dir, linkAVL x);
linkAVL freeAVL(linkAVL tree);
linkAVL freeNodeAVL(linkAVL x);
linkAVL deleteNodeAVL(struct nodeAVL *toDelete, linkAVL tree);