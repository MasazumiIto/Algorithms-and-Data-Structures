#include <stdio.h>
#include <string.h>
#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    int i = 0 ;/*注目しているテキストの位置*/
    int j = 0 ;/*注目しているパターンの位置*/
    int z=0;/*インクリメント用*/
    int text_len = strlen(text);/*テキストの長さ*/
    int patn_len = strlen(pattern);/*パターンの長さ*/
    while(i<text_len && j<patn_len) /*テキストの最後尾までたどり着くかパターンを見つけ出すまでループ*/
    {
        if(text[i] == pattern[j]){/*テキストとパターンの一文字を比較して一致したら*/
            printf("%c",pattern[j]);
            i++;/*テキストを一文字進める*/
            j++;/*パターンを一文字進める*/
        }else{/*テキストとパターンが一致しなければ*/
            if(j==0){/*パターンの先頭で一致した場合*/
                i++;/*テキストを１進める*/
                j=0;/*注目しているパターンの位置を先頭に持ってくる*/
                printf("%c",pattern[j]);
            }else{
                i-=(j-1);/*テキストをパターンが移動した分-1だけ手前に移動する*/
                j=0;/*注目しているパターンの位置を先頭に持ってくる*/
            }
            printf(" …failure\n");
            for(z=0;z<i;z++){
                printf(" ");
            }
        }
    }
    if(i==text_len){/*テキスト最後尾までたどり着いてパターンが見つからなかったら*/
        return -1;/*-1を変えす*/
    }else{/*パターンが見つかったら*/
        printf(" …success\n");
        return i-j;/*テキストでのパターンの先頭位置を変えす*/
    }
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
    int j = 0;
    int k = 0;
    int m = 0;
    int patn_len = strlen(pattern);
    /*printf("%d",patn_len);*/
    for ( j = 0; j < patn_len; j++ ) {
        if ( j < 1 ){
            next[j] = 1;
        }else {
            for ( k = 1; k < j; k++ ) {
                for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ ) ;
                if ( m == j ){
                    break;
                }
            }
                next[j] = k;
        }
    }
    for(j=0;j<patn_len;j++){
        printf("%c: next[%d] = %d\n",pattern[j],j,next[j]);
    }
}
    /* 講義資料を参考に実装せよ */

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
    int i = 0;/*注目しているテキストの位置*/
    int j = 0;/*注目しているパターンの位置*/
    int z=0;/*インクリメント用*/
    int text_len = strlen(text);/*テキストの長さ*/
    int patn_len = strlen(pattern);/*パターンの長さ*/
    while (i<text_len && j <patn_len ){
        if(text[i] == pattern[j]){
            printf("%c",pattern[j]);
            i++;
            j++;
        }else{
            j-=next[j];
            if(j<0){
                i++;
                j++;
                printf("%c",pattern[j]);
            }
            printf(" …failure\n");
            for(z=0;z<i;z++){
            printf(" ");
            }
        }
    }
    if(i==text_len){
        return -1;
    }else{
        printf(" …success\n");
        return i-j;
    }
}
    /* 講義資料を参考に実装せよ */


int main(void)
{
    char text[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
    int i;
    int position;
#if BF
    printf("--- B F ---\n");
    strcpy(text,"xxxtartartayx");
    strcpy(pattern,"tartay");
    printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
    printf("見つけたパターン:");
    for(i=position; i<position+strlen(pattern);i++){
        printf("%c",text[i]);
    }
    printf("\n\n");
    strcpy(text,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
    strcpy(pattern,"pyokopyokomu");
        printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
    printf("見つけたパターン:");
    for(i=position; i<position+strlen(pattern);i++){
        printf("%c",text[i]);
    }
    printf("\n\n");

#endif

#if KMP
    printf("--- KMP ---\n");
    strcpy(text,"xxxtartartayx");
    strcpy(pattern,"tartay");
    init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
    printf("見つけたパターン:");
    for(i=position; i<position+strlen(pattern);i++){
        printf("%c",text[i]);
    }
    printf("\n\n");
    strcpy(text,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
    strcpy(pattern,"pyokopyokomu");
        init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
    printf("見つけたパターン:");
    for(i=position; i<position+strlen(pattern);i++){
        printf("%c",text[i]);
    }
    printf("\n\n");
#endif
    return 0;
}


/*実行結果*/

/*--- B F ---
xxxtartartayx
t …failure
 t …failure
  t …failure
   tarta …failure
    t …failure
     t …failure
      tartay …success
position=6
見つけたパターン:tartay

pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
pyokopyokom …failure
 p …failure
  p …failure
   p …failure
    p …failure
     pyoko …failure
      p …failure
       p …failure
        p …failure
         p …failure
          p …failure
           p …failure
            pyokopyokom …failure
             p …failure
              p …failure
               p …failure
                p …failure
                 pyoko …failure
                  p …failure
                   p …failure
                    p …failure
                     p …failure
                      p …failure
                       p …failure
                        pyokopyoko …failure
                         p …failure
                          p …failure
                           p …failure
                            p …failure
                             pyokopyoko …failure
                              p …failure
                               p …failure
                                p …failure
                                 p …failure
                                  pyokopyokomu …success
position=34
見つけたパターン:pyokopyokomu

--- KMP ---
t: next[0] = 1
a: next[1] = 1
r: next[2] = 2
t: next[3] = 3
a: next[4] = 3
y: next[5] = 3
xxxtartartayx
t …failure
 t …failure
  t …failure
   tarta …failure
        rtay …success
position=6
見つけたパターン:tartay

p: next[0] = 1
y: next[1] = 1
o: next[2] = 2
k: next[3] = 3
o: next[4] = 4
p: next[5] = 5
y: next[6] = 5
o: next[7] = 5
k: next[8] = 5
o: next[9] = 5
m: next[10] = 5
u: next[11] = 11
pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko
pyokopyokom …failure
           p …failure
            pyokopyokom …failure
                       p …failure
                        pyokopyoko …failure
                                  pyoko …failure
                                       pyokomu …success
position=34
見つけたパターン:pyokopyokomu*/