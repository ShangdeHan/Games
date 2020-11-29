#ifndef _ADVANCE_H
#define _ADVANCE_H

int SearchAndStore(FILE *file);//this function read from file and store it to a char array
int checkDuplicard();//this function check whether there are duplicated cards
int checkMissingcard();//this function check whether there are missing cards
void Store_RULES();//this function store RULES elements to a char array
void Store_FOUNDATIONS();//store FOUNDATIONS elements to a char array
void Store_TABLEAU();//store TABLEAU elements to a char array
void Store_STOCK();//store STOCK elements to a char array
void Store_MOVES();//store MOVES elements to a char array
void splitColumns();//split columns in TABLEAU to 7 columns
int move(char str[10]);//has 6 situations, ".", "r", "w->f", "t->t", "w->t", "t->f"
int stockToWaste();//move card from stock to waste
int stockReset();//reset waste card
int moveInTableau(char str[10]);//one situation of move, t->t, move in TABLEAU
int movefromTtoF(char str[10]);//one situation of move, t->f, move from TABLEAU to FOUNDATION
int movefromWtoT(char str[10]);//one situation of move, w->t, move from waste to TABLEAU
int movefromWtoF(char str[10]);//one situation of move, w->f, move from waste to FOUNDATION
int check_suit(char s1[], char s2[]);//check two cards color, if not same return 0, else return 1
int check_rank(char s1[], char s2[]);//check two cards rank, if different by 1 return 0, else return
void show(int count, int error);//if no any argument or just -m N, output on screen
void showToFile(int count, int error, FILE* file);//if has -o but not -x, output to file
void showExchangeFormat(int count, int error);//if has -x but not -o, output by exchange format
void showExchangeFormatToFile(int count, int error, FILE* file);//if has both -x and -o, output to file

char solitaireC[13][3] = {"Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc"};//clubs cards
char solitaireD[13][3] = {"Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd"};//diamonds cards
char solitaireH[13][3] = {"Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh"};//hearts cards
char solitaireS[13][3] = {"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks"};//spades cards
char order[] = {'_', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', '\0'};//to check rank

char storeAll[500][20];//store all string in file, each line end has "line_end", file end has "all_end"
char storeRules[10][10];//store RULES part, end with "FOUNDATIONS:"
char storeFundations[15][10];//store FOUNDATION part, end with "TABLEAU:"
char storeTableau[70][10];//store TABLEAU part, end with"STOCK:"
char storeStock[70][10];//store STOCK part, end with "MOVES:"
char storeMoves[200][10];//store MOVES part, end with"all_end"
char dublicated_Cards[55][10];//store duplicated cards from input file
char missing_Cards[55][10];//store missing cards from input file
char columns[8][55][9];//store 7 columns with cards in each column
int resetNum;//is how many "r" has been called

#endif //_ADVANCE_H

