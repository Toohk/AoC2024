#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vec2{
    int y,x;
} vec2;

typedef struct Antenna{
    char frequency;
    vec2 positions[20];
    int counter_pos;
    int antinodes;
} Antenna;

void part_one(char map[50][51], Antenna * antennas){
    for(int i=0; i<50; i++){
        for(int j=0; j<51; j++){
            if(map[i][j] == '.') continue;
            
            //printf("%c", map[i][j]);
        }
    }
    //antennas = malloc(sizeof(Antenna));
}

int main(){
    FILE * file;
    if((file = fopen("day_8/input.txt", "r")) == NULL) return 1;

    char map[50][51];

    char frequencies[200]= {' '};
    int i_freq = 0;
    
    for(int i=0; i < 50; i++){
        for(int j=0; j<51; j++){
            map[i][j] = fgetc(file);
            if (map[i][j] != '.' && map[i][j] !='\n' && strchr(frequencies, map[i][j])== NULL) {
                frequencies[i_freq] = map[i][j];
                i_freq++;
            }
        }
    }

    fclose(file);
    
    Antenna * antennas;

    part_one(map, antennas);
    printf("%s\n", frequencies);
    
    return 0;
}
