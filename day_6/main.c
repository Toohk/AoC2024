#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define lx 130
#define ly 130

typedef struct Vec2{
    int x;
    int y;
}vec2;

void display_map(char map[lx][ly]){
    printf("\n\n\n");
    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

int run_sequence(char map[lx][ly], vec2 pos){
    bool moving = true;
    int loop_score = 0;
    while (moving && loop_score < 4) {
        loop_score = 0;

        if(map[pos.x-1][pos.y]== 'X') loop_score++;
        while (map[pos.x-1][pos.y] != '#') {
            if(pos.x -1 < 0){ moving = false; break;}
            pos.x = pos.x -1;
            map[pos.x][pos.y] = 'X';
        }
        if(!moving) break;

        if(map[pos.x][pos.y+1]== 'X') loop_score++;
        while (map[pos.x][pos.y+1] != '#') {
            if(pos.y +1 > ly -1){ moving = false; break;}
            pos.y = pos.y +1;
            map[pos.x][pos.y] = 'X';
        }
        if(!moving) break;

        if(map[pos.x+1][pos.y]== 'X') loop_score++;
        while (map[pos.x+1][pos.y] != '#') {
            if(pos.x +1 > lx -1){ moving = false; break;}
            pos.x = pos.x +1;
            map[pos.x][pos.y] = 'X';
        }
        if(!moving) break;

        if(map[pos.x][pos.y-1]== 'X') loop_score++;
        while (map[pos.x][pos.y-1] != '#') {
            if(pos.y -1 < 0){ moving = false; break;}
            pos.y = pos.y -1;
            map[pos.x][pos.y] = 'X';
        }
        if(!moving) break;

        //if(loop_score > 3) printf("alert\n");
    }
    if(loop_score >=4) return 1;
    return 0;
}


void part_two(char map[lx][ly], vec2 pos){
    char new_map [lx][ly];
    int n_loop = 0;
    memcpy(new_map, map, lx * ly * sizeof(char));
    new_map[4][8] = '#';
    run_sequence(new_map, pos);
    display_map(new_map);
/*
    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly; j++){
            if(pos.x == i && pos.y == j) continue;
            memcpy(new_map, map, lx * ly * sizeof(char));
            new_map[i][j] = '#';
            printf("%d %d\n", i,j);
            n_loop = n_loop + run_sequence(new_map,pos);
        }
    }
*/
    printf("Part two result : %d \n", n_loop);
}

void part_one(char map[lx][ly], vec2 pos){

    run_sequence(map, pos);
    display_map(map);

    int n_pos = 0;
    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly; j++){
            if(map[i][j] == 'X') n_pos++;
        }
    }

    printf("Part one result : %d \n", n_pos);
}

int main(){
    FILE * file;
    if((file = fopen("day_6/input.txt", "r")) == NULL) return 1;

    char map[lx][ly] = {' '};

    vec2 guard_pos;

    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly+1; j++){
            char ch = fgetc(file);
            if(ch != '\n') map[i][j] = ch;
            if(map[i][j] == '^'){
                guard_pos.x = i;
                guard_pos.y = j;
            }
        }
    }

    fclose(file);

    //part_one(map, guard_pos);
    part_two(map, guard_pos);

    return 0;
}
