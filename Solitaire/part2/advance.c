#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "advance.h"

int main(int argc, char *argv[]) {
    int moveNumber, result2 = 0, result3 = 0, result4 = 0;
    FILE *file1;
    FILE *input = stdin;
    FILE* outfile;
    if(argc == 1){
        SearchAndStore(input);
    }else if(argc == 2){
        file1 = fopen(argv[1], "r");
        SearchAndStore(file1);
    }else{
        int m, mNum = 0, count = 0, xNum = 0, oNum = 0;
        int s[2];
        for(m = 0; m<argc; m++){
            if(strcmp(argv[m], "-m") == 0)mNum = m;
            if(strcmp(argv[m], "-x") == 0)xNum = m;
            if(strcmp(argv[m], "-o") == 0)oNum = m;
            if(strstr(argv[m], ".txt") != NULL)s[count] = m, count++;
        }
        file1 = fopen(argv[s[0]], "r");
        SearchAndStore(file1);
        if(mNum != 0)moveNumber = atoi(argv[mNum+1]), result2 = 1;
        if(oNum != 0)outfile = fopen(argv[s[1]], "w"), result3 = 1;
        if(xNum != 0)result4 = 1;
    }
//    FILE* file = fopen("C:\\Users\\shangde\\Desktop\\327part\\testmoves5.txt", "r");
//    int result = SearchAndStore(file);
    Store_RULES();
    Store_FOUNDATIONS();
    Store_TABLEAU();
    Store_STOCK();
    Store_MOVES();
    splitColumns();
    int q = 0, Tcount = 0;
    while(strcmp(storeTableau[q], "STOCK:") != 0){//check many "|" in TABLEAU
        if(strcmp(storeTableau[q], "|") == 0) Tcount++;
        q++;
    }if(Tcount!=7){
        fprintf(stderr, "Invalid input in columns \n");
        exit(1);
    }
    int h = 0, Scount = 0;
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
        exit(1);
    }
    int misNums = checkMissingcard();
    if(misNums != 0){
        printf("%s", "Missing cards: ");
        for(int i =0;i<misNums;i++){
            printf("%s ", missing_Cards[i]);
        }
        printf("\n");
        exit(1);
    }
    int moveCount = 0, error = 0, resetCount = 0;
    resetNum = 0;
    if(strcmp(storeRules[2], "limit") == 0) resetCount = atoi(storeRules[3]);
    if(result2 == 0){
        while(strcmp(storeMoves[moveCount], "all_end") != 0){
            if(strcmp(storeRules[2], "limit") == 0 && strcmp(storeMoves[moveCount], "r") == 0){
                if(resetNum>= resetCount){
                    error = 1;
                    break;
                }
            }
            error = move(storeMoves[moveCount]);
            if(error == 1) break;
            moveCount++;
        }
        if(result3 == 1 && result4 == 0)showToFile(moveCount, error, outfile), fclose(outfile);
        else if(result3 == 1 && result4 == 1)showExchangeFormatToFile(moveCount, error, outfile), fclose(outfile);
        else if(result3 == 0 && result4 == 1)showExchangeFormat(moveCount, error);
        else if(result3 == 0 && result4 == 0)show(moveCount, error);
    }else{
        for(moveCount = 0; moveCount<moveNumber; moveCount++){
            if(strcmp(storeMoves[moveCount], "all_end") == 0)break;
            if(strcmp(storeRules[2], "limit") == 0 && strcmp(storeMoves[moveCount], "r") == 0){
                if(resetNum>= resetCount){
                    error = 1;
                    break;
                }
            }
            error = move(storeMoves[moveCount]);
            if(error == 1) break;
        }
        if(result3 == 1 && result4 == 0)showToFile(moveCount, error, outfile), fclose(outfile);
        else if(result3 == 1 && result4 == 1)showExchangeFormatToFile(moveCount, error, outfile), fclose(outfile);
        else if(result3 == 0 && result4 == 1)showExchangeFormat(moveCount, error);
        else if(result3 == 0 && result4 == 0)show(moveCount, error);
    }
    if(argc != 1)fclose(file1);
    if(argc == 1)fclose(input);
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
        if(strstr(temp, "MOVES:")!= NULL)between_TabAndStock = 2;//when read MOVES:,
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

            if(between_TabAndStock == 2){
                char s[] = "1234567";
                int result1 = 0, result2 = 0, error = 0;
                int i;
                for(i = 0; i<7; i++){
                    if(s[i] == token[0])result1 = 1;
                    if(s[i] == token[3])result2 = 1;
                }
                if(strcmp(token, ".") == 0);
                else if(strcmp(token, "MOVES:") == 0);
                else if(strcmp(token, "r") == 0);
                else if(result1 == 1 && result2 == 1 && token[1] == '-' && token[2] == '>');
                else if(result1 == 1 && token[3]=='f'&& token[1] == '-' && token[2] == '>');
                else if(token[0]=='w' && result2 == 1&& token[1] == '-' && token[2] == '>');
                else if(token[0]=='w' && token[3] == 'f'&& token[1] == '-' && token[2] == '>');
                else{
                    fprintf(stderr, "formatting error in MOVES near line: %d\n", line);
                    exit(1);
                }
            }
            token = strtok(NULL, space);
            iter++;
            num++;
        }
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
            while(strcmp(storeAll[i], "FOUNDATIONS:") != 0) {
                if(strcmp(storeAll[i], "line_end") == 0){
                    i++;
                    continue;
                }
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

void Store_MOVES(){
    int i;
    int movesIndex = 0;
    for(i = 0; i<500;i++){
        if(strcmp(storeAll[i], "MOVES:") == 0){
            i = i + 1;
            while(strcmp(storeAll[i], "all_end") != 0) {
                if(strcmp(storeAll[i], "line_end") == 0){
                    i++;
                    continue;
                }
                strcpy(storeMoves[movesIndex], storeAll[i]);
                movesIndex++;
                i++;
            }
        }
        if(strcmp(storeAll[i], "all_end") == 0){
            strcpy(storeMoves[movesIndex], storeAll[i]);
            break;
        }
    }
}






int move(char str[10]){
    char s[] = "1234567";
    int result1 = 0, result2 = 0, error = 0;
    int i;
    for(i = 0; i<7; i++){
        if(s[i] == str[0])result1 = 1;
        if(s[i] == str[3])result2 = 1;
    }
    if(strcmp(str, ".") == 0){
        if(strcmp(storeRules[1], "1") == 0)stockToWaste();
        if(strcmp(storeRules[1], "3") == 0){
            int j = 0, final = 0;
            while(strcmp(storeStock[j], "|") != 0)j++;
            j++;
            while(strcmp(storeStock[final], "MOVES:") != 0)final++;
            if(final - j >= 3){
                error = stockToWaste();
                if(error == 1)return error;
                error  = stockToWaste();
                if(error == 1)return error;
                error = stockToWaste();
            }else if(final - j == 2){
                error = stockToWaste();
                if(error == 1)return error;
                error = stockToWaste();
            }else if(final - j == 1){
                error = stockToWaste();
            }
        }
    }
    else if(strcmp(str, "r") == 0){
        if(strcmp(storeRules[2], "unlimited") == 0){
            error = stockReset();
        }
        else{
            resetNum++;
            error = stockReset();
        }
    }
    else{
        if(result1 == 1 && result2 == 1){//from number to number
            error = moveInTableau(str);
        }else if(result1 == 1 && str[3]=='f'){
            error = movefromTtoF(str);
        }else if(str[0]=='w' && result2 == 1){
            error = movefromWtoT(str);
        }else if(str[0]=='w' && str[3] == 'f'){
            error = movefromWtoF(str);
        }
    }
    return error;
}

int stockToWaste(){
    int i;
    for(i = 0; i<60; i++){
        if(strcmp(storeStock[i], "|") == 0){
            if(strcmp(storeStock[i+1], "MOVES:") == 0)return 1;
            char temp[10];
            strcpy(temp, storeStock[i]);
            strcpy(storeStock[i], storeStock[i+1]);
            strcpy(storeStock[i+1], temp);
            break;
        }
    }
    return 0;
}

int stockReset(){
    int j = 0;
    while(strcmp(storeStock[j], "|") != 0)j++;
    if(strcmp(storeStock[j+1], "MOVES:") != 0)return 1;
    if(j == 0 && strcmp(storeStock[1], "MOVES:") == 0)return 1;
    char temp[10];
    char temp2[10];
    strcpy(temp, storeStock[0]);
    strcpy(storeStock[0], "|");
    int i = 1;
    while(strcmp(storeStock[i], "|") != 0){
        strcpy(temp2, storeStock[i]);
        strcpy(storeStock[i], temp);
        strcpy(temp, temp2);
        i++;
    }
    strcpy(storeStock[i], temp);
    return 0;
}

void splitColumns(){
    int i = 0;
    int j = 0;
    int a = 7;//from column7 to column1
    while(strcmp(storeTableau[j], "STOCK:") != 0){
        int i = 0;
        while(strcmp(storeTableau[j], "line_end") != 0){
            if(strcmp(storeTableau[j], "STOCK:") == 0) return;
            strcpy(columns[a][i], storeTableau[j]);
            i++;
            j++;
        }
        strcpy(columns[a][i], storeTableau[j]);
        j++;
        a--;
    }
}

int moveInTableau(char str[10]){
    int subtract = 0;
    int col_1 = str[0] - '0';// indicate from which column
    int col_2 = str[3] - '0';// indicate to which column
    int k =0;
    while(strcmp(columns[col_2][k], "line_end") != 0)k++;//find last element index in target column
    int j = 0;
    while(strcmp(columns[col_1][j], "|") != 0)j++;//find "|" index in original column
    if(strcmp(columns[col_2][1], "line_end") == 0 && columns[col_1][j+1][0]!='K') return 1;
    int i = j+1;
    if(strcmp(columns[col_1][i], "line_end") == 0) return 1;
    else{
        int num1;
        for(num1 = 0; num1<13; num1++){//find original rank
            if(order[num1] == columns[col_1][i][0]) break;
        }
        if(strcmp(columns[col_2][1], "line_end") != 0){
            int num2;
            for(num2 = 0; num2<13; num2++){//find target rank
                if(order[num2] == columns[col_2][k-1][0]) break;
            }
            if(num2 - num1 > 1)return 1;
            if(num2 - num1 !=1 && strcmp(columns[col_1][i+1], "line_end") == 0)return 1;
            if(num2 - num1 != 1){
                i = i+1;
                while(num2 - num1 !=1){
                    if(strcmp(columns[col_1][i], "line_end") == 0)break;
                    for(num1 = 0; num1<13; num1++){//find original rank
                        if(order[num1] == columns[col_1][i][0]) break;
                    }
                    if(num2 - num1 == 1)break;
                    i++;
                }
            }
            if(num2 - num1 != 1)return 1;
            if(strcmp(columns[col_1][i], "line_end") == 0)return 1;
        }
    }
    subtract = i;
    if(strcmp(columns[col_2][k-1], "|") != 0){//check suit
        if(check_suit(columns[col_2][k-1], columns[col_1][i]) == 1)return 1;
    }
    while(strcmp(columns[col_1][i], "line_end") != 0 && strcmp(columns[col_1][i], "") != 0){
        strcpy(columns[col_2][k], columns[col_1][i]);
        strcpy(columns[col_2][k+1], "line_end");
        strcpy(columns[col_1][i], "line_end");
        k++;
        i++;
    }
    if(j != 0 && subtract - j == 1){
        strcpy(columns[col_1][j], columns[col_1][j-1]);
        strcpy(columns[col_1][j-1], "|");
    }
    return 0;
}

int movefromTtoF(char str[10]) {
    int col = str[0] - '0';// indicate from which column
    int i = 0;
    while (strcmp(columns[col][i], "line_end") != 0)i++;//find "|" index in original column
    i = i - 1;
    int k = 0;
    while (storeFundations[k][1] != columns[col][i][1])k++;    //check two cards color are same
    if(check_rank(storeFundations[k], columns[col][i]) != 0)return 1;//check rank
    char temp[10];
    strcpy(temp, columns[col][i]);
    strcpy(columns[col][i], "line_end");
    strcpy(columns[col][i+1], "");
    if(strcmp(columns[col][i-1], "|") == 0){//if this move left "|", swap it with last element
        if(strcmp(columns[col][0], "|") != 0){
            strcpy(columns[col][i-1], columns[col][i-2]);
            strcpy(columns[col][i-2], "|");
        }
    }
    int j = 0;
    while (strcmp(storeFundations[j], "TABLEAU:") != 0) {//check FOUNDATION card color
        if (storeFundations[j][1] == temp[1]){
            strcpy(storeFundations[j], temp);
        }j++;
    }
    return 0;
}

int movefromWtoT(char str[10]){
    if(strcmp(storeStock[0], "|") == 0)return 1;
    else{
        int k = 0;
        while(strcmp(storeStock[k], "|") != 0)k++;//find "|" in stock
        int col = str[3] - '0';// indicate to which column
        if(strcmp(columns[col][1], "line_end") == 0 && storeStock[k-1][0]!='K') return 1;
        int i = 0;
        while (strcmp(columns[col][i], "line_end") != 0)i++;//find "line_end" index in original column
        /* check rank*/
        if(strcmp(columns[col][1], "line_end") != 0 && check_rank(storeStock[k-1], columns[col][i-1]) != 0)return 1;
        /* check color*/
        if(strcmp(columns[col][1], "line_end") != 0 && check_suit(storeStock[k-1], columns[col][i-1]) != 0)return 1;
        char temp[10];
        strcpy(temp, storeStock[k-1]);
        strcpy(columns[col][i], temp);
        strcpy(columns[col][i+1], "line_end");//add waste card to column
        int j = k-1;
        char temp2[10];
        strcpy(temp2, "|");
        while(strcmp(storeStock[j], "MOVES:") != 0){
            strcpy(storeStock[j], temp2);
            strcpy(temp2, storeStock[j+2]);
            j++;
        }
        strcpy(storeStock[j], "");
    }
    return 0;
}

int movefromWtoF(char str[10]){
    if(strcmp(storeStock[0], "|") == 0)return 1;
    else{
        int k = 0;
        while(strcmp(storeStock[k], "|") != 0)k++;
        int m = 0;
        while (storeFundations[m][1] != storeStock[k-1][1])m++;//find F color
        if(check_rank(storeFundations[m], storeStock[k-1]) != 0)return 1;//check rank
        int i = 0;
        while (strcmp(storeFundations[i], "TABLEAU:") != 0) {//check FOUNDATION card color
            if (storeFundations[i][1] == storeStock[k-1][1]){
                strcpy(storeFundations[i], storeStock[k-1]);
            }i++;
        }
        int j = k-1;
        char temp[10];
        strcpy(temp, "|");
        while(strcmp(storeStock[j], "MOVES:") != 0){
            strcpy(storeStock[j], temp);
            strcpy(temp, storeStock[j+2]);
            j++;
        }
        strcpy(storeStock[j], "");
    }
    return 0;
}


int check_suit(char s1[], char s2[]){
    if(s1[1]=='s' && s2[1]=='c')return 1;
    if(s1[1]=='c' && s2[1]=='s')return 1;
    if(s1[1]=='s' && s2[1]=='s')return 1;
    if(s1[1]=='c' && s2[1]=='c')return 1;
    if(s1[1]=='h' && s2[1]=='d')return 1;
    if(s1[1]=='d' && s2[1]=='h')return 1;
    if(s1[1]=='d' && s2[1]=='d')return 1;
    if(s1[1]=='h' && s2[1]=='h')return 1;
    return 0;
}

int check_rank(char s1[], char s2[]){
    int num1 = 0, num2 = 0;
    for(num1 = 0; num1<13; num1++){
        if(order[num1] == s1[0]) break;
    }
    for(num2 = 0; num2<13; num2++){
        if(order[num2] == s2[0]) break;
    }
    if(num2 - num1 == 1) return 0;
    else return 1;
}



void show(int count, int error){
    if(error == 1) printf("Move %d is illegal: %s \n", count+1, storeMoves[count]);
    else printf("Processed %d moves, all valid\n", count);
    printf("Foundations\n");
    int k = 0;
    while(strcmp(storeFundations[k], "TABLEAU:") != 0){
        printf("%s ", storeFundations[k]);
        k++;
    }
    printf("\nTableau\n");
    int i1 = 0, cover1 = 0, i2 = 0, cover2 = 0, i3 = 0, cover3 = 0, i4 = 0, cover4 = 0;
    int i5 = 0, cover5 = 0, i6 = 0, cover6 = 0, i7 = 0, cover7 = 0;
    while(strcmp(columns[1][i1], "line_end") != 0)i1++;
    while(strcmp(columns[1][cover1], "|") != 0)cover1++;
    while(strcmp(columns[2][i2], "line_end") != 0)i2++;
    while(strcmp(columns[2][cover2], "|") != 0)cover2++;
    while(strcmp(columns[3][i3], "line_end") != 0)i3++;
    while(strcmp(columns[3][cover3], "|") != 0)cover3++;
    while(strcmp(columns[4][i4], "line_end") != 0)i4++;
    while(strcmp(columns[4][cover4], "|") != 0)cover4++;
    while(strcmp(columns[5][i5], "line_end") != 0)i5++;
    while(strcmp(columns[5][cover5], "|") != 0)cover5++;
    while(strcmp(columns[6][i6], "line_end") != 0)i6++;
    while(strcmp(columns[6][cover6], "|") != 0)cover6++;
    while(strcmp(columns[7][i7], "line_end") != 0)i7++;
    while(strcmp(columns[7][cover7], "|") != 0)cover7++;
    int i, maxCount = i2;
    if(i1 > i2)maxCount = i1;
    if(i3 > i2)maxCount = i3;
    if(i4 > maxCount)maxCount = i4;
    if(i5 > maxCount)maxCount = i5;
    if(i6 > maxCount)maxCount = i6;
    if(i7 > maxCount)maxCount = i7;
    int p1 = cover1+1, p2 = cover2+1, p3 = cover3+1, p4 = cover4+1;
    int p5 = cover5+1, p6 = cover6+1, p7 = cover7+1;
    for(i = 0; i< maxCount-1; i++){
        if(i<cover1) printf("##" );
        else if(i < i1 && p1<i1) printf("%s ", columns[1][p1]), p1++;
        else printf(".. ");
        if(i<cover2) printf("## ");
        else if(i < i2 && p2<i2) printf("%s ", columns[2][p2]), p2++;
        else printf(".. ");
        if(i<cover3) printf("## ");
        else if(i < i3 && p3<i3) printf("%s ", columns[3][p3]), p3++;
        else printf(".. ");
        if(i<cover4) printf("## ");
        else if(i < i4 && p4<i4) printf("%s ", columns[4][p4]), p4++;
        else printf(".. ");
        if(i<cover5) printf("## ");
        else if(i < i5 && p5<i5) printf("%s ", columns[5][p5]), p5++;
        else printf(".. ");
        if(i<cover6) printf("## ");
        else if(i < i6 && p6<i6) printf("%s ", columns[6][p6]), p6++;
        else printf(".. ");
        if(i<cover7) printf("## ");
        else if(i < i7 && p7<i7) printf("%s ", columns[7][p7]), p7++;
        else printf(".. ");
        printf("\n");
    }
    printf("Waste top\n");
    int num = 0;
    while(strcmp(storeStock[num], "|") !=0) num++;
    if(strcmp(storeStock[0], "|") !=0){
        if(strcmp(storeRules[1], "1") == 0) printf("%s ", storeStock[num-1]);
        if(strcmp(storeRules[1], "3") == 0){
            if(num >= 3){
                printf("%s ", storeStock[num-3]);
                printf("%s ", storeStock[num-2]);
                printf("%s ", storeStock[num-1]);
            }else if(num == 2){
                printf("%s ", storeStock[num-2]);
                printf("%s ", storeStock[num-1]);
            }else if(num == 1){
                printf("%s ", storeStock[num-1]);
            }
        }
    }
    if(num != 0)printf("\n");
    if(num == 0)printf("(empty)\n");
}


void showToFile(int count, int error, FILE* file){
    if(error == 1) printf("Move %d is illegal: %s \n", count+1, storeMoves[count]);
    else printf("Processed %d moves, all valid\n", count);
    fprintf(file,"Foundations\n");
    int k = 0;
    while(strcmp(storeFundations[k], "TABLEAU:") != 0){
        fprintf(file,"%s ", storeFundations[k]);
        k++;
    }
    fprintf(file,"\nTableau\n");
    int i1 = 0, cover1 = 0, i2 = 0, cover2 = 0, i3 = 0, cover3 = 0, i4 = 0, cover4 = 0;
    int i5 = 0, cover5 = 0, i6 = 0, cover6 = 0, i7 = 0, cover7 = 0;
    while(strcmp(columns[1][i1], "line_end") != 0)i1++;
    while(strcmp(columns[1][cover1], "|") != 0)cover1++;
    while(strcmp(columns[2][i2], "line_end") != 0)i2++;
    while(strcmp(columns[2][cover2], "|") != 0)cover2++;
    while(strcmp(columns[3][i3], "line_end") != 0)i3++;
    while(strcmp(columns[3][cover3], "|") != 0)cover3++;
    while(strcmp(columns[4][i4], "line_end") != 0)i4++;
    while(strcmp(columns[4][cover4], "|") != 0)cover4++;
    while(strcmp(columns[5][i5], "line_end") != 0)i5++;
    while(strcmp(columns[5][cover5], "|") != 0)cover5++;
    while(strcmp(columns[6][i6], "line_end") != 0)i6++;
    while(strcmp(columns[6][cover6], "|") != 0)cover6++;
    while(strcmp(columns[7][i7], "line_end") != 0)i7++;
    while(strcmp(columns[7][cover7], "|") != 0)cover7++;
    int i, maxCount = i2;
    if(i1 > i2)maxCount = i1;
    if(i3 > i2)maxCount = i3;
    if(i4 > maxCount)maxCount = i4;
    if(i5 > maxCount)maxCount = i5;
    if(i6 > maxCount)maxCount = i6;
    if(i7 > maxCount)maxCount = i7;
    int p1 = cover1+1, p2 = cover2+1, p3 = cover3+1, p4 = cover4+1;
    int p5 = cover5+1, p6 = cover6+1, p7 = cover7+1;
    for(i = 0; i< maxCount-1; i++){
        if(i<cover1) fprintf(file,"##" );
        else if(i < i1 && p1<i1) fprintf(file,"%s ", columns[1][p1]), p1++;
        else fprintf(file,".. ");
        if(i<cover2) fprintf(file,"## ");
        else if(i < i2 && p2<i2) fprintf(file,"%s ", columns[2][p2]), p2++;
        else fprintf(file,".. ");
        if(i<cover3) fprintf(file,"## ");
        else if(i < i3 && p3<i3) fprintf(file,"%s ", columns[3][p3]), p3++;
        else fprintf(file,".. ");
        if(i<cover4) fprintf(file,"## ");
        else if(i < i4 && p4<i4) fprintf(file, "%s ", columns[4][p4]), p4++;
        else fprintf(file,".. ");
        if(i<cover5) fprintf(file,"## ");
        else if(i < i5 && p5<i5) fprintf(file,"%s ", columns[5][p5]), p5++;
        else fprintf(file,".. ");
        if(i<cover6) fprintf(file,"## ");
        else if(i < i6 && p6<i6) fprintf(file,"%s ", columns[6][p6]), p6++;
        else fprintf(file,".. ");
        if(i<cover7) fprintf(file,"## ");
        else if(i < i7 && p7<i7) fprintf(file,"%s ", columns[7][p7]), p7++;
        else fprintf(file,".. ");
        fprintf(file,"\n");
    }
    fprintf(file,"Waste top\n");
    int num = 0;
    while(strcmp(storeStock[num], "|") !=0) num++;
    if(strcmp(storeStock[0], "|") !=0){
        if(strcmp(storeRules[1], "1") == 0) fprintf(file,"%s ", storeStock[num-1]);
        if(strcmp(storeRules[1], "3") == 0){
            if(num >= 3){
                fprintf(file,"%s ", storeStock[num-3]);
                fprintf(file,"%s ", storeStock[num-2]);
                fprintf(file,"%s ", storeStock[num-1]);
            }else if(num == 2){
                fprintf(file,"%s ", storeStock[num-2]);
                fprintf(file,"%s ", storeStock[num-1]);
            }else if(num == 1){
                fprintf(file,"%s ", storeStock[num-1]);
            }
        }
    }
    if(num != 0)fprintf(file,"\n");
    if(num == 0)fprintf(file,"(empty)\n");
}

void showExchangeFormat(int count, int error){
    if(error == 1) printf("Move %d is illegal: %s \n", count+1, storeMoves[count]);
    else printf("Processed %d moves, all valid\n", count);
    printf("RULES:\n");
    printf("  %s %s\n", storeRules[0], storeRules[1]);
    if(strcmp(storeRules[2], "unlimited") == 0)printf("  %s\n", storeRules[2]);
    if(strcmp(storeRules[2], "limit") == 0)printf("  %s %s\n", storeRules[2], storeRules[3]);
    printf("FOUNDATIONS:\n");
    for(int i = 0; i<4;i++)printf("  %s\n", storeFundations[i]);
    printf("TABLEAU:\n");
    for(int j = 7; j>0;j--){
        printf("  ");
        int m = 0;
        while(strcmp(columns[j][m], "line_end") != 0)printf("%s ", columns[j][m]), m++;
        printf("\n");
    }
    printf("STOCK:\n");
    int k = 0;
    while(strcmp(storeStock[k], "MOVES:") != 0)printf("%s ", storeStock[k]), k++;
    printf("\nMOVES:\n");
}

void showExchangeFormatToFile(int count, int error, FILE* file){
    if(error == 1) printf("Move %d is illegal: %s \n", count+1, storeMoves[count]);
    else printf("Processed %d moves, all valid\n", count);
    fprintf(file, "RULES:\n");
    fprintf(file,"  %s %s\n", storeRules[0], storeRules[1]);
    if(strcmp(storeRules[2], "unlimited") == 0)fprintf(file,"  %s\n", storeRules[2]);
    if(strcmp(storeRules[2], "limit") == 0)fprintf(file,"  %s %s\n", storeRules[2], storeRules[3]);
    fprintf(file,"FOUNDATIONS:\n");
    for(int i = 0; i<4;i++)fprintf(file,"  %s\n", storeFundations[i]);
    fprintf(file,"TABLEAU:\n");
    for(int j = 7; j>0;j--){
        fprintf(file,"  ");
        int m = 0;
        while(strcmp(columns[j][m], "line_end") != 0)fprintf(file,"%s ", columns[j][m]), m++;
        fprintf(file, "\n");
    }
    fprintf(file,"STOCK:\n");
    int k = 0;
    while(strcmp(storeStock[k], "MOVES:") != 0)fprintf(file,"%s ", storeStock[k]), k++;
    fprintf(file,"\nMOVES:\n");
}
