#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "check.h"

int main(int argc, char *argv[]) {
    FILE *file1;
    FILE *input = stdin;
    int result;
    if(argc == 1){
        result = SearchAndStore(input);
    }else if(argc == 2){
        file1 = fopen(argv[1], "r");
        result = SearchAndStore(file1);
    }
    else if(argc< 0 || argc > 2){
        fprintf(stderr ,"%s" ,"It does not exist.\n");
        exit(1);
    }
//    FILE* file = fopen("/home/shangde/where/hw1/part2/valid0.txt", "r");
//    int result = SearchAndStore(file);
    if(result == 0){
        Store_RULES();
        Store_FOUNDATIONS();
        Store_TABLEAU();
        Store_STOCK();
        int q = 0;
        int Tcount = 0;
        while(strcmp(storeTableau[q], "STOCK:") != 0){//check many "|" in TABLEAU
            if(strcmp(storeTableau[q], "|") == 0) Tcount++;
            q++;
        }if(Tcount!=7){
            fprintf(stderr, "Invalid input in columns \n");
            exit(1);
        }
        int h = 0;
        int Scount = 0;
        while(strcmp(storeStock[h], "MOVES:") != 0){//check many "|" in STOCK
            if(strcmp(storeStock[h], "|") == 0) Scount++;
            h++;
        }if(Scount!=1){
            fprintf(stderr, "Invalid input in STOCK \n");
            exit(1);
        }
        int dubNums = checkDuplicard();
        if(dubNums != 0){
            printf("%s", "Duplicated cards: ");
            for(int i =0;i<dubNums;i++){
                printf("%s ", dublicated_Cards[i]);
            }
            printf("\n");
        }
        int misNums = checkMissingcard();
        if(misNums != 0){
            printf("%s", "Missing cards: ");
            for(int i =0;i<misNums;i++){
                printf("%s ", missing_Cards[i]);
            }
            printf("\n");
        }
        if(dubNums == 0 && misNums == 0){
            printf("%s\n", "Input file is valid");
            int covered = ReadCoveredFromTableau();
            printf("%d%s\n", covered, " covered cards");
            int stock = ReadStockFromStore();
            printf("%d%s\n", stock, " stock cards");
            printf("%d%s\n", wastCards, " wast cards");
        }
    }
    return 0;
}


int SearchAndStore(FILE *file) {
    int num_of_sting = 0;//number of each string in this file
    char fileName[100];
    int iter = 0;
    char temp[501];
    const char space[2] = " ";
    char *token;
    int line = 0;
    int between_TabAndStock = 0;// if this variable equals 1, check tableau rank and color
    char str[30];
    while(fgets(temp, 500, file) != NULL){// read each line from file
        line ++;
        while(temp[0] <0){//remove messy code(machine code)
            memmove(&temp[0], &temp[1], strlen(temp) - 1);
        }
        if(temp[0] == '#')continue;
        if(temp[2] == '#')continue;
        if(temp[0] == '\n')continue;
        token = strtok(temp, space);
        char store_line[20][20];
        int num = 0;
        while(token != NULL && strcmp(token, "#") != 0){//splite each string from line, and if '#' occurs, skip to next line
            int i;
            if(token[0] == '#')break;
            if(strcmp(token, "#\n") == 0 ||strcmp(token, "\n") == 0 || token[0] == '\n'|| token[0] == '#'){
                token = strtok(NULL, space);
                continue;
            }
            if(strstr(token, "\n")){
                while(token[strlen(token)-1]=='\n'){
                    token[strlen(token)-1] = 0;
                }
            }
	    if(strstr(token, "\r")){
                while(token[strlen(token)-1]=='\r'){
                    token[strlen(token)-1] = 0;
                }
            }
            if(strstr(token, "\t")){
                while(token[strlen(token)-1]=='\t'){
                    token[strlen(token)-1] = 0;
                }
                if(token[0]=='\t'){
                    char strr[2];
                    memset(strr, 0, 2);
                    strr[0] = token[strlen(token)-2];
                    strr[1] = token[strlen(token)-1];
                    strcpy(token, strr);
                }
            }
            if(strcmp(token, "")==0){
                token = strtok(NULL, space);
                continue;
            }
            strcpy(store_line[num], token);
            strcpy(storeAll[iter], token);
//            if(num_of_sting == 0) {
//                if (strcmp(token, "RULES:") != 0) {
//                    fprintf(stderr, "Error near line %d : expecting 'RULES:'\n", line);
//                }
//            }if (num_of_sting == 1) {
//                if(strcmp(token, "turn") != 0){
//                    fprintf(stderr, "Error near line %d : expecting 'turn\n", line);
//                }
//            }if (num_of_sting == 2) {
//                if(strcmp(token, "1") != 0 && strcmp(token, "3") != 0){
//                    fprintf(stderr, "Error near line %d: expecting 'integer'\n", line);
//                }
//            }if (num_of_sting == 3) {
//                if (strcmp(token, "unlimited") != 0 && strcmp(token, "limit") != 0) {
//                    fprintf(stderr, "Error near line %d: expecting 'unlimited'\n", line);
//                }
//                if (strcmp(token, "limit") == 0) {
//                    token = strtok(NULL, space);
//                    if(strstr(token, "\n")){
//                        while(token[strlen(token)-1]=='\n'){
//                            token[strlen(token)-1] = 0;
//                        }
//                    }
//                    if(strcmp(token, "0")!=0&&strcmp(token, "1")!=0&&strcmp(token, "2")!=0&&strcmp(token, "3")!=0&&strcmp(token, "4")!=0&&strcmp(token, "5")!=0
//                    &&strcmp(token, "6")!=0&&strcmp(token, "7")!=0&&strcmp(token, "8")!=0&&strcmp(token, "9")!=0){
//                        fprintf(stderr, "Error near line %d: expecting 'number'\n", line);
//                    }
//                }
//            }if (num_of_sting == 4) {
//                if (strcmp(token, "FOUNDATIONS:") != 0) {
//                    fprintf(stderr, "Error near line %d: expecting 'FOUNDATIONS:'\n", line);
//                }
//            }
            num_of_sting++;
            token = strtok(NULL, space);
            iter++;
            num++;
        }
        if(strstr(temp, "TABLEAU:") != NULL)between_TabAndStock++;//when read STOCK:,
        if(between_TabAndStock == 1){
            int rank_result = check_table_rank(store_line, num);//call check rank function
            if(rank_result == -1){
                fprintf(stderr ,"%s %d", "error near line: ", line);
                return -1;
            }
            int suit_result = check_table_suit(store_line, num);//call check suit function
            if(suit_result == -1){
                fprintf(stderr ,"%s %d", "error near line: ", line);
                return -1;
            }
        }
        if(strstr(temp, "STOCK:")!= NULL)between_TabAndStock++;//when read TABLEAU:, check rank and color
        strcpy(storeAll[iter], "line_end");//each line end with "line_end"
        iter += 1;
    }
    strcpy(storeAll[iter], "all_end");//after running the whole file, end with "all_end"
    int j;
    for(j = 0; j<10; j++){
        if(strcmp(storeAll[j], "all_end") == 0){
            break;
        }
    }

    return 0;
}


void Store_RULES(){
    int rulesIndex = 0;
    for(int i = 0; i<500;i++){
        if(strcmp(storeAll[i], "RULES:") == 0){
            i = i + 1;
            if(strcmp(storeAll[i], "line_end") == 0)i++;
            while(strcmp(storeAll[i], "FOUNDATIONS:") != 0) {
                strcpy(storeRules[rulesIndex], storeAll[i]);
                rulesIndex++;
                i++;
            }
        }
        if(strcmp(storeAll[i], "FOUNDATIONS:") == 0){
            strcpy(storeRules[rulesIndex], storeAll[i]);
            break;
        }
    }
}

