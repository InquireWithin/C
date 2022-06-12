#include<stdio.h>
#include<Windows.h>
#include"header.h"

//typename int _child_pid;
int main(int argc, char* argv[]){
int child_pid = GetCurrentProcessId();
	
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	if (*(*argv + 0) == 'p') {
		system("ping www.nmap.org");
	}
	else {
		printf("not ping\n");
	}
	//printf("Child process: %d\n", _child_pid);
	system("pause");
	printf("child process: %d\n", child_pid);
	return 0;
}
