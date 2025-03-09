#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_correct(int rules[1200][2], int updates[200][25], int n_line){
    bool pass =false;
    for (int j = 0; j < 25 && updates[n_line][j] != 0; j++ ) {
        for (int k = j+1; k < 25 && updates[n_line][k] != 0; k++ ) {
            pass = false;
            int a = updates[n_line][j];
            int b = updates[n_line][k];

            int i = 0;
            while (rules[i][0] != 0) {
                if(rules[i][0] == a && rules[i][1] == b){
                    pass = true;
                    break;
                }
                i++;
            }
            if (!pass) return false;
        }
    }
    return true;
}

void reorganize(int rules[1200][2], int updates[200][25], int n_line){
    int index_score[25] = {0};
    int buff[25] = {0};

    for (int i = 0; i < 25; i++ ) {
        buff[i] = updates[n_line][i];
    }

    for (int i = 0; i < 25 && updates[n_line][i] != 0; i++ ) {
        for (int j = 0; j < 25 && updates[n_line][j] != 0; j++ ) {
            int a = updates[n_line][i];
            int b = updates[n_line][j];

            int k = 0;
            while (rules[k][0] != 0) {
                if(rules[k][0] == a && rules[k][1] == b){
                    index_score[j]++;
                    break;
                }
                k++;
            }
        }
    }
    for (int i = 0; i < 25 && buff[i] != 0; i++ ) {
        updates[n_line][index_score[i]] = buff[i];
    }
}

int get_middle_value(int updates[200][25], int n_line){
    int length = 0;
    for (int i = 0; i < 25 && updates[n_line][i] != 0; i++ ) {
        length++;
    }
    return updates[n_line][(length - 1) / 2];
}

void part_two(int rules[1200][2], int updates[200][25]){
    int result = 0;
    for (int i = 0; i < 200 && updates[i][0] != 0; i++) {
        bool pass = is_correct(rules, updates, i);
        if(!pass) {
            reorganize(rules, updates, i);
            result = result + get_middle_value(updates, i);
        }
    }
    printf("Part two result : %d\n", result);
}


void part_one(int rules[1200][2], int updates[200][25]){
    int result = 0;
    for (int i = 0; i < 200 && updates[i][0] != 0; i++) {
        bool pass = is_correct(rules, updates, i);
        if (pass) result = result + get_middle_value(updates, i);
    }
    printf("Part one result : %d\n", result);
}

int main(){
    FILE * file;
    if ((file = fopen("day_5/input.txt", "r")) == NULL) {
        return 1;
    }

    int rules[1200][2] = {0};
    int updates[200][25] = {0};
    char buff[80];

    int sequence = 0;
    int n_rule = 0;
    int n_update = 0;

    while (fgets(buff, 80, file) != NULL) {
        if(buff[0] == '\n'){
            sequence = 1;
            continue;
        }

        if (sequence == 0) {
            sscanf(buff, "%d|%d", &rules[n_rule][0], &rules[n_rule][1]);
            n_rule++;
        }else{
            char * token;
            token = strtok(buff, ",");

            int n_num = 0;
            while (token != NULL) {
                int num = atoi(token);
                updates[n_update][n_num] = num;
                n_num++;
                token = strtok(NULL, ",");
            }
            n_update++;

        }
    }

    fclose(file);

    part_one(rules, updates);
    part_two(rules, updates);

    return 0;
}
