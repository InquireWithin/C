#include<stdlib.h>
#include<intrin.h>
#include<stdio.h>
#include<Windows.h>
typedef int(*function_t)(int, int);
typedef void(*num_t)(char*);
typedef void(*num_c)(char*, char*);
int main() 
{
    pathtoexec = "" //put path to exec here
    dirpath = "" //path to package dir here
	LPCWSTR str = L"",dirpath;
	HINSTANCE handle =
		LoadLibraryW(str);
	if (handle == NULL) {
		printf("LoadLibrary failed with %d\n",
			GetLastError());
		return 1;
	}
	function_t f1, f2;
	num_t n1;
	num_c n2, n3;
	printf("add function runs...\n");
	f1 = (function_t)GetProcAddress(handle, "add");
	int result1 = f1(10, 20);
	printf("\nmultiply function runs...\n");
	f2 = (function_t)GetProcAddress(handle, "multiply");
	int result2 = f2(10, 20);
	printf("result = %d\n", result1);
	printf("result = %d\n", result2);
	char buf[50];
	scanf_s("%s", buf, 49);
	//char* e =  string_copy(result1, result2);
	printf("\ncopy function runs...\n");
	n1 = (num_t)GetProcAddress(handle, "copy");
	char copied_string[50];
	n1(buf);
	printf("\ncreateProc function runs...\n");
	n2 = (num_c)GetProcAddress(handle, "createProc");
	n2((char*)pathtoexec, (char*)"one two three");
	printf("\ncreateProc runs again...\n");
	n3 = (num_c)GetProcAddress(handle, "createProc");
	n3(NULL, (char*)"ping www.nmap.org");
	FreeLibrary(handle);
}

