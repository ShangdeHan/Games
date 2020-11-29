/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termbox.h>
#include "game.h"

int main(int argc, char *argv[]) {
    FILE *file1;
    FILE *input = stdin;
    RNG_seed = 0, def = 0, limit = 0, resetNum = 0;
    if(argc == 1){
        SearchAndStore(input);
        Store_RULES();
        Store_FOUNDATIONS();
        Store_TABLEAU();
        Store_STOCK();
        Store_MOVES();
        splitColumns();
        mergeData();
    }else if(argc == 2){
        file1 = fopen(argv[1], "r");
        SearchAndStore(file1);
        Store_RULES();
        Store_FOUNDATIONS();
        Store_TABLEAU();
        Store_STOCK();
        Store_MOVES();
        splitColumns();
        mergeData();
    }else{
        for(int m = 0; m<argc; m++){
            if(strcmp(argv[m], "-f") == 0){
                file1 = fopen(argv[m+1], "r");
                SearchAndStore(file1);
                Store_RULES();
                Store_FOUNDATIONS();
                Store_TABLEAU();
                Store_STOCK();
                Store_MOVES();
                splitColumns();
                mergeData();
            }
            if(strcmp(argv[m], "-s") == 0){
                RNG_seed = atoi(argv[m+1]);
                for(int i = 0; i<argc; i++){
                    if(strcmp(argv[i], "-1") == 0) def = 1;
                    if(strcmp(argv[i], "-3") == 0) def = 3;
                    if(strcmp(argv[i], "-l") == 0)
                        limit = atoi(argv[i+1]);
                }
                printf("%d\n", RNG_seed);
                printf("%d\n", def);
                printf("%d\n", limit);
                newgame(RNG_seed, def, limit);
                //printf("%s\n", "good");
            }
        }
    }
    struct node* head = NULL;
    head = insertAtTail(head, copyData);

    strcpy(arrays[0], "Q: quit");
    strcpy(arrays[1],"R: restart    U: undo move");
    strcpy(arrays[2], "  ");
    strcpy(arrays[3], ".: next card  r: reset stock");
    strcpy(arrays[4], "To move, press the source and");
    strcpy(arrays[5], "then destination(one of w, f");
    strcpy(arrays[6], "1, 2, 3, 4, 5, 6, 7)");

    tb_init();
    gameconfiguration(head->copyConfiguration);
    int a = tb_width();
    int b = tb_height();
    struct tb_event event;
    struct tb_event event2;
    for(;;){
        tb_set_cursor(0, 7);
        tb_present();
        tb_poll_event(&event);
        char ch1 = event.ch;
        char array[2];
        if(ch1 == 'Q'){
            tb_clear();
            break;
        }
        if(ch1 == 'R'){
            gameconfiguration(copyData);
            head = NULL;
            head = insertAtTail(head, copyData);
        }
        if(ch1 == 'U'){
            if(head->last != NULL){
                head = head->last;
                gameconfiguration(head->copyConfiguration);
                head->next = NULL;
            }
            continue;
        }
        head = insertAtTail(head, (*head).copyConfiguration);
        head = head->next;
        if(ch1 == 'r'){
            strcpy(array, "r");
            move(array, head->copyConfiguration);
            gameconfiguration(head->copyConfiguration);
            continue;
        }
        if(ch1 == '.'){
            strcpy(array, ".");
            move(array, head->copyConfiguration);
            gameconfiguration(head->copyConfiguration);
            continue;
        }
        int result1 = 0, result2 = 0;
        for(int i = 0; i<8; i++){
            if(ch1 == src[i]) result1 = 1;
        }
        if(result1 == 1){
            tb_poll_event(&event2);
            char ch2 = event2.ch;
            for(int i = 0; i<8; i++){
                if(ch2 == des[i]) result2 = 1;
            }
            if(result2 == 1){
                char array[4];
                array[0] = ch1;
                array[1] = '-';
                array[2] = '>';
                array[3] = ch2;
                array[4] = '\0';
                move(array, head->copyConfiguration);
                gameconfiguration(head->copyConfiguration);
            }
            if(ch2 == 'Q'){
                tb_clear();
                break;
            }
        }
    }
    tb_shutdown();
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

struct node* getNewNode(char str[9][55][9]){// initial new node

    struct node *newnode = (struct node *) malloc(sizeof(struct node));
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 54; j++) {
            strcpy(newnode->copyConfiguration[i][j], str[i][j]);
        }
    }
    newnode->last = NULL;
    newnode->next = NULL;
    return newnode;
}

