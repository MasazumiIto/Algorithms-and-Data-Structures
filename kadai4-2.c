//3J04　伊藤雅純 Ad4-2
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 32 

int aaa(char *str) {
    int num = 0;
    while(*str != '\0'){
        num += *str - 48;
        num *= 10;
        str++;
    }
    
    num /= 10;
    
    return num;
}
 

int get_num2(int *a, int *b) 

{ 
    int i=0,t=0,k=0,count=2;

    char buf[BUF_SIZE+1]; 

    fgets(buf, BUF_SIZE, stdin); 

    /* この続きを実装せよ */ 
    char ac[32]={},bc[32]={};
    while(buf[i]!=','){
        ac[i]=buf[i];
        i++;
    }
    i++;
    while(buf[i]!='\0'){
        bc[t]=buf[i];
        i++;
        t++;
    }
    while(k!=i-t-1){
        if(ac[k]<=48 || ac[k]>=57){
            count = 0;
            break;
        }
    k++;
    }
    k=0;
    while(k!=t){
        if(bc[k]<=48 || bc[k]>=57){
            count--;
            break;
        }
    k++;
    }
    *a = aaa(ac) ;
    *b = aaa(bc) ;
    if(count==0){
        printf("a = ×××××, b = %d, r = 1\n",*b); 
        exit(0);
    }else if(count==1){
        printf("a = %d, b = ×××××, r = 1\n",*a); 
        exit(0);
    }else if(count== -1){
        printf("a =××××× , b = ×××××, r = 0\n"); 
        exit(0);
    }

    return count;
} 

 

int main(void) 

{ 

    int a, b, r; 

 

    printf(">"); 

    r = get_num2(&a,&b); 

 

    printf("a = %d, b = %d, r = %d\n",a,b,r); 

 

    return 0; 

} 
/*
>a = 123, b = 456, r = 2    (123,456)

>a = ×××××, b = 456, r = 1  (1a3,456)

>a = 123, b = ×××××, r = 1   (123,4b6)

>a =××××× , b = ×××××, r = 0 (aa3,4b6)
*/
 