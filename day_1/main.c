#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void part_one(int col1[1000], int col2[1000]){
    qsort(col1, 1000, sizeof(int), compare);
    qsort(col2, 1000, sizeof(int), compare);

    int result = 0;

    for(int i = 0; i < 1000; i++){
        result = result + abs(col1[i] - col2[i]);
    }

    printf("%d\n", result);
}

void part_two(int col1[1000], int col2[1000]){
    int result = 0;

    for(int i = 0; i < 1000; i++){
        int counter = 0;

        for(int j = 0; j < 1000; j++){
            if (col1[i] == col2[j]) {
                counter++; 
            }
        }

        result = result+ (col1[i] * counter);
    }

    printf("%d\n", result);
}

int main(){
    FILE *file;
    if ((file = fopen("input.txt", "r")) == NULL) {
     exit(1);
    }
     
    char buff[15];
    int col1[1000];
    int col2[1000];

    int j = 0;
    while(fgets(buff, 15, file) != NULL){
        sscanf(buff, "%d %d", &col1[j], &col2[j]);
        j++;    
    } 

    //part_one(col1, col2);
    part_two(col1, col2);


    fclose(file);
    return 0;
}
