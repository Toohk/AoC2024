#include <stdio.h>
#include <string.h>

void part_one(char data[142][142]){
    int count = 0;
    
    for (int i =0; i < 142; i++) {
        for (int j = 0; j<142; j++) {
            if(data[i][j] != 'X') continue;
            if(data[i][j+1] == 'M' && data[i][j+2] == 'A' && data[i][j+3] == 'S') count++; 
            if(data[i][j-1] == 'M' && data[i][j-2] == 'A' && data[i][j-3] == 'S') count++; 
            if(data[i+1][j] == 'M' && data[i+2][j] == 'A' && data[i+3][j] == 'S') count++; 
            if(data[i-1][j] == 'M' && data[i-2][j] == 'A' && data[i-3][j] == 'S') count++; 
            
            if(data[i+1][j+1] == 'M' && data[i+2][j+2] == 'A' && data[i+3][j+3] == 'S') count++; 
            if(data[i+1][j-1] == 'M' && data[i+2][j-2] == 'A' && data[i+3][j-3] == 'S') count++; 
            if(data[i-1][j+1] == 'M' && data[i-2][j+2] == 'A' && data[i-3][j+3] == 'S') count++; 
            if(data[i-1][j-1] == 'M' && data[i-2][j-2] == 'A' && data[i-3][j-3] == 'S') count++; 
        }
    
    }
    printf("Part one result : %d\n", count);
}

void part_two(char data[142][142]){
    int count = 0;
    
    for (int i =0; i < 142; i++) {
        for (int j = 0; j<142; j++) {
            if(data[i][j] != 'A') continue;
            if(data[i-1][j-1] == 'M' && data[i+1][j+1] == 'S' && data[i+1][j-1] == 'M' && data[i-1][j+1] == 'S') count++; 
            if(data[i-1][j+1] == 'M' && data[i+1][j-1] == 'S' && data[i+1][j+1] == 'M' && data[i-1][j-1] == 'S') count++; 
            if(data[i+1][j-1] == 'M' && data[i-1][j+1] == 'S' && data[i+1][j+1] == 'M' && data[i-1][j-1] == 'S') count++; 
            if(data[i-1][j-1] == 'M' && data[i+1][j+1] == 'S' && data[i-1][j+1] == 'M' && data[i+1][j-1] == 'S') count++; 
        }
    
    }
    printf("Part two result : %d\n", count);
}

int main(){
    FILE * file;
    if ((file = fopen("input.txt", "r")) == NULL) {
        return 1;
    }
    
    char data[142][142];
    
    for (int i = 0; i<142; i++) {
        fgets(data[i], 142, file); 
    }

    fclose(file);

    //part_one(data);
    part_two(data);

    return 0;
}
