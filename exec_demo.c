#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
//code
char* argv[] = {"ls","-al",NULL};

int result = execvp("ls",*argv);//replace the current process by a new process (ls)
if(result<0){printf("exec failed\n");exit(1);}
printf("original process is terminated\n");//this will never be reached, as execvp never returns to its caller, and only will if exec fails.

}