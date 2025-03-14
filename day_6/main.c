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

void clean_map(char map[lx][ly]){
    for(int x = 0; x<lx; x++){
        for(int y = 0; y<ly; y++){
            if(map[x][y]== 'X' || map[x][y] == '+') map[x][y] = '.';
        }
    }
}

int run_sequence(char map[lx][ly], vec2 pos){
    int vecx[]={-1,0,1,0},vecy[]={0,1,0,-1},veci=0;
    bool moving = true;
    int loop_score = 0;
    while (moving && loop_score < 4) {
        loop_score = 0;
        
        while(map[pos.x+vecx[veci]][pos.y+vecy[veci]] == '#')veci=(veci+1) % 4;

        if(pos.x+vecx[veci] <= 0 || pos.x+vecx[veci] >= lx-1 || pos.y+vecy[veci] <= 0 || pos.y+vecy[veci] >= ly-1 ){ 
            moving = false; 
        }
        pos.x+=vecx[veci];
        pos.y+=vecy[veci];

        if(map[pos.x][pos.y] != '+') map[pos.x][pos.y] = 'X';
        if(map[pos.x][pos.y] == '+' && map[pos.x][pos.y+1] != '.') loop_score++;
        map[pos.x][pos.y] = '+';
    }
    if(loop_score >=4) return 1;
    return 0;
}


void part_two(char map[lx][ly], vec2 pos){
    char new_map [lx][ly];
    int n_loop = 0;
    memcpy(new_map, map, lx * ly * sizeof(char));
    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly; j++){
            if(map[i][j] != 'X' && map[i][j] != '+') continue;
            memcpy(new_map, map, lx * ly * sizeof(char));
            clean_map(new_map); 
            new_map[i][j] = '#';
            n_loop = n_loop + run_sequence(new_map,pos);
        }
    }
    printf("Part two result : %d \n", n_loop);
}

void part_one(char map[lx][ly], vec2 pos){
    run_sequence(map, pos);
    int n_pos = 0;
    for(int i = 0; i<lx; i++){
        for(int j = 0; j<ly; j++){
            if(map[i][j] == 'X' || map[i][j] == '+') n_pos++;
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

    part_one(map, guard_pos);
    part_two(map, guard_pos);

    return 0;
}
