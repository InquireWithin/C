#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int main(){
	const int CHILDREN = 10;
	int child_pids[CHILDREN];
	for(int i =0;i<10;i++){
	
	
	pid_t pid = fork(); //creates child process
	
	//"after fork" will print twice due to child process, and they cant be distinguished (at the moment)
	//these two processes will run simultaneously and will compete like threads
	//fork returns an important value "pid_t" (process id type)
	if(pid<0){
	printf("process failed on creation\n");
	exit(1);
	}
	else if(pid ==0){
	printf("child %d created\n",i);
	//child process code
	//parent process is terminated before child process executes
	//therefore, the parent process might wait for child process to finish
	printf("this is a child process wirh pid num %d\n",getpid());
	printf("parent process of child %d with parent id %d\n",getpid(),getppid());
	sleep(rand()%5);
	printf("child %d terminated\n",i);
	exit(0);
	}
	
	//executed by parent process
	
	//parent process runs first, but has a chance of waiting for child process to finish
	for(int i =0;i<CHILDREN;i++){
	waitpid(child_pids[i],NULL,0);
	}
	}
	printf("this is a parent process wirh pid num %d\n",getpid());
	wait(NULL);
	}
