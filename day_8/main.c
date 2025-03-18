#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec2{
    int y,x;
} vec2;

typedef struct Antenna{
    char frequency;
    int n_pos;
    int antinodes;
    vec2 positions[10];
} Antenna;

void part_one(char map[50][51], Antenna * antennas, int n_freq){
    for(int i=0; i<50; i++){
        for(int j=0; j<51; j++){
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
            printf("[%d,%d]", antennas[i].positions[j].y, antennas[i].positions[j].x);
            for(int k = 0; k < 4; k++){

            }
        }
        printf("\n");
    }

}

int main(){
    FILE * file;
    if((file = fopen("day_8/input.txt", "r")) == NULL) return 1;

    char map[50][51];

    char frequencies[200]= {' '};
    int n_freq = 0;

    for(int i=0; i < 50; i++){
        for(int j=0; j<51; j++){
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
