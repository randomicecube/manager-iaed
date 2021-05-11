/* the buffer can contain at most 65535 characters + '\0' */
#define BUFFERSIZE 65536
/* the command can have at most 6 characters + '\0' */
#define MAX_COMMAND_SIZE 7

/* the program can continue - the command wasn't quit */
#define CONTINUE 1
/* the program must stop - the command was quit */
#define QUIT 0
/* prompt macro */
#define PROMPT "? "

/* command strings */
#define HELP "help"
#define SET "set"
#define PRINT "print"
#define FIND "find"
#define LIST "list"
#define SEARCH "search"
#define DELETE "delete"

/* command information - used in helpHub */

#define HELP_INFO "help: Imprime os comandos disponíveis.\n"
#define QUIT_INFO "quit: Termina o programa.\n"
#define SET_INFO "set: Adiciona ou modifica o valor a armazenar.\n"
#define PRINT_INFO "print: Imprime todos os caminhos e valores.\n"
#define FIND_INFO "find: Imprime o valor armazenado.\n"
#define LIST_INFO "list: Lista todos os componentes de um caminho.\n"
#define SEARCH_INFO "search: Procura o caminho dado um valor.\n"
#define DELETE_INFO "delete: Apaga um caminho e todos os subcaminhos.\n"


/* Function prototypes */

int commandHub(char *input);
void helpHub();
void setHub(char *input);
void printHub(char *input);
void findHub(char *input);
void listHub(char *input);
void searchHub(char *input);
void deleteHub(char *input);