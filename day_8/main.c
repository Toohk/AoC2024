#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ly 11
#define lx 12

typedef struct vec2{
    int y,x;
} vec2;

typedef struct Antenna{
    char frequency;
    int n_pos;
    int antinodes;
    vec2 positions[10];
} Antenna;

void part_one(char map[ly][lx], Antenna * antennas, int n_freq){
    int result = 0;
    for(int i=0; i<ly; i++){
        for(int j=0; j<lx; j++){
            if(map[i][j] == '.' || map[i][j] == '\n') continue;
            for(int k=0; k < n_freq; k++){
                if(antennas[k].frequency == map[i][j]){
                    vec2 pos = {i,j};
                    antennas[k].positions[antennas[k].n_pos] = pos;
                    antennas[k].n_pos++;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < n_freq; i++){
        printf("%c %d ||", antennas[i].frequency, antennas[i].n_pos);
        for(int j=0; j < 4; j++){
            vec2 pos_a =  antennas[i].positions[j];
            if(pos_a.x == 0 && pos_a.y ==0) continue;
            for(int k = 0; k < 4; k++){
                vec2 pos_b =  antennas[i].positions[k];
                if(pos_a.y == pos_b.y && pos_a.x == pos_b.x) continue;
                vec2 pos_diff = {pos_a.y - pos_b.y, pos_a.x - pos_b.x};
                if(pos_a.y + pos_diff.y <0 || pos_a.y + pos_diff.y >ly) continue;
                if(pos_a.x + pos_diff.x <0 || pos_a.x + pos_diff.x >lx) continue;
                antennas[i].antinodes++;
            }
        }
        result = result + antennas[i].antinodes;
        printf("%d\n", antennas[i].antinodes);
    }
    printf("Part one result: %d\n", result);
}

int main(){
    FILE * file;
    if((file = fopen("day_8/debug.txt", "r")) == NULL) return 1;

    char map[ly][lx];

    char frequencies[200]= {' '};
    int n_freq = 0;

    for(int i=0; i < ly; i++){
        for(int j=0; j<lx; j++){
            map[i][j] = fgetc(file);
            if (map[i][j] != '.' && map[i][j] !='\n' && strchr(frequencies, map[i][j])== NULL) {
                frequencies[n_freq] = map[i][j];
                n_freq++;
            }
        }
    }

    fclose(file);

    Antenna * antennas = malloc(sizeof(Antenna)*n_freq);
    if(antennas == NULL) return 1;

    for (int i = 0; i < n_freq; i++) {
       Antenna antenna = {frequencies[i], 0, 0};
       antennas[i] = antenna;
    }

    part_one(map, antennas, n_freq);

    free(antennas);
    return 0;
}
