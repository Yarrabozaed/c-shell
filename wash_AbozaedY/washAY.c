x/*
 Author: Yarra Abozaed
 Class: CSC 3350
 Last Edit: June 5th, 2022
 Assignment: EC wash
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <libc.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "new_headAY.c"
/**
 This function prints out the man information for the command the user inputted
 */
void manCommand(char argv[]){
    if(strcmp(argv,"pwd") == 0){
        printf(" - pwd: prints current working directory \n");
    }
    else if(strcmp(argv,"setpath") == 0){
        printf(" - setpath<dir>[dir]: changes current path. Provide directory. \n");
    }
    else if(strcmp(argv,"cd") == 0){
        printf(" - cd[dir]: changes current directory. If no specific directory is given, sets directory as home. Provide full path. \n");
    }
    else if(strcmp(argv,"date") == 0){
        printf(" - date: prints today's day, date, time, and year \n ");
    }
    else if(strcmp(argv,"cat") == 0){
        printf(" - cat [file name]: displays contents of a file. Provide file name \n");
    }
    else if(strcmp(argv,"man") == 0){
        printf(" - man: prints the README if no specific command manual is requested, can also be done by typing \"man wash.\" If a specific command is requested, the command's man is given. \n");
    }
    else if(strcmp(argv,"help") == 0){
        printf(" - help: manual descriptions for wash \n");
    }
    else if(strcmp(argv,"exit") == 0){
        printf(" - exit: exists shell \n");
    }
    else{
        printf(" I don't know this one! (...yet) \n");
    }
}

/**
 This function prints out the list of commands the shell can handle.
 */
void printHelpmsg(){
    printf(" - pwd: prints current working directory \n");
    printf(" - setpath<dir>[dir]: changes current path. Provide directory. \n");
    printf(" - cd[dir]: changes current directory. If no specific directory is given, sets directory as home. Provide full path. \n");
    printf(" - date: prints today's day, date, time, and year \n ");
    printf(" - cat [file name]: displays contents of a file. Provide file name \n");
    printf(" - man: prints the README if no specific command manual is requested, can also be done by typing \"man wash.\" If a specific command is requested, the command's man is given. \n");
    printf(" - help: manual descriptions for wash \n");
    printf(" - exit: exists shell \n");
}

/**
 This function opens a file and prints all of its contents for the user.
 */
void openFile(char argv[]){
    FILE* txtptr;
    //open file argv for read
    txtptr = fopen(argv, "r");
    if(txtptr == NULL){
        perror("Unable to open file");
    }
    else{
        char c;
        c = fgetc(txtptr);

        //while file end has not been reached, print char c
        while(!feof(txtptr)){
            printf("%c", c);
            c = fgetc(txtptr);
        }
    }
    //close file
    fclose(txtptr);
}

void buildDep(){
    system("gcc dataProcessing.c -o dataProcessing");
}

/**
 Main function, reads user inputs until user inputs "exit"
 */
