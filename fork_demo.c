#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(){
	int count = 0;
	pid_t pid = fork(); //creates child process
	//"after fork" will print twice due to child process, and they cant be distinguished (at the moment)
	//these two processes will run simultaneously and will compete like threads
	//fork returns an important value "pid_t" (process id type)
	if(pid<0){
	printf("process failed on creation\n");
	exit(1);
	}
	else if(pid ==0){
	//child process code
	//parent process is terminated before child process executes
	//therefore, the parent process might wait for child process to finish
	printf("this is a child process wirh pid num %d\n",getpid());
	printf("parent process of child %d with parent id %d\n",getpid(),getppid());
	while(count <100){
	count++;}
	printf("child count = %d\n",count);
	exit(0);
	}
	//else{
	//positive process id
	//executed by parent process
	
	//parent process runs first, but has a chance of waiting for child process to finish
	printf("this is a parent process wirh pid num %d\n",getpid());
	printf("my child process is %d\n",pid);
	while(count >0){
	count--;}
	printf("parent count = %\n",count);
	//int status;
	//wait for child process to finish, guaranteed, using the blocking function wait
	//wait(&status);
	//printf("exist status of child %d\n");
	wait(NULL); //parent process may use this to wait for one of its children to terminate.
	
	//}
}