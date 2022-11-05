
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <libc.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

int main(){
    printf("Input CSV file name: ");
    int i;
    scanf("%d[^\n]",&i);
    printf("input was %d \n", i);
    
    char command[20];
    
    strcpy(command, "Rscript data.r");
    system(command);
    
    sleep(2);
    return 0;
}