int main(int argc, char * argv[]){
    
    buildDep();
    
    char cp[PATH_MAX];
    strcpy(cp, "/bin");
    
    //clear current command line screen
    printf("\e[1;1H\e[2J");

    printf("wash");
    printf("\n");
    
    char sh[3];
    strcpy(sh, "-h");
    
    //check if -h flag is used
    if(argc > 1){
        if(strcmp(argv[1], sh) == 0){
            printf("welcome to wash; \n");
            printHelpmsg();
        }
    }
    
    char cwd[PATH_MAX];
    
    while(1){
        printf(" >");
        printf(" %s ", cp);
        
        //read input from user (not including enter)
        char userInput[150];
        scanf(" %150[^\n]", userInput);
        
        if(strcmp(userInput, "exit") == 0){     //exit
            printf("Goodbye! \n");
            return 0;
        }
        else if(strcmp(userInput, "pwd") == 0){     //pwd
            //use get cwd
            if(getcwd(cwd, sizeof(cwd)) != NULL){
                printf("%s \n",cwd);
            }
            else{
                printf("failed to print cwd \n");
            }
        }
        else if(strcmp(userInput, "setpath") == 0){ //setpath
            printf("TODO");
        }
        else if(userInput[0] == 'c' && userInput[1] == 'd'){    //cd
            //no directory path given -> getnev home dir
            if(strlen(userInput) == 2){
                if(chdir(getenv("HOME")) != 0){
                    perror("cd to home directory failed");
                }
                else{
                    if(getcwd(cwd, sizeof(cwd)) != NULL){
                        printf("%s \n",cwd);
                    }
                    else{
                        perror("failed to print cwd \n");
                    }
                }
            }
            else{
                char tmp [PATH_MAX];
                strncpy(tmp, userInput+3, strlen(userInput) - 2);
                
                char reqDir [PATH_MAX];

                reqDir[0] = '/';
                strcat(reqDir, tmp);

                if(chdir(reqDir) != 0){
                    printf("cd to %s failed \n", reqDir);
                }
                memset(tmp,0,strlen(tmp));
                memset(reqDir,0,strlen(reqDir));
            }
        }
        else if(strcmp(userInput, "help") == 0){    //help
            printHelpmsg();
        }
        else if(strcmp(userInput, "date") == 0){    //date
            //use <time.h> to get current time & day
            time_t curT;
            time(&curT);
            printf("%s",ctime(&curT));
        }
        else if(userInput[0] == 'm' && userInput[1] == 'a' && userInput[2] == 'n'){   //man OR man wash
            //if man wash is called, print the entire README by calling openFile with README.
            if(strcmp(userInput, "man wash") == 0 || strcmp(userInput, "man") == 0){
                openFile("READMEAY.txt");
            }
            else{
                //otherwise, man will use the function manCommand and will print the information on the requested command
                char commandName [PATH_MAX];
                strncpy(commandName, userInput+4, strlen(userInput) - 3);
                manCommand(commandName);
                memset(commandName,0,strlen(commandName));
            }
        }
        else if(userInput[0] == 'c' && userInput[1] == 'a' && userInput[2] == 't'){     //cat
            char fileName [PATH_MAX];
            strncpy(fileName, userInput+4, strlen(userInput) - 3);

            //call openFile function with the name of the file given by user
            openFile(fileName);
            
            memset(fileName,0,strlen(fileName));
        }
        else if(userInput[0] == '.' && userInput[1] == '/'){     //execute file
            char fileToExe [PATH_MAX];
            strncpy(fileToExe, userInput+3, strlen(userInput) - 2);

            //call openFile function with the name of the file given by user
            newHead(1,fileToExe);
            
            memset(fileToExe,0,strlen(fileToExe));
        }
        else if(strcmp(userInput, "timer") == 0){
            int hours;
            int minutes;
            int seconds;
            
            printf("Input hours: \n");
            scanf("%d[^\n]", &hours);
            printf("Input minutes: \n");
            scanf("%d[^\n]", &minutes);
            printf("Input seconds: \n");
            scanf("%d[^\n]", &seconds);
            
            if(minutes < 60 && seconds < 60){
                while(hours+minutes+seconds > 0){
                    printf("\e[1;1H\e[2J");
                    sleep(1);
                    printf("%d : %d : %d \n", hours, minutes,seconds);
                    fflush(stdout);
                    
                    if(seconds > 0){
                        seconds -= 1;
                    }
                    else if(seconds == 0 && minutes > 0){
                        seconds = 60;
                        minutes -= 1;
                        if(minutes == 0 && hours > 0){
                            minutes = 60;
                            hours -=1;
                        }
                    }
                }
                printf("0 : 0 : 0 \n");
                printf("\e[1;1H\e[2J");
                printf("done! \n");
            }
            else{
                printf("Invalid input! Please try again. \n");
            }
        }
        else if(strcmp(userInput, "data") == 0){
            pid_t p;
            p = fork();
            if(p == 0){
                printf("\e[1;1H\e[2J");
                printf("Starting data processing... \n");
                execv("./dataProcessing", (char * const*)NULL);
            }
            else{
                printf("\n");
                int s =0;
                p = wait(&s);
                printf("End of %d \n", p);
            }
        }
        else{
            //if inputted command not defined
            perror("Command not found \n");
        }
    }
    
    return 0;
}