void Store_FOUNDATIONS(){
    int foundationsIndex = 0;
    for(int i = 0; i<500;i++){
        if(strcmp(storeAll[i], "FOUNDATIONS:") == 0){
            i = i + 1;
            while(strcmp(storeAll[i], "TABLEAU:") != 0) {
                if(strcmp(storeAll[i], "line_end") == 0){
                    i++;
                    continue;
                }
                strcpy(storeFundations[foundationsIndex], storeAll[i]);
                foundationsIndex++;
                i++;
            }
        }
        if(strcmp(storeAll[i], "TABLEAU:") == 0){
            strcpy(storeFundations[foundationsIndex], storeAll[i]);
            break;
        }
    }
}

void Store_TABLEAU() {
    int tableauIndex = 0;
    for (int i = 0; i < 500; i++) {
        if (strcmp(storeAll[i], "TABLEAU:") == 0) {
            i = i + 1;
            if (strcmp(storeAll[i], "line_end") == 0)i++;
            while (strcmp(storeAll[i], "STOCK:") != 0) {
                strcpy(storeTableau[tableauIndex], storeAll[i]);
                tableauIndex++;
                i++;
            }
        }
        if (strcmp(storeAll[i], "STOCK:") == 0) {
            strcpy(storeTableau[tableauIndex], storeAll[i]);
            break;
        }
    }
}

void Store_STOCK() {
    int stockIndex = 0;
    for (int i = 0; i < 500; i++) {
        if (strcmp(storeAll[i], "STOCK:") == 0) {
            i = i + 1;
            while (strcmp(storeAll[i], "MOVES:") != 0) {
                if (strcmp(storeAll[i], "line_end") == 0){
                    i++;
                    continue;
                }
                strcpy(storeStock[stockIndex], storeAll[i]);
                stockIndex++;
                i++;
            }
        }
        if (strcmp(storeAll[i], "MOVES:") == 0) {
            strcpy(storeStock[stockIndex], storeAll[i]);
            break;
        }
    }
}

int ReadCoveredFromTableau()
{
    int covered_card = 0;
    for(int i =0; i<60; i++){
        while(strcmp(storeTableau[i], "|") != 0) {
            covered_card++;
            i++;
        }
        while(strcmp(storeTableau[i], "line_end") != 0)i++;
        if(strcmp(storeTableau[i+1], "STOCK:") == 0)break;
    }
    return covered_card;
}

int ReadStockFromStore(){
    wastCards = 0;
    int stockCards = 0;
    for(int i = 0; i<60;i++){
        while(strcmp(storeStock[i], "|") != 0) {
            wastCards++;
            i++;
        }
        if(strcmp(storeStock[i], "|") == 0)i++;
        while(strcmp(storeStock[i], "MOVES:") != 0) {
            if(strcmp(storeStock[i], "line_end") == 0){
                i++;
                continue;
            }
            stockCards++;
            i++;
        }
        if(strcmp(storeStock[i], "MOVES:") == 0)break;
    }
    return stockCards;
}

