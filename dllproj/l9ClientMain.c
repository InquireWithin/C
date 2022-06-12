#include<Windows.h>
#include<stdio.h>

int main() {
    pathtocmdargs = ""	
	printf("add function runs...\n");
	int addReturn = add(10, 20);
	printf("Returned = % d\n", addReturn);

	printf("\nmultiply function runs...\n");
	int multiplyReturn = multiply(10, 20);
	printf("Returned %d\n", multiplyReturn);

	printf("\ngetProc function runs...\n");
	createProc((char*)pathtocmdargs, (char*)"one two three");

	printf("\ngetProc function runs again...\n");
	createProc(NULL, (char*)"ping www.nmap.org");

	printf("\ncopy function runs...\n");
	char name[50];
	printf("Enter your name: ");
	scanf_s("%s", name, 50);
	copy(name);

	return 0;
}

