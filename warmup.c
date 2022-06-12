#include<stdio.h> 
#include<string.h> 
 
int main(){
//in the prompt enter "lengthnHi" to have str1 print out as "Hi"
        char str1[] = "Hello"; 
        char str2[] = "World!"; 
        printf("Enter a string: "); 
        scanf("%s", str2); 
        printf("str1 = %s at %p\n", str1, str1); 
        printf("str2 = %s at %p\n", str2, str2); 
        //longest string possible was a length of 21:
        //"aaaaaaaaaaaaaaaaaaaaa"
        //21 a's
} 