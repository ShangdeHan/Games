#ifndef GAME_H
#define GAME_H
int SearchAndStore(FILE *file);//this function read from file and store in to char array
void Store_RULES();//this function store RULES elements to a char array
void Store_FOUNDATIONS();//store FOUNDATIONS elemetns to a char array
void Store_TABLEAU();//store TABLEAU elements to a char array
void Store_STOCK();//store STOCK elements to a char array
void Store_MOVES();//store MOVES elements to a char array
void splitColumns();//split columns in TABLEAU to 7 columns
int move(char str[10], char data[9][55][9]);//has 6 situations, ".", "r", "w->f", "t->t", "w->t", "t->f"
int stockToWaste(char data[9][55][9]);//move card from stock to waste
int stockReset(char data[9][55][9]);//reset waste card
int moveInTableau(char str[10], char data[9][55][9]);//one situation of move, t->t, move in TABLEAU
int movefromTtoF(char str[10], char data[9][55][9]);//one situation of move, t->f, move from TABLEAU to FOUNDATION
int movefromWtoT(char str[10], char data[9][55][9]);//one situation of move, w->t, move from waste to TABLEAU
int movefromWtoF(char str[10], char data[9][55][9]);//one situation of move, w->f, move from waste to FOUNDATION
int check_suit(char s1[], char s2[]);//check two cards color, if not same return 0, else return 1
int check_rank(char s1[], char s2[]);//check two cards rank, if different by 1 return 0, else return
struct node* getNewNode(char str[9][55][9]);// initial new node
struct node * insertAtTail(struct node* head, char str[9][55][9]);// insert node at tail
void mergeData();//merge all tableau, stock, foundation into one 3d array
int suitToUnit(char s);
void gameconfiguration(char data[9][55][9]);
void shuffle(int* deck);
int choose_randomly_between(int a, int b);
double Random();
void newgame(int seed, int def, int limit);

char order[] = {'_', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', '\0'};//to check rank
char src[] = {'w', '1', '2', '3', '4', '5', '6', '7', '\0'};//source array, from target
char des[] = {'f', '1', '2', '3', '4', '5', '6', '7', '\0'};//destination array, to target

char storeAll[500][20];//store all string in file, each line end has "line_end", file end has "all_end"
char storeRules[10][10];//store RULES part, end with "FOUNDATIONS:"
char storeFundations[15][10];//store FOUNDATION part, end with "TABLEAU:"
char storeTableau[70][10];//store TABLEAU part, end with"STOCK:"
char storeStock[70][10];//store STOCK part, end with "MOVES:"
char storeMoves[200][10];//store MOVES part, end with"all_end"
char columns[8][55][9];//store 7 columns with cards in each column
int resetNum;//is how many "r" has been called
unsigned long RNG_seed;
int def;
int limit;
char copyData[8][55][9];//after merge data
char arrays[10][35];
struct node{
    char copyConfiguration[9][55][9];
    struct node* next;
    struct node* last;
};

#endif //GAME_H
