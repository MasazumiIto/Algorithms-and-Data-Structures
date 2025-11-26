#include<stdio.h>

#define	MAXSIZE	13
#define	TRUE	1
#define	FALSE	0
#define IMAX	100000	/* INT_MAXだと桁あふれにより正しい計算が出来ない */

int	Adjacent[MAXSIZE][MAXSIZE] = {	/* 隣接行列 */
	{   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  0: 東京
	{  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  1: 埼玉
	{IMAX,  90,   0,IMAX,IMAX, 110, 330, 240,IMAX,IMAX,IMAX,IMAX,IMAX},     //  2: 群馬
	{  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  3: 千葉
	{IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  4: 茨城
	{IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  5: 栃木
	{IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     //  6: 福島
	{IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     //  7: 新潟
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     //  8: 山形
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     //  9: 宮城
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // 10: 秋田
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // 11: 岩手
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // 12: 青森
} ;

char *GraphData[] = {	/* 都県名．上記隣接行列の0-12番目の各要素に対応 */
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

int	Cost[MAXSIZE][MAXSIZE] ;		/* 頂点間の最小コスト */
int PreVertex[MAXSIZE][MAXSIZE] ;	/* 最短経路 */

/*
 *	GraphData[]を表示する
 */
void PrintGraphData( void )
{
	int		i ;

	for( i = 0 ; i < MAXSIZE ; i++ ) {
		printf( "%2d : %s\n", i, GraphData[i] ) ;
	}
}


/*
 *	Cost[][]とPreVertex[][]を初期化する
 */
void Initialize( void )
{
    int i, j;
    for(i=0; i < MAXSIZE; i++ ){
        for( j =0; j < MAXSIZE; j++ ){
            PreVertex[i][j] = i;
            Cost[i][j]=Adjacent[i][j];
            
        }
    }
	/*《実装①》*/
	/* Cost[][]とPreVertex[][]の初期化を行う関数を作成せよ */
	/* 補足資料及び実行結果の例を参考にすること */
}


/*
 *	Cost[][]とPreVertex[][]の表示
 */
void PrintCostPreVertex( int n )
{
    int i, j;
    printf("==== n=%d ====\n",n);
    printf("Cost[][]                                                               PreVertex[][]\n");
    for(i=0;i<MAXSIZE;i++){
        for(j=0;j<MAXSIZE;j++){
            if(Cost[i][j]==IMAX){
                printf("   ∞,");
            }else{
            printf("%4d,",Cost[i][j]);
            }
        }
        printf("    ");
        for(j=0;j<MAXSIZE;j++){
            printf("%3d,",PreVertex[i][j]);
        }
        printf("\n");
    }
	/*《実装②》*/
	/* Cost[][]とPreVertex[][]を実行例のように表示するよう本関数を作成せよ */
}


/*
 *	すべての頂点間の最短経路をフロイド法で探索する
 */
void Search( void )
{
    int i,j,k;
    for(k=0;k<MAXSIZE;k++){
        PrintCostPreVertex(k);
        for(i=0;i<MAXSIZE;i++){
            for(j=0;j<MAXSIZE;j++){
                if(Cost[i][j]>Cost[i][k]+Cost[k][j]){
                    Cost[i][j]=Cost[i][k]+Cost[k][j];
                    PreVertex[i][j]=PreVertex[k][j];
                }
            }
        }
    }
	/*《実装③》*/
	/* フロイドのアルゴリズムを実装せよ */
	/* 最終的にCost[][]に各2点間の最小コストが入るようにすること */
	/* iからjへの最短経路においてjの1つ手前のノードがPreVertex[i][j]に入るようにすること */
	/* 実行例も参考にすること */
}


/*
 *	経路を表示
 */
void PrintPath( int start, int goal )
{
    int x = goal;
    int t[MAXSIZE];
    int i=0;
    t[i]=x;
    do{
        x = PreVertex[start][x];
        i++;
        t[i]=x;
    }while(x !=  start);
    printf("%s",GraphData[t[i]]);
    while(i>0){
        i--;
        printf("->%s",GraphData[t[i]]);
    }
	/*《実装④》*/
	/* 最短経路を実行例のように表示するよう関数を作成せよ */
	/* 経路が逆順にならないように注意すること */
}


int main( void )
{
	int		start, goal ;

	/* 初期化 */
    Initialize();

	/* フロイド法による探索 */
    Search();

	/* 都県名と番号の表示 */
    PrintGraphData();

	/* 出発地と目的地の入力 */
	printf( "出発地を0～12の番号で入力してください：" ) ;
	scanf( "%d", &start ) ;
	printf( "目的地を0～12の番号で入力してください：" ) ;
	scanf( "%d", &goal ) ;

	/* 表示の一例 */
    int i;
  

    PrintPath(start,goal);
	printf( "\n" ) ;
	printf( "コストは %d です．\n", Cost[start][goal] ) ;

	return 0 ;
}