int checkDuplicard(){
    int dubNums = 0;
    int fou_indexC, fou_indexD, fou_indexH, fou_indexS;
    for(int i =0; i<15; i++){
        if(strcmp(storeFundations[i], "line_end") == 0)continue;
        if(strcmp(storeFundations[i], "TABLEAU:") == 0)break;
        if(storeFundations[i][1]== 'c'){//if this card is a Club
            if(storeFundations[i][0] == '_'){
                fou_indexC = -1;
                continue;
            }
            for(fou_indexC =0; fou_indexC<13;fou_indexC++){//check foundation Clubs index in solitaireC
                int c = strcmp(storeFundations[i], solitaireC[fou_indexC]);
                if(c == 0)break;
            }
        }if(storeFundations[i][1]== 'd'){//if this card is a Diamond
            if(storeFundations[i][0] == '_'){
                fou_indexD = -1;
                continue;
            }
            for(fou_indexD =0; fou_indexD<13;fou_indexD++){//check foundation Diamond index in solitaireD
                int d = strcmp(storeFundations[i], solitaireD[fou_indexD]);
                if(d == 0)break;
            }
        }if(storeFundations[i][1]== 'h'){//if this card is a Heart
            if(storeFundations[i][0] == '_'){
                fou_indexH = -1;
                continue;
            }
            for(fou_indexH =0; fou_indexH<13;fou_indexH++){//check foundation Heart index in solitaireH
                int h = strcmp(storeFundations[i], solitaireH[fou_indexH]);
                if(h == 0)break;
            }
        }
        if(storeFundations[i][1]== 's'){//if this card is a Spade
            if(storeFundations[i][0] == '_'){
                fou_indexS = -1;
                continue;
            }
            for(fou_indexS =0; fou_indexS<13;fou_indexS++){//check foundation Spades index in solitaireS
                int s = strcmp(storeFundations[i], solitaireS[fou_indexS]);
                if(s == 0)break;
            }
        }
    }
    for(int i =0; i<60; i++) {
        if (strcmp(storeTableau[i], "line_end") == 0)continue;
        if (strcmp(storeTableau[i], "|") == 0)continue;
        if (strcmp(storeTableau[i], "STOCK:") == 0)break;
        if(storeTableau[i][1] == 'c'){
            for (int tab_indexC = 0; tab_indexC < 13; tab_indexC++) {//check whether tableau has card smaller than foundation
                int c = strcmp(storeTableau[i], solitaireC[fou_indexC]);
                if(c == 0){
                    if (fou_indexC >= tab_indexC) {
                        strcpy(dublicated_Cards[dubNums], storeTableau[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeTableau[i][1] == 'd'){
            for (int tab_indexD = 0; tab_indexD < 13; tab_indexD++) {//check whether tableau has card smaller than foundation
                int d = strcmp(storeTableau[i], solitaireD[tab_indexD]);
                if(d == 0){
                    if (fou_indexD >= tab_indexD) {
                        strcpy(dublicated_Cards[dubNums], storeTableau[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeTableau[i][1] == 'h'){
            for (int tab_indexH = 0; tab_indexH < 13; tab_indexH++) {//check whether tableau has card smaller than foundation
                int h =strcmp(storeTableau[i], solitaireH[tab_indexH]);
                if(h == 0){
                    if (fou_indexH >= tab_indexH) {
                        strcpy(dublicated_Cards[dubNums], storeTableau[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeTableau[i][1] == 's'){
            for (int tab_indexS = 0; tab_indexS < 13; tab_indexS++) {//check whether tableau has card smaller than foundation
                int s = strcmp(storeTableau[i], solitaireS[tab_indexS]);
                if(s == 0){
                    if (fou_indexS >= tab_indexS) {
                        strcpy(dublicated_Cards[dubNums], storeTableau[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
    }

    for(int i =0; i<60; i++){
        if(strcmp(storeStock[i], "line_end") == 0)continue;
        if (strcmp(storeStock[i], "|") == 0)continue;
        if(strcmp(storeStock[i], "MOVES:") == 0)break;
        if(storeStock[i][1] == 'c'){
            for(int sto_indexC =0; sto_indexC<13;sto_indexC++){//check whether stock has card smaller than foundation
                int c = strcmp(storeStock[i], solitaireC[sto_indexC]);
                if(c == 0){
                    if(fou_indexC>=sto_indexC){
                        strcpy(dublicated_Cards[dubNums], storeStock[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeStock[i][1] == 'd'){
            for(int sto_indexD =0; sto_indexD<13;sto_indexD++){//check whether stock has card smaller than foundation
                int d = strcmp(storeStock[i], solitaireD[sto_indexD]);
                if(d == 0){
                    if(fou_indexD>=sto_indexD){
                        strcpy(dublicated_Cards[dubNums], storeStock[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeStock[i][1] == 'h'){
            for(int sto_indexH =0; sto_indexH<13;sto_indexH++){//check whether stock has card smaller than foundation
                int h = strcmp(storeStock[i], solitaireH[sto_indexH]);
                if(h == 0){
                    if(fou_indexH>=sto_indexH){
                        strcpy(dublicated_Cards[dubNums], storeStock[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
        if(storeStock[i][1] == 's'){
            for(int sto_indexS =0; sto_indexS<13;sto_indexS++){//check whether stock has card smaller than foundation
                int s = strcmp(storeStock[i], solitaireS[sto_indexS]);
                if(s == 0){
                    if(fou_indexS>=sto_indexS){
                        strcpy(dublicated_Cards[dubNums], storeStock[i]);
                        dubNums++;
                    }
                    break;
                }
            }
        }
    }

    int k = 0;
    while(strcmp(storeStock[k], "MOVES:") != 0){
        if(strcmp(storeStock[k], "line_end") == 0){
            k++;
            continue;
        }
        if(strcmp(storeStock[k], "|") == 0){
            k++;
            continue;
        }
        int m = 0;
        while(strcmp(storeTableau[m], "STOCK:") != 0){//check whether there is duplicated card in TBLEAU and STOCK
            if(strcmp(storeTableau[m], "line_end") == 0){
                m++;
                continue;
            }
            if(strcmp(storeTableau[m], "|") == 0){
                m++;
                continue;
            }
            if(strcmp(storeStock[k], storeTableau[m]) == 0){
                strcpy(dublicated_Cards[dubNums], storeTableau[m]);
                dubNums++;
            }
            m++;
        }
        if(strcmp(storeStock[k+1], "MOVES:") != 0){
            int n = k+1;
            while(strcmp(storeStock[n], "MOVES:") != 0){//check whether there is duplicated card in TBLEAU and STOCK
                if(strcmp(storeStock[k], storeStock[n]) == 0){
                    strcpy(dublicated_Cards[dubNums], storeStock[n]);
                    dubNums++;
                }
                n++;
            }
        }
        k++;
    }
    int i = 0;
    while(strcmp(storeTableau[i], "STOCK:") != 0){//check whether there is duplicated card in TBLEAU and TABLEAU
        if(strcmp(storeTableau[i], "line_end") == 0){
            i++;
            continue;
        }
        if(strcmp(storeTableau[i], "|") == 0){
            i++;
            continue;
        }
        if(strcmp(storeTableau[i+1], "STOCK:") != 0){
            int j = i+1;
            while(strcmp(storeTableau[j], "STOCK:") != 0){
                if(strcmp(storeTableau[j], "line_end") == 0){
                    j++;
                    continue;
                }
                if(strcmp(storeTableau[j], "|") == 0){
                    j++;
                    continue;
                }
                if(strcmp(storeTableau[i], storeTableau[j]) == 0){
                    strcpy(dublicated_Cards[dubNums], storeTableau[j]);
                    dubNums++;
                }j++;
            }
        }i++;
    }
    return dubNums;
}

int checkMissingcard(){
    int missing = 0;
    int fou_indexC, fou_indexD, fou_indexH, fou_indexS;
    for(int i =0; i<15; i++){
        if(strcmp(storeFundations[i], "line_end") == 0)continue;
        if(strcmp(storeFundations[i], "TABLEAU:") == 0)break;
        if(storeFundations[i][1]== 'c'){//if this card is a Club
            if(storeFundations[i][0] == '_'){
                fou_indexC = -1;
                continue;
            }
            for(fou_indexC =0; fou_indexC<13;fou_indexC++){//check foundation Clubs index in solitaireC
                int c = strcmp(storeFundations[i], solitaireC[fou_indexC]);
                if(c == 0)break;
            }
        }if(storeFundations[i][1]== 'd'){//if this card is a Diamond
            if(storeFundations[i][0] == '_'){
                fou_indexD = -1;
                continue;
            }
            for(fou_indexD =0; fou_indexD<13;fou_indexD++){//check foundation Diamond index in solitaireD
                int d = strcmp(storeFundations[i], solitaireD[fou_indexD]);
                if(d == 0)break;
            }
        }if(storeFundations[i][1]== 'h'){//if this card is a Heart
            if(storeFundations[i][0] == '_'){
                fou_indexH = -1;
                continue;
            }
            for(fou_indexH =0; fou_indexH<13;fou_indexH++){//check foundation Heart index in solitaireH
                int h = strcmp(storeFundations[i], solitaireH[fou_indexH]);
                if(h == 0)break;
            }
        }
        if(storeFundations[i][1]== 's'){//if this card is a Spade
            if(storeFundations[i][0] == '_'){
                fou_indexS = -1;
                continue;
            }
            for(fou_indexS =0; fou_indexS<13;fou_indexS++){//check foundation Spades index in solitaireS
                int s = strcmp(storeFundations[i], solitaireS[fou_indexS]);
                if(s == 0)break;
            }
        }
    }

    for(int j =fou_indexC+1;j<13;j++){//search from after index "fou_indexC" in solitaireC
        int findC = 0;
        for(int m = 0; m<70;m++){//check whether m in solitaireC exists in TABLEAU
            if (strcmp(storeTableau[m], "line_end") == 0)continue;
            if (strcmp(storeTableau[m], "|") == 0)continue;
            if (strcmp(storeTableau[m], "STOCK:") == 0)break;
            int tabC = strcmp(storeTableau[m], solitaireC[j]);
            if(tabC == 0){
                findC = 1;
                break;
            }
        }
        if(findC == 0){
            for(int k =0;k<60;k++){//check whether k in solitaireC exists in STOCK
                if(strcmp(storeStock[k], "line_end") == 0)continue;
                if (strcmp(storeStock[k], "|") == 0)continue;
                if(strcmp(storeStock[k], "MOVES:") == 0)break;
                int stoC = strcmp(storeStock[k], solitaireC[j]);
                if(stoC == 0){
                    findC = 1;
                    break;
                }
            }
        }
        if(findC == 0){
            strcpy(missing_Cards[missing], solitaireC[j]);//store missing cards
            missing++;
        }
    }

    for(int j =fou_indexD+1;j<13;j++){//search from after index "fou_indexD" in solitaireD
        int findD = 0;
        for(int m = 0; m<70;m++){//check whether m in solitaireD exists in TABLEAU
            if (strcmp(storeTableau[m], "line_end") == 0)continue;
            if (strcmp(storeTableau[m], "|") == 0)continue;
            if (strcmp(storeTableau[m], "STOCK:") == 0)break;
            int tabD = strcmp(storeTableau[m], solitaireD[j]);
            if(tabD == 0){
                findD = 1;
                break;
            }
        }
        if(findD == 0){
            for(int k =0;k<70;k++){//check whether k in solitaireD exists in STOCK
                if(strcmp(storeStock[k], "line_end") == 0)continue;
                if (strcmp(storeStock[k], "|") == 0)continue;
                if(strcmp(storeStock[k], "MOVES:") == 0)break;
                int stoD = strcmp(storeStock[k], solitaireD[j]);
                if(stoD == 0){
                    findD = 1;
                    break;
                }
            }
        }
        if(findD == 0){
            strcpy(missing_Cards[missing], solitaireD[j]);//store missing cards
            missing++;
        }
    }
    for(int j =fou_indexH+1;j<13;j++){//search from after index "fou_indexH" in solitaireH
        int findH = 0;
        for(int m = 0; m<60;m++){//check whether m in solitaireH exists in TABLEAU
            if (strcmp(storeTableau[m], "line_end") == 0)continue;
            if (strcmp(storeTableau[m], "|") == 0)continue;
            if (strcmp(storeTableau[m], "STOCK:") == 0)break;
            int tabH = strcmp(storeTableau[m], solitaireH[j]);
            if(tabH == 0){
                findH = 1;
                break;
            }
        }
        if(findH == 0){
            for(int k =0;k<70;k++){//check whether k in solitaireH exists in STOCK
                if(strcmp(storeStock[k], "line_end") == 0)continue;
                if (strcmp(storeStock[k], "|") == 0)continue;
                if(strcmp(storeStock[k], "MOVES:") == 0)break;
                int stoH = strcmp(storeStock[k], solitaireH[j]);
                if(stoH == 0){
                    findH = 1;
                    break;
                }
            }
        }
        if(findH == 0){
            strcpy(missing_Cards[missing], solitaireH[j]);//store missing cards
            missing++;
        }
    }

    for(int j =fou_indexS+1;j<13;j++){//search from after index "fou_indexS" in solitaireS
        int findS = 0;
        for(int m = 0; m<70;m++){//check whether m in solitaireS exists in TABLEAU
            if (strcmp(storeTableau[m], "line_end") == 0)continue;
            if (strcmp(storeTableau[m], "|") == 0)continue;
            if (strcmp(storeTableau[m], "STOCK:") == 0)break;
            int tabS = strcmp(storeTableau[m], solitaireS[j]);
            if(tabS == 0){
                findS = 1;
                break;
            }
        }
        if(findS == 0){
            for(int k =0;k<70;k++){//check whether k in solitaireS exists in STOCK
                if(strcmp(storeStock[k], "line_end") == 0)continue;
                if (strcmp(storeStock[k], "|") == 0)continue;
                if(strcmp(storeStock[k], "MOVES:") == 0)break;
                int stoS = strcmp(storeStock[k], solitaireS[j]);
                if(stoS == 0){
                    findS = 1;
                    break;
                }
            }
        }
        if(findS == 0){
            strcpy(missing_Cards[missing], solitaireS[j]);//store missing cards
            missing++;
        }
    }
    return missing;
}

int check_table_rank(char s[40][20], int size){
    char line[size][20];
    for(int i = 0;i<size; i++){//copy strings in s to line
        strcpy(line[i], s[i]);
    }
    int j;
    for(j =0; j<size; j++){//read each string until "|"
        if(strcmp(line[j], "|") == 0)break;
    }
    if(j == size || (j+1) == size)return 0;
    if(j+1 < size){
        for(int k = j+1; k<size; k++){//check rank
            if(k+1==size)break;
            if(line[k][0] == '2' && line[k+1][0] !='A')return -1;
            if(line[k][0] == '3' && line[k+1][0] !='2')return -1;
            if(line[k][0] == '4' && line[k+1][0] !='3')return -1;
            if(line[k][0] == '5' && line[k+1][0] !='4')return -1;
            if(line[k][0] == '6' && line[k+1][0] !='5')return -1;
            if(line[k][0] == '7' && line[k+1][0] !='6')return -1;
            if(line[k][0] == '8' && line[k+1][0] !='7')return -1;
            if(line[k][0] == '9' && line[k+1][0] !='8')return -1;
            if(line[k][0] == 'T' && line[k+1][0] !='9')return -1;
            if(line[k][0] == 'J' && line[k+1][0] !='T')return -1;
            if(line[k][0] == 'Q' && line[k+1][0] !='J')return -1;
            if(line[k][0] == 'K' && line[k+1][0] !='Q')return -1;
        }
    }
    return 0;
}

int check_table_suit(char s[40][20], int size){
    char line[size][20];
    for(int i = 0;i<size; i++){//copy strings in s to line
        strcpy(line[i], s[i]);
    }
    int j;
    for(j =0; j<size; j++){//read each string until "|"
        if(strcmp(line[j], "|") == 0)break;
    }
    if(j == size || (j+1) == size)return 0;
    if(j+1 < size){
        for(int k = j+1; k<size; k++){//check color
            if(k+1==size)break;
            if(line[k][1]=='s' && line[k+1][1]=='c')return -1;
            if(line[k][1]=='c' && line[k+1][1]=='s')return -1;
            if(line[k][1]=='s' && line[k+1][1]=='s')return -1;
            if(line[k][1]=='c' && line[k+1][1]=='c')return -1;
            if(line[k][1]=='h' && line[k+1][1]=='d')return -1;
            if(line[k][1]=='d' && line[k+1][1]=='h')return -1;
            if(line[k][1]=='d' && line[k+1][1]=='d')return -1;
            if(line[k][1]=='h' && line[k+1][1]=='h')return -1;
        }
    }
    return 0;
}


