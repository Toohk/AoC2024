#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool isCorrect( int n[8]){
        bool safe = true; 
        for (int i = 0; i<7; i++) {
            if (n[i+1] == - 1) break;
            safe=(n[i] <= n[i+1]|| abs(n[i] - n[i+1]) > 3)? false : true; 
            if(!safe) break;
        }

        if(safe){return true;}
        for (int i = 0; i<7; i++) {
            if (n[i+1] == - 1) break;
            safe=(n[i] >= n[i+1] ||abs(n[i] - n[i+1]) > 3)? false : true; 
            if(!safe) break;
        }
        return safe;
}

void part_one(FILE * file){
    int n[8];
    int valid = 0;
    
    char buff[30];
    while(fgets(buff, 30, file) != NULL){
        memset(n, -1, sizeof(n));
        sscanf(buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
        if(isCorrect(n)) valid++;
    }
    printf("SAFE REPORTS : %d\n",  valid);
}


void part_two(FILE * file){
    int n[8];
    int new[8];
    int valid = 0;
    
    char buff[30];
    while(fgets(buff, 30, file) != NULL){
        memset(n, -1, sizeof(n));
        sscanf(buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);
        int badLevel = 0;
        if (!isCorrect(n)) {
        
            for(int i= 0; i<8; i++){
                memset(new, -1, sizeof(new));
                for(int j= 0; j <7; j++){
                    if (j < i) {
                        new[j] = n[j];    
                    }else{
                        new[j] = n[j+1];    
                    }
                }
                if (!isCorrect(new)) badLevel++;
            }
            if(badLevel < 8) valid++;

        }else{
            valid++;
        }
    }
    printf("SAFE REPORTS : %d\n",  valid);
}

int main(){
    FILE * file;
    if((file = fopen("input.txt", "r"))== NULL){
        exit(1);
    }

    //part_one(file);
    part_two(file);
       return 0;
}
