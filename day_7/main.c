#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long concat_long(long a, long b){
    char str_a[16], str_b[16];
    sprintf(str_a, "%ld", a);
    sprintf(str_b, "%ld", b);

    char str_c[32];
    sprintf(str_c, "%s%s", str_a, str_b);
    return atol(str_c);
}

long part_two(long equation[20]){
    int base3[11]= {0};

    for (int i = 0; i < 177147; i++) {
        long result = equation[1];

        int index = 11 -1; 
        
        while (index >= 0) {
            base3[index]++;
            if (base3[index] == 3) {
                base3[index] = 0;
                index--;  
            } else {
                break;
            }
        }

        for (int j = 0; equation[j+2] != 0; j++) {
            if (base3[j] == 0) result = result + equation[j+2]; 
            if (base3[j] == 1) result = result * equation[j+2]; 
            if (base3[j] == 2) result = concat_long(result,equation[j+2]); 
        }

        if (result == equation[0]) {return result;}
    }
    return 0;
}

long part_one(long equation[20]){
    for (int i = 0; i < 2048; i++) {
        long result = equation[1];
        for (int j = 0; equation[j+2] != 0; j++) {
            if ((i>>j) & 1) {
                result = result + equation[j+2]; 
            }else {
                result = result * equation[j+2]; 
            }
        }
        if (result == equation[0]) {return result;}
    }
    return 0;
}

int main(){
    FILE * file;
    if((file = fopen("day_7/input.txt", "r")) == NULL) return 1;
    
    char buff[100];
    long part_one_result;
    long part_two_result;

    while (fgets(buff, 100, file) != NULL) {
        long equation[20]= {-1};

        char * token;
        token = strtok(buff, " ");

        int n_num = 0;
        while (token != NULL) {
            long num = atol(token);
            equation[n_num] = num;
            n_num++;
            token = strtok(NULL, " ");
        }
        part_one_result = part_one_result + part_one(equation);
        part_two_result = part_two_result + part_two(equation);
    }
    printf("Part one result : %ld\n", part_one_result);
    printf("Part two result : %ld\n", part_two_result);

    return 0;
}
