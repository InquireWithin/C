#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void display_time(char *command, char *name);

int main(){
    char command[20] = "date";
    char name[50];
    printf("Enter your name: ");
    scanf("%s", name);
    display_time(command, name);
    return 0;
}
//string used "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaals$IFS-al"
void display_time(char *command, char *name){
        char command_buf[20];
        char name_buf[20];
    
        strcpy(command_buf, command);
        strcpy(name_buf, name);

        printf("Hello, %s\n", name_buf);  
        printf("Current time is\n");
        system(command_buf);
}