struct node * insertAtTail(struct node* head, char str[9][55][9]){// insert node at tail
    struct node *temp = head;
    struct node *newNode = getNewNode(str);
    if (head == NULL) {
        head = newNode;
        return head;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->last = temp;
    return head;
}


int move(char str[10], char data[9][55][9]){
    char s[] = "1234567";
    int result1 = 0, result2 = 0, error = 0;
    int i;
    for(i = 0; i<7; i++){
        if(s[i] == str[0])result1 = 1;
        if(s[i] == str[3])result2 = 1;
    }
    if(strcmp(str, ".") == 0){
        if(strcmp(storeRules[1], "1") == 0)stockToWaste(data);
        if(strcmp(storeRules[1], "3") == 0){
            int j = 0, final = 0;
            while(strcmp(data[8][j], "|") != 0)j++;
            j++;
            while(strcmp(data[8][final], "MOVES:") != 0)final++;
            if(final - j >= 3){
                error = stockToWaste(data);
                if(error == 1)return error;
                error  = stockToWaste(data);
                if(error == 1)return error;
                error = stockToWaste(data);
            }else if(final - j == 2){
                error = stockToWaste(data);
                if(error == 1)return error;
                error = stockToWaste(data);
            }else if(final - j == 1){
                error = stockToWaste(data);
            }
        }
    }
    else if(strcmp(str, "r") == 0){
        if(strcmp(storeRules[2], "unlimited") == 0){
            error = stockReset(data);
        }
        else{
            int resetCount = atoi(storeRules[3]);
            if(resetCount > resetNum){
                error = stockReset(data);
                resetNum++;
            }
        }
    }
    else{
        if(result1 == 1 && result2 == 1){//from number to number
            error = moveInTableau(str, data);
        }else if(result1 == 1 && str[3]=='f'){
            error = movefromTtoF(str, data);
        }else if(str[0]=='w' && result2 == 1){
            error = movefromWtoT(str, data);
        }else if(str[0]=='w' && str[3] == 'f'){
            error = movefromWtoF(str, data);
        }
    }
    return error;
}

int stockToWaste(char data[9][55][9]){
    int i;
    for(i = 0; i<60; i++){
        if(strcmp(data[8][i], "|") == 0){
            if(strcmp(data[8][i+1], "MOVES:") == 0)return 1;
            char temp[10];
            strcpy(temp, data[8][i]);
            strcpy(data[8][i], data[8][i+1]);
            strcpy(data[8][i+1], temp);
            break;
        }
    }
    return 0;
}

int stockReset(char data[9][55][9]){
    int j = 0;
    if(strcmp(data[8][0], "|") == 0)return 1;
    if(strcmp(data[8][1], "|") == 0 && strcmp(data[8][2], "MOVES:") == 0)return 1;
    while(strcmp(data[8][j], "|") != 0)j++;
    if(strcmp(data[8][j+1], "MOVES:") != 0)return 1;
    char temp[10];
    char temp2[10];
    strcpy(temp, data[8][0]);
    strcpy(data[8][0], "|");
    int i = 1;
    while(strcmp(data[8][i], "|") != 0){
        strcpy(temp2, data[8][i]);
        strcpy(data[8][i], temp);
        strcpy(temp, temp2);
        i++;
    }
    strcpy(data[8][i], temp);
    return 0;
}

int moveInTableau(char str[10], char data[9][55][9]){
    int subtract = 0;
    int col_1 = str[0] - '0';// indicate from which column
    if(strcmp(data[col_1][0], "|") == 0 && strcmp(data[col_1][1], "line_end") == 0)return 1;
    int col_2 = str[3] - '0';// indicate to which column
    int k =0;
    while(strcmp(data[col_2][k], "line_end") != 0)k++;//find last element index in target column
    int j = 0;
    while(strcmp(data[col_1][j], "|") != 0)j++;//find "|" index in original column
    if(strcmp(data[col_2][1], "line_end") == 0 && data[col_1][j+1][0]!='K') return 1;
    int i = j+1;
    if(strcmp(data[col_1][i], "line_end") == 0) return 1;
    else{
        int num1;
        for(num1 = 0; num1<13; num1++){//find original rank
            if(order[num1] == data[col_1][i][0]) break;
        }
        if(strcmp(data[col_2][1], "line_end") != 0){
            int num2;
            for(num2 = 0; num2<13; num2++){//find target rank
                if(order[num2] == data[col_2][k-1][0]) break;
            }
            if(num2 - num1 > 1)return 1;
            if(num2 - num1 !=1 && strcmp(data[col_1][i+1], "line_end") == 0)return 1;
            if(num2 - num1 != 1){
                i = i+1;
                while(num2 - num1 !=1){
                    if(strcmp(data[col_1][i], "line_end") == 0)break;
                    for(num1 = 0; num1<13; num1++){//find original rank
                        if(order[num1] == data[col_1][i][0]) break;
                    }
                    if(num2 - num1 == 1)break;
                    i++;
                }
            }
            if(num2 - num1 != 1)return 1;
            if(strcmp(data[col_1][i], "line_end") == 0)return 1;
        }
    }
    subtract = i;
    if(strcmp(data[col_2][k-1], "|") != 0){//check suit
        if(check_suit(data[col_2][k-1], data[col_1][i]) == 1)return 1;
    }
    while(strcmp(data[col_1][i], "line_end") != 0 && strcmp(data[col_1][i], "") != 0){
        strcpy(data[col_2][k], data[col_1][i]);
        strcpy(data[col_2][k+1], "line_end");
        strcpy(data[col_1][i], "line_end");
        k++;
        i++;
    }
    if(j != 0 && subtract - j == 1){
        strcpy(data[col_1][j], data[col_1][j-1]);
        strcpy(data[col_1][j-1], "|");
    }
    return 0;
}

int movefromTtoF(char str[10], char data[9][55][9]) {
    int col = str[0] - '0';// indicate from which column
    if(strcmp(data[col][0], "|") == 0 && strcmp(data[col][1], "line_end") == 0)return 1;
    int i = 0;
    while (strcmp(data[col][i], "line_end") != 0)i++;//find "|" index in original column
    i = i - 1;
    int k = 0;
    while (data[0][k][1] != data[col][i][1])k++;    //check two cards color are same
    if(check_rank(data[0][k], data[col][i]) != 0)return 1;//check rank
    char temp[10];
    strcpy(temp, data[col][i]);
    strcpy(data[col][i], "line_end");
    strcpy(data[col][i+1], "");
    if(strcmp(data[col][i-1], "|") == 0){//if this move left "|", swap it with last element
        if(strcmp(data[col][0], "|") != 0){
            strcpy(data[col][i-1], data[col][i-2]);
            strcpy(data[col][i-2], "|");
        }
    }
    int j = 0;
    while (strcmp(data[0][j], "TABLEAU:") != 0) {//check FOUNDATION card color
        if (data[0][j][1] == temp[1]){
            strcpy(data[0][j], temp);
        }j++;
    }
    return 0;
}

int movefromWtoT(char str[10], char data[9][55][9]){
    if(strcmp(data[8][0], "|") == 0)return 1;
    else{
        int k = 0;
        while(strcmp(data[8][k], "|") != 0)k++;//find "|" in stock
        int col = str[3] - '0';// indicate to which column
        if(strcmp(data[col][1], "line_end") == 0 && data[8][k-1][0]!='K') return 1;
        int i = 0;
        while (strcmp(data[col][i], "line_end") != 0)i++;//find "line_end" index in original column
    */
/* check rank*//*

        if(strcmp(data[col][1], "line_end") != 0 && check_rank(data[8][k-1], data[col][i-1]) != 0)return 1;
    */
/* check color*//*

        if(strcmp(data[col][1], "line_end") != 0 && check_suit(data[8][k-1], data[col][i-1]) != 0)return 1;
        char temp[10];
        strcpy(temp, data[8][k-1]);
        strcpy(data[col][i], temp);
        strcpy(data[col][i+1], "line_end");//add waste card to column
        int j = k-1;
        char temp2[10];
        strcpy(temp2, "|");
        while(strcmp(data[8][j], "MOVES:") != 0){
            strcpy(data[8][j], temp2);
            strcpy(temp2, data[8][j+2]);
            j++;
        }
        strcpy(data[8][j], "");
    }
    return 0;
}

int movefromWtoF(char str[10], char data[9][55][9]){
    if(strcmp(data[8][0], "|") == 0)return 1;
    else{
        int k = 0;
        while(strcmp(data[8][k], "|") != 0)k++;
        int m = 0;
        while (data[0][m][1] != data[8][k-1][1])m++;//find F color
        if(check_rank(data[0][m], data[8][k-1]) != 0)return 1;//check rank
        int i = 0;
        while (strcmp(data[0][i], "TABLEAU:") != 0) {//check FOUNDATION card color
            if (data[0][i][1] == data[8][k-1][1]){
                strcpy(data[0][i], data[8][k-1]);
            }i++;
        }
        int j = k-1;
        char temp[10];
        strcpy(temp, "|");
        while(strcmp(data[8][j], "MOVES:") != 0){
            strcpy(data[8][j], temp);
            strcpy(temp, data[8][j+2]);
            j++;
        }
        strcpy(data[8][j], "");
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


void mergeData(){
    int i = 0, j = 0, k = 0;
    while(strcmp(storeFundations[i], "TABLEAU:") != 0){
        strcpy(copyData[0][i], storeFundations[i]);
        i++;
    }
    strcpy(copyData[0][i], storeFundations[i]);
    for(int m = 1; m<8; m++){
        j = 0;
        while(strcmp(columns[m][j], "line_end") != 0){
            strcpy(copyData[m][j], columns[m][j]);
            j++;
        }
        strcpy(copyData[m][j], columns[m][j]);
    }
    while(strcmp(storeStock[k], "MOVES:") != 0){
        strcpy(copyData[8][k], storeStock[k]);
        k++;
    }
    strcpy(copyData[8][k], storeStock[k]);
}


int suitToUnit(char s){
    if(s == 's') return 0x2660;
    if(s == 'h') return 0x2665;
    if(s == 'c') return 0x2663;
    if(s == 'd') return 0x2666;
}

void gameconfiguration(char data[9][55][9]){
    struct tb_cell cell;
    cell.bg = TB_BLACK;
    cell.fg = TB_BLACK;
    for(int m = 0 ; m<tb_width();m++) {
        for (int n = 0; n < tb_height(); n++) {
            cell.ch = ' ';
            tb_put_cell(m, n, &cell);
        }
    }
    cell.fg = TB_WHITE;
    cell.bg = TB_BLACK;
    int cx = 0, cy = 0, i, j;
    for(i=0 ; i<7; i++){
        for(j=0 ; j<35; j++){
            cell.ch = arrays[i][j];
            tb_put_cell(cx, cy, &cell);
            cx++;
        }
        cx = 0;
        cy++;
    }
    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;
    cell.ch = 'Q';
    tb_put_cell(0, 0, &cell);
    cell.ch = 'R';
    tb_put_cell(0, 1, &cell);
    cell.ch = 'U';
    tb_put_cell(14, 1, &cell);
    cell.ch = '.';
    tb_put_cell(0, 3, &cell);
    cell.ch = 'r';
    tb_put_cell(14, 3, &cell);
    cell.ch = '1';
    tb_put_cell(35, 0, &cell);
    cell.ch = '2';
    tb_put_cell(41, 0, &cell);
    cell.ch = '3';
    tb_put_cell(47, 0, &cell);
    cell.ch = '4';
    tb_put_cell(53, 0, &cell);
    cell.ch = '5';
    tb_put_cell(59, 0, &cell);
    cell.ch = '6';
    tb_put_cell(65, 0, &cell);
    cell.ch = '7';
    tb_put_cell(71, 0, &cell);

    strcpy(arrays[7], "foundations");
    cell.ch = arrays[7][0];
    tb_put_cell(10, 8, &cell);
    for(int i = 1; i<11; i++){
        cell.fg = TB_WHITE;
        cell.bg = TB_BLACK;
        cell.ch = arrays[7][i];
        tb_put_cell(i+10, 8, &cell);
    }

    strcpy(arrays[8], "waste ");
    cell.fg = TB_BLACK;
    cell.bg = TB_MAGENTA;
    cell.ch = arrays[8][0];
    tb_put_cell(5, 16, &cell);
    for(int i = 1; i<6; i++){
        cell.fg = TB_WHITE;
        cell.bg = TB_BLACK;
        cell.ch = arrays[8][i];
        tb_put_cell(i+5, 16, &cell);
    }
    if(strcmp(storeRules[2], "limit") == 0){
        int resetCount = atoi(storeRules[3]);
        int sub = resetCount - resetNum;
        cell.bg = TB_BLACK;
        cell.ch = sub+'0';
        tb_put_cell(11, 16, &cell);
        strcpy(arrays[9], "resets remaining");
        for(int i = 0; i<18; i++){
            cell.bg = TB_BLACK;
            cell.ch = arrays[9][i];
            tb_put_cell(i+13, 16, &cell);
        }
    }else{
        strcpy(arrays[9], "infinite resets remaining");
        for(int i = 0; i<28; i++){
            cell.bg = TB_BLACK;
            cell.ch = arrays[9][i];
            tb_put_cell(i+11, 16, &cell);
        }
    }

    int q = 0, x = 6, y = 10;
    while(strcmp(data[0][q], "TABLEAU:") != 0){//FOUNDATION
        for(int m = 0 ; m<4;m++) {
            for (int n = 0; n < 4; n++) {
                cell.bg = TB_WHITE;
                cell.ch = ' ';
                tb_put_cell(m + x, n + y, &cell);
            }
        }
        if(data[0][q][1] == 'c' || data[0][q][1] == 's')cell.fg = TB_BLACK;
        else cell.fg = TB_RED;
        cell.ch = data[0][q][0];
        tb_put_cell(x, y, &cell);
        tb_put_cell(x+3, y+3, &cell);
        cell.ch = suitToUnit(data[0][q][1]);
        tb_put_cell(x+1, y, &cell);
        tb_put_cell(x+2, y+3, &cell);
        q++;
        x = x+6;
    }
    q = 0, x = 8, y = 18;
    if(strcmp(data[8][0], "|") == 0){//STOCK
        cell.bg = TB_GREEN;
        for(int m = 0 ; m<4;m++) {
            for (int n = 0; n < 4; n++) {
                cell.ch = ' ';
                tb_put_cell(m + x, n + y, &cell);
            }
        }
        cell.bg = TB_BLACK;
        cell.fg = TB_WHITE;
        cell.ch = 0+'0';
        tb_put_cell(x+2, 4+y+1, &cell);
    }else{
        for(int m = 0 ; m<4;m++) {
            for (int n = 0; n < 4; n++) {
                cell.bg = TB_WHITE;
                cell.ch = ' ';
                tb_put_cell(m + x, n + y, &cell);
            }
        }
        while(strcmp(data[8][q], "|") != 0) q++;
        q = q-1;
        if(data[8][q][1] == 'c' || data[8][q][1] == 's')cell.fg = TB_BLACK;
        else cell.fg = TB_RED;
        cell.ch = data[8][q][0];
        tb_put_cell(x, y, &cell);
        tb_put_cell(x+3, y+3, &cell);
        cell.ch = suitToUnit(data[8][q][1]);
        tb_put_cell(x+1, y, &cell);
        tb_put_cell(x+2, y+3, &cell);
        cell.bg = TB_BLACK;
        cell.fg = TB_WHITE;
        cell.ch = 1+'0';
        tb_put_cell(x+1, 4+y+1, &cell);
        for(int m = 0 ; m<4;m++) {
            for (int n = 0; n < 4; n++) {
                cell.bg = TB_GREEN;
                cell.fg = TB_WHITE;
                cell.ch = '#';
                tb_put_cell(m + 18, n + 18, &cell);
            }
        }
        cell.bg = TB_BLACK;
        cell.fg = TB_WHITE;
        int a = 0, b = 0;
        while(strcmp(data[8][a], "|") != 0) a++;
        while(strcmp(data[8][b], "MOVES:") != 0) b++;
        int num = b-a-1;
        char sss[5];
        sprintf(sss, "%d", num);
        for(int i = 0; i<5; i++){
            cell.fg = TB_WHITE;
            cell.bg = TB_BLACK;
            cell.ch = sss[i];
            tb_put_cell(i+19, 23, &cell);
        }

        if(strcmp(storeRules[1], "3") == 0){// turn 3
            if(q>=2){
                for(int m = 4; m > 0; m--) {
                    for (int n = 0; n < 4; n++) {
                        cell.bg = TB_WHITE;
                        cell.ch = ' ';
                        tb_put_cell(x - m, n + y, &cell);
                    }
                }
                if(data[8][q-1][1] == 'c' || data[8][q-1][1] == 's')cell.fg = TB_BLACK;
                else cell.fg = TB_RED;
                cell.ch = data[8][q-1][0];
                tb_put_cell(x-2, y, &cell);
                cell.ch = suitToUnit(data[8][q-1][1]);
                tb_put_cell(x-1, y, &cell);
                if(data[8][q-2][1] == 'c' || data[8][q-2][1] == 's')cell.fg = TB_BLACK;
                else cell.fg = TB_RED;
                cell.ch = data[8][q-2][0];
                tb_put_cell(x-4, y, &cell);
                cell.ch = suitToUnit(data[8][q-2][1]);
                tb_put_cell(x-3, y, &cell);
                cell.bg = TB_BLACK;
                cell.fg = TB_WHITE;
                cell.ch = 3+'0';
                tb_put_cell(x+1, 4+y+1, &cell);
            }else if(q==1){
                for(int m = 2; m > 0; m--) {
                    for (int n = 0; n < 4; n++) {
                        cell.bg = TB_WHITE;
                        cell.ch = ' ';
                        tb_put_cell(x - m, n + y, &cell);
                    }
                }
                if(data[8][q-1][1] == 'c' || data[8][q-1][1] == 's')cell.fg = TB_BLACK;
                else cell.fg = TB_RED;
                cell.ch = data[8][q-1][0];
                tb_put_cell(x-2, y, &cell);
                cell.ch = suitToUnit(data[8][q-1][1]);
                tb_put_cell(x-1, y, &cell);
                cell.bg = TB_BLACK;
                cell.fg = TB_WHITE;
                cell.ch = 2+'0';
                tb_put_cell(x+1, 4+y+1, &cell);
            }
        }
    }

    for(int k = 1; k<8; k++) {//TABLEAU
        cx = 34; cy = 1, j = 0;
        if(strcmp(data[k][0], "|") == 0 && strcmp(data[k][1], "line_end") == 0 ) continue;
            while (strcmp(data[k][j], "|") != 0) {
            for (int m = 0; m < 4; m++) {
                cell.bg = TB_GREEN;
                cell.fg = TB_WHITE;
                cell.ch = '#';
                tb_put_cell(cx + (k - 1) * 6 + m, cy, &cell);
            }
            cy++;
            j++;
        }
        j++;
        while (strcmp(data[k][j], "line_end") != 0) {
            for (int m = 0; m < 4; m++) {
                cell.bg = TB_WHITE;
                cell.ch = ' ';
                tb_put_cell(cx + (k - 1) * 6 + m, cy, &cell);
            }
            if(data[k][j][1] == 'c' || data[k][j][1] == 's')cell.fg = TB_BLACK;
            else cell.fg = TB_RED;
            cell.ch = data[k][j][0];
            tb_put_cell(cx + (k - 1) * 6, cy, &cell);
            cell.ch = suitToUnit(data[k][j][1]);
            tb_put_cell(cx + 1 + (k - 1) * 6, cy, &cell);
            cy++;
            j++;
        }
        if(strcmp(data[k][j], "line_end") == 0){
            for(int m = 0 ; m<4;m++) {
                for (int n = 0; n < 3; n++) {
                    cell.bg = TB_WHITE;
                    cell.ch = ' ';
                    tb_put_cell(cx + (k - 1) * 6 + m, cy + n, &cell);
                }
            }
            if(data[k][j-1][1] == 'c' || data[k][j-1][1] == 's')cell.fg = TB_BLACK;
            else cell.fg = TB_RED;
            cell.ch = data[k][j-1][0];
            tb_put_cell(3 + cx + (k - 1) * 6, cy+2, &cell);
            cell.ch = suitToUnit(data[k][j-1][1]);
            tb_put_cell(2 + cx + 1 + (k - 1) * 6, cy+2, &cell);
        }
    }
}

void shuffle(int* deck)
{
    int temp;
    int i;
    for (i=0; i<51; i++) {
        int j = choose_randomly_between(i, 51);
        if (i != j) {
            temp = deck[i];
            deck[i] = deck[j];
            deck[j] = temp;
        }
    }
}

int choose_randomly_between(int a, int b)
{
    return a + ( (b-a+1) * Random() );
}

double Random()
{
    const unsigned long MODULUS = 2147483647;
    const unsigned long MULTIPLIER = 48271;
    const unsigned long Q = MODULUS / MULTIPLIER;
    const unsigned long R = MODULUS % MULTIPLIER;
    unsigned long t1 = MULTIPLIER * (RNG_seed % Q);
    unsigned long t2 = R * (RNG_seed / Q);
    if (t1 > t2) {
        RNG_seed = t1 - t2;
    } else {
        RNG_seed = t1 + (MODULUS - t2);
    }
    return ((double)RNG_seed / MODULUS);
}

void newgame(int seed, int defa, int limited){

    strcpy(storeRules[0], "turn");
    if(defa == 0 || defa == 1){
        strcpy(storeRules[1], "1");
    }else{
        char ary[2];
        sprintf(ary, "%d", defa);
        strcpy(storeRules[1], ary);
    }
    if(limit == 0){
        strcpy(storeRules[2], "unlimited");
        strcpy(storeRules[3], "FOUNDATIONS:");
    }else{
        char ary[5];
        sprintf(ary, "%d", limited);
        strcpy(storeRules[2], "limit");
        strcpy(storeRules[3], ary);
        strcpy(storeRules[4], "FOUNDATIONS:");
    }

    int deck[53];
    int m = 0;
    for (m=0; m<52; m++) deck[m] = m+1;
    shuffle(deck);
    char new[53][3];
    int i, j = 0;
    for(i = 0; i<52; i++){
        if(deck[i] == 1) strcpy(new[j], "Ac");
        else if(deck[i] == 2) strcpy(new[j], "2c");
        else if(deck[i] == 3) strcpy(new[j], "3c");
        else if(deck[i] == 4) strcpy(new[j], "4c");
        else if(deck[i] == 5) strcpy(new[j], "5c");
        else if(deck[i] == 6) strcpy(new[j], "6c");
        else if(deck[i] == 7) strcpy(new[j], "7c");
        else if(deck[i] == 8) strcpy(new[j], "8c");
        else if(deck[i] == 9) strcpy(new[j], "9c");
        else if(deck[i] == 10) strcpy(new[j], "Tc");
        else if(deck[i] == 11) strcpy(new[j], "Jc");
        else if(deck[i] == 12) strcpy(new[j], "Qc");
        else if(deck[i] == 13) strcpy(new[j], "Kc");
        else if(deck[i] == 14) strcpy(new[j], "Ad");
        else if(deck[i] == 15) strcpy(new[j], "2d");
        else if(deck[i] == 16) strcpy(new[j], "3d");
        else if(deck[i] == 17) strcpy(new[j], "4d");
        else if(deck[i] == 18) strcpy(new[j], "5d");
        else if(deck[i] == 19) strcpy(new[j], "6d");
        else if(deck[i] == 20) strcpy(new[j], "7d");
        else if(deck[i] == 21) strcpy(new[j], "8d");
        else if(deck[i] == 22) strcpy(new[j], "9d");
        else if(deck[i] == 23) strcpy(new[j], "Td");
        else if(deck[i] == 24) strcpy(new[j], "Jd");
        else if(deck[i] == 25) strcpy(new[j], "Qd");
        else if(deck[i] == 26) strcpy(new[j], "Kd");
        else if(deck[i] == 27) strcpy(new[j], "Ah");
        else if(deck[i] == 28) strcpy(new[j], "2h");
        else if(deck[i] == 29) strcpy(new[j], "3h");
        else if(deck[i] == 30) strcpy(new[j], "4h");
        else if(deck[i] == 31) strcpy(new[j], "5h");
        else if(deck[i] == 32) strcpy(new[j], "6h");
        else if(deck[i] == 33) strcpy(new[j], "7h");
        else if(deck[i] == 34) strcpy(new[j], "8h");
        else if(deck[i] == 35) strcpy(new[j], "9h");
        else if(deck[i] == 36) strcpy(new[j], "Th");
        else if(deck[i] == 37) strcpy(new[j], "Jh");
        else if(deck[i] == 38) strcpy(new[j], "Qh");
        else if(deck[i] == 39) strcpy(new[j], "Kh");
        else if(deck[i] == 40) strcpy(new[j], "As");
        else if(deck[i] == 41) strcpy(new[j], "2s");
        else if(deck[i] == 42) strcpy(new[j], "3s");
        else if(deck[i] == 43) strcpy(new[j], "4s");
        else if(deck[i] == 44) strcpy(new[j], "5s");
        else if(deck[i] == 45) strcpy(new[j], "6s");
        else if(deck[i] == 46) strcpy(new[j], "7s");
        else if(deck[i] == 47) strcpy(new[j], "8s");
        else if(deck[i] == 48) strcpy(new[j], "9s");
        else if(deck[i] == 49) strcpy(new[j], "Ts");
        else if(deck[i] == 50) strcpy(new[j], "Js");
        else if(deck[i] == 51) strcpy(new[j], "Qs");
        else if(deck[i] == 52) strcpy(new[j], "Ks");
        j++;
    }

    memset(copyData[8][0], '0', 5);
    strcpy(copyData[0][0], "_c");
    strcpy(copyData[0][1], "_d");
    strcpy(copyData[0][2], "_h");
    strcpy(copyData[0][3], "_s");
    strcpy(copyData[0][4], "TABLEAU:");

    strcpy(copyData[1][0], "|");
    strcpy(copyData[1][1], new[0]);
    strcpy(copyData[1][2], "line_end");
    strcpy(copyData[2][0], new[1]);
    strcpy(copyData[2][1], "|");
    strcpy(copyData[2][2], new[2]);
    strcpy(copyData[2][3], "line_end");
    strcpy(copyData[3][0], new[3]);
    strcpy(copyData[3][1], new[4]);
    strcpy(copyData[3][2], "|");
    strcpy(copyData[3][3], new[5]);
    strcpy(copyData[3][4], "line_end");
    strcpy(copyData[4][0], new[6]);
    strcpy(copyData[4][1], new[7]);
    strcpy(copyData[4][2], new[8]);
    strcpy(copyData[4][3], "|");
    strcpy(copyData[4][4], new[9]);
    strcpy(copyData[4][5], "line_end");
    strcpy(copyData[5][0], new[10]);
    strcpy(copyData[5][1], new[11]);
    strcpy(copyData[5][2], new[12]);
    strcpy(copyData[5][3], new[13]);
    strcpy(copyData[5][4], "|");
    strcpy(copyData[5][5], new[14]);
    strcpy(copyData[5][6], "line_end");
    strcpy(copyData[6][0], new[15]);
    strcpy(copyData[6][1], new[16]);
    strcpy(copyData[6][2], new[17]);
    strcpy(copyData[6][3], new[18]);
    strcpy(copyData[6][4], new[19]);
    strcpy(copyData[6][5], "|");
    strcpy(copyData[6][6], new[20]);
    strcpy(copyData[6][7], "line_end");
    strcpy(copyData[7][0], new[21]);
    strcpy(copyData[7][1], new[22]);
    strcpy(copyData[7][2], new[23]);
    strcpy(copyData[7][3], new[24]);
    strcpy(copyData[7][4], new[25]);
    strcpy(copyData[7][5], new[26]);
    strcpy(copyData[7][6], "|");
    strcpy(copyData[7][7], new[27]);
    strcpy(copyData[7][8], "line_end");

    char s[2];
    strcpy(s, "|");
    strcpy(copyData[8][0], s);
    int q = 1;
    for(int k = 28; k<52; k++){
        strcpy(copyData[8][q], new[k]);
        q++;
    }
    strcpy(copyData[8][q], "MOVES:");

}*/
