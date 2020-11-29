#ifndef _CHECK_H
#define _CHECK_H

int SearchAndStore(FILE *file);//this function read from file and store in to char array
int ReadCoveredFromTableau();//this function read covered card from TABLEAU
int ReadStockFromStore();//this function read cards from stock
int checkDuplicard();//this function check whether there are duplicated cards
int checkMissingcard();//this function check wheter there are missing cards
void Store_RULES();//this function store RULES elements to a char array
void Store_FOUNDATIONS();//store FOUNDATIONS elemetns to a char array
void Store_TABLEAU();//store TABLEAU elements to a char array
void Store_STOCK();//store STOCK elements to a char array
int check_table_rank(char s[40][20], int size);//check uncovered cards' rank
int check_table_suit(char s[40][20], int size);//check uncovered card's color

char solitaireC[13][3] = {"Ac","2c","3c","4c","5c","6c","7c","8c","9c","Tc","Jc","Qc","Kc"};
char solitaireD[13][3] = {"Ad","2d","3d","4d","5d","6d","7d","8d","9d","Td","Jd","Qd","Kd"};
char solitaireH[13][3] = {"Ah","2h","3h","4h","5h","6h","7h","8h","9h","Th","Jh","Qh","Kh"};
char solitaireS[13][3] = {"As","2s","3s","4s","5s","6s","7s","8s","9s","Ts","Js","Qs","Ks"};

char storeAll[500][20];
char storeRules[10][10];
char storeFundations[15][10];
char storeTableau[70][10];
char storeStock[70][10];
char dublicated_Cards[55][10];
char missing_Cards[55][10];
int wastCards;

#endif //_CHECK_H
