#include <_regex.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <regex.h>
#include <stdbool.h>

void part_one(char * data){
    
    regex_t regex;
    regmatch_t *matches = NULL;
    size_t matches_size = 0;
    size_t matches_count = 0;
    int reti;

    reti = regcomp(&regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED);

    if (reti) {
        printf("erreur compilation regex"); 
        regfree(&regex);
        exit(1);
    }

    const char *ptr = data;

    int result=0;

    while(1){
        matches_size++;
        matches = realloc(matches, matches_size * sizeof(regmatch_t));
        assert(matches != NULL);

        reti = regexec(&regex, ptr, 1, &matches[matches_count], 0);
        if(reti == REG_NOMATCH) break;
        
        char p[20];
        int parameters[2] ={0,0};
        memset(p, ' ', 20);
        strncpy(p, ptr + matches[matches_count].rm_so, matches[matches_count].rm_eo - matches[matches_count].rm_so);
        p[(matches[matches_count].rm_eo - matches[matches_count].rm_so) + 1] = '\0';

        sscanf(p, "mul(%d,%d)", &parameters[0], &parameters[1]);
        result = result + parameters[0] * parameters[1];
       
        //printf("%d %d\n", parameters[0], parameters[1]);

        ptr += matches[matches_count].rm_eo;
        matches_count++;
    }

    printf("Matches : %zu\n", matches_count);
    printf("Part one result : %d\n", result);
    
    regfree(&regex);
    free(matches);
}

void part_two(char * data){
    
    regex_t regex;
    regmatch_t match;

    int reti = regcomp(&regex, "do\\(\\)|don't\\(\\)|mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED);

    if (reti) {
        printf("erreur compilation regex"); 
        regfree(&regex);
        exit(1);
    }

    const char *ptr = data;

    bool active = true;

    int result=0;
            
    while(1){
        
        reti = regexec(&regex, ptr, 1, &match, 0);
        if(reti == REG_NOMATCH) break;
        
        char p[20];
        int parameters[2] ={0,0};
        memset(p, ' ', 20);
        strncpy(p, ptr + match.rm_so, match.rm_eo - match.rm_so);
        p[(match.rm_eo - match.rm_so) + 1] = '\0';

        ptr += match.rm_eo;

        if(p[2] == '('){
            active = true;
        }else if(p[2] == 'n'){
            active = false;
        }else{
            if(!active) continue;
            sscanf(p, "mul(%d,%d)", &parameters[0], &parameters[1]);
            result = result + parameters[0] * parameters[1];
        }

    }

    printf("Part two result : %d\n", result);
    
    regfree(&regex);
}

int main(){
    FILE * file;
    if ((file = fopen("input.txt", "r")) == NULL) {
        return 1; 
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *data = malloc(file_size + 1);
    assert(data != NULL);

    fread(data, 1, file_size, file);
    fclose(file);

    data[file_size] = '\0'; 

    //part_one(data);
    part_two(data);

    free(data);
    return 0;
}
