#include<stdio.h>
#include<Windows.h>

int main(int argc, char* argv[]) {
	printf("process id: %d\n", GetCurrentProcessId());
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	//system("pause");
	return 0;
}
