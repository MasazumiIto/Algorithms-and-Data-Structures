// Ad4-1 3J04 伊藤雅純　
#include <stdio.h>
#define BUF_SIZE 32

int checksp(int c)
{
    if(c==' '||c=='\t'||c=='\n'){
        return 1;
    }
    return 0;
        /* 実装せよ */
}

void compress(char *s)
{
    char *p=s;
    int i=0;
    /* 行頭の空白を消去 */
    
    while( *s !='\0' ){
        if(checksp(*p)==1){
            p++;
        }else{
            *s=*p;
            s++;
            p++;
        }/* 実装せよ */
    }
    /* 新しい文字列を作成していく */
    *s = '\0';
}


int main(void)
{
    char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";

    printf("Before = \"%s\"\n",s);
    compress(s);

    printf("After  = \"%s\"\n",s);

    return 0;
}

/*
Before = "     Nice to 
 meet 	 you    ,  Jack !
     I'm      Mike 
		 .    "
After  = "Nicetomeetyou,Jack!I'mMike."
*/

