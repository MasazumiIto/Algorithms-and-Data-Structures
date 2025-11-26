#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define	MAXSIZE	13
#define	TRUE	1
#define	FALSE	0
#define IMAX	INT_MAX
        
/* データ（隣接行列） */
int Adjacent[MAXSIZE][MAXSIZE] = {
	{   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // A: 東京
	{  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // B: 埼玉
	{IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      // C: 群馬
	{  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // D: 千葉
	{IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // E: 茨城
	{IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     // F: 栃木
	{IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     // G: 福島
	{IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     // H: 新潟
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     // I: 山形
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     // J: 宮城
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // K: 秋田
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // L: 岩手
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // M: 青森
} ;

char *GraphData[] = {	/* 上記隣接行列の0～12番目の各要素に対応 */
	"Tokyo",
	"Saitama",
	"Gunma",
	"Chiba",
	"Ibaraki",
	"Tochigi",
	"Fukushima",
	"Niigata",
	"Yamagata",
	"Miyagi",
	"Akita",
	"Iwate",
	"Aomori"
} ;

int	Visited[MAXSIZE];	/* 調べた頂点を記憶 */
int	Cost[MAXSIZE];		/* コスト */
int	Prev[MAXSIZE];		/* 直前の頂点 */


/*
 *	各頂点について，直前の頂点とコストを表示
 */
void PrintCost( void )
{
    int i;
    for(i=0;i<MAXSIZE;i++){
        printf("頂点　%s 直前の頂点　%s コスト %d\n",GraphData[i] ,GraphData[Prev[i]] ,Cost[i] );
    }
	/*《実装①》*/
	/*実行例のように全ての頂点(都県)に対して都県の名前，直前の頂点，頂点までのコストを表示する*/
}


/*
 *	Dijkstra法の実装
 */
void Search( int start )
{
    int i,t,min,next;
    
    Cost[start]=0;
    do{
        min=IMAX;
        next=-1;
        Visited[start]=TRUE;
        
        for(start=0;start<MAXSIZE;start++){
            if(Visited[start]==TRUE){
                for(i=0;i<MAXSIZE;i++){
                    if(Visited[i]==FALSE){
                        if( min > Cost[start]+Adjacent[start][i] && Cost[start] + Adjacent[start][i] > 0  ){
                            min=Adjacent[start][i] + Cost[start];
                            next=i;
                            Prev[i]=start;
                        }
                    }
                }
            }
        }
        Cost[next]=min;
        start=next;
    }while(start!=-1);
	/*《実装②》*/
	/*startから全ての都県までの最短経路及びコストをDijkstra法によって求める*/
	/*各都県までの経路は，それぞれの都県の1つ前の都県をPrev[]に入れることによって求めたことにする*/
	/*各都県までの最小コストはCost[]に代入すること*/
}


/*
 *	メイン関数
 */
int main( void )
{
	int		i, j=0 ;
	int		start ;			/* 出発地点 */
	int		goal ;			/* 到着地点 */
	int		path[MAXSIZE] ;	/* 出発地点から到着地点へのパス */


	/* 初期化 */
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		Visited[i] = FALSE ;
		Cost[i] = IMAX ;
		path[i] = -1 ;
	}

	/* 都県情報の表示 */
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		printf( "%2d: %s\n", i, GraphData[i] ) ;
	}

	/* 出発地点及び到着地点の入力 */
	printf( "出発地点を入力してください：" ) ;
	scanf( "%d", &start ) ;
	printf( "到着地点を入力してください：" ) ;
	scanf( "%d", &goal ) ;

	/* 探索 */
	Search( start );

	/* 表示 */
	PrintCost( ) ;

    path[j]=goal;
    while(path[j]!=start){
        path[j+1]=Prev[path[j]];
        j++;
    }
    
    printf("[%s]",GraphData[path[j]]);
    while (j!=0)
    {
        j--;
        printf("->[%s]",GraphData[path[j]]);
        /* code */
    }
    printf("Cost=%d",Cost[path[j]]);
    
	/*《実装③》最短経路の表示*/
	/*実行例のように出発地点から到着地点までの最短経路とコストを表示する*/

	return 0;
}

