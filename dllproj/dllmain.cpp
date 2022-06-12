// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include<stdio.h>
#include<Windows.h>
#include<specstrings.h>
extern "C" _declspec(dllexport) 
int add(int x, int y) {
	return x + y;
}
extern "C" _declspec(dllexport)
int multiply(int x, int y) {
	int og = x;
	for (int i = 1; i < y; i++) {
		x = x + og;
	}
	return x;
}
extern "C" _declspec(dllexport)
void copy(char *name) {
	char buff[30];
	strcpy(buff, name);
	printf("From copy dll : buff = %s\n", buff);
}
extern "C" _declspec(dllexport)
void createProc(char *applicationName, char *cmdline) {
	/*
	Creates a child process that will execute the  applicationName module. The 
cmdline is a string containing command line arguments separated by blank 
space that is to be passed into the application. The applicationName 
parameter can be NULL. In that case, the module name must be the first token in 
the cmdline string. 
- The parent process must wait until the child process is terminated and then print 
its own pid and child pid. */
	STARTUPINFOA info;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&info, sizeof(info));
	info.cb = sizeof(info);
	ZeroMemory(&processInfo, sizeof(processInfo));
	if (applicationName == NULL) {
		applicationName = cmdline;
	}
	CreateProcessA(applicationName, cmdline, NULL, FALSE, NORMAL_PRIORITY_CLASS, 0, NULL, NULL, &info,&processInfo);
	DWORD child_pid = GetCurrentProcessId();
	WaitForSingleObject(&processInfo, INFINITE);
	DWORD parent_pid = GetCurrentProcessId();
	printf("parent pid: %d\n", parent_pid);
	printf("child pid: %d\n", child_pid);
	}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

