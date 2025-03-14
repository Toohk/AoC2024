#include <stdio.h>

int main(){
    FILE * file;
    if((file = fopen("day_7/input.txt", "r")) == NULL) return 1;
    
    char buff[100];

    while (fgets(buff, 100, file) != NULL) {
        printf("%s", buff); 
    }

    return 0;
}
