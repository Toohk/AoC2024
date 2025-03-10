#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vec2{
    int x;
    int y;
}vec2;

void display_map(char map[130][130]){
    printf("\n\n\n");
    for(int i = 0; i<130; i++){
        for(int j = 0; j<130; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
} 

int run_sequence(char map[130][130], vec2 pos){
    bool moving = true;
    int loop_score = 0;
    while (moving && loop_score < 1000) {
        if (map[pos.x][pos.y] == '^' && moving) {
            while (map[pos.x - 1][pos.y] != '#') {
                 if(pos.x -1 < 0){
                    moving = false;
                    break;
                }
                if(map[pos.x][pos.y]== 'X') loop_score++;
                if(map[pos.x][pos.y]== '.') loop_score = 0;
                map[pos.x][pos.y] = 'X';     
                pos.x = pos.x -1;
                map[pos.x][pos.y] = '>';     
            }
        }
        if (map[pos.x][pos.y] == '>' && moving) {
            while (map[pos.x][pos.y +1] != '#') {
                if(pos.y +1 > 129){
                    moving = false;
                    break;
                }
                if(map[pos.x][pos.y]== 'X') loop_score++;
                if(map[pos.x][pos.y]== '.') loop_score = 0;
                map[pos.x][pos.y] = 'X';     
                pos.y = pos.y +1;
                map[pos.x][pos.y] = 'v';     
            }
        }
        if (map[pos.x][pos.y] == 'v' && moving) {
            while (map[pos.x+1][pos.y] != '#') {
                if(pos.x +1 > 129){
                    moving = false;
                    break;
                }
                if(map[pos.x][pos.y]== 'X') loop_score++;
                if(map[pos.x][pos.y]== '.') loop_score = 0;
                map[pos.x][pos.y] = 'X';     
                pos.x = pos.x +1;
                map[pos.x][pos.y] = '<';     
            }
        }
        if (map[pos.x][pos.y] == '<' && moving) {
            while (map[pos.x][pos.y -1] != '#') {
                if(pos.y -1 < 0){
                    moving = false;
                    break;
                }
                if(map[pos.x][pos.y]== 'X') loop_score++;
                if(map[pos.x][pos.y]== '.') loop_score = 0;
                map[pos.x][pos.y] = 'X';     
                pos.y = pos.y -1;
                map[pos.x][pos.y] = '^';     
            }
        }
    }
    if(loop_score >= 1000) return 1;
    return 0;
}


void part_two(char map[130][130], vec2 pos){ 
    char new_map [130][130];
    int n_loop = 0;
    int c=0;
    for(int i = 0; i<130; i++){
        for(int j = 0; j<130; j++){
            memcpy(new_map, map, 130 * 130 * sizeof(char));
            map[i][j] = '#';
            c++;
            printf("%d - loop = %d\n", c, n_loop);
            n_loop = n_loop + run_sequence(new_map,pos);
        }
    }

    printf("Part two result : %d \n", n_loop);
}

void part_one(char map[130][130], vec2 pos){
    
    run_sequence(map, pos);
    display_map(map);
     
    int n_pos = 1;
    for(int i = 0; i<130; i++){
        for(int j = 0; j<130; j++){
            if(map[i][j] == 'X') n_pos++;
        }
    }

    printf("Part one result : %d \n", n_pos);
}

int main(){
    FILE * file;
    if((file = fopen("input.txt", "r")) == NULL) return 1;
    
    char map[130][130] = {' '};
    
    vec2 guard_pos;

    for(int i = 0; i<130; i++){
        for(int j = 0; j<131; j++){
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
