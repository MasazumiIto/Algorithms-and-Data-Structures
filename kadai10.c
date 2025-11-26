#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	TRUE	1
#define	FALSE	0
#define	MAXSIZE	11

typedef struct _Cell {
	int				no ;	/* 0～10, A-Kに対応 */
	char			name ;	/* 'A'～'K' */
	struct _Cell	*next ;	/* 次のセルへのポインタ */
} Cell ;

char *GraphData[] = {
	"CI",		/* A : C I */
	"DGH",		/* B : D G H */
	"ADG",		/* C : A D G */
	"BCHIJ",	/* D : B C H I J */
	"FHJ",		/* E : F H J */
	"EGK",		/* F : E G K */
	"BCF",		/* G : G C F */
	"BDEJ",		/* H : B D E J */
	"AD",		/* I : A D */
	"DEHK",		/* J : D E H K */
	"FJ"		/* K : F J */
} ;

Cell	*adjacent[MAXSIZE] ;	/* 隣接リスト */
int		visited[MAXSIZE] ;		/* 訪問済フラグ */  //0にTRUEが入っていたら0にはもう行きました
int		path[MAXSIZE] ;			/* 経路 */  //今まで行った道


/* 隣接リストを表示 */
void Disp( void )
{
	int		i ;
	Cell	*c ;

	printf( "隣接リスト\n" ) ;
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		if( adjacent[i] != NULL ) {
			c = adjacent[i] ;
			do {
				printf( "-|%c|-", c->name ) ;
				c = c->next ;
			} while( c != NULL ) ;
		}
		printf( "\n" ) ;
	}
}


/* データの追加：親ノードparentの子ノードにchildを追加 */
void	Add( int parent, int child )
{
	Cell *p, *q ;

	p = (Cell*)malloc( sizeof(Cell) ) ;
	p->no = child ;
	p->name = 'A' + child ;
	p->next = NULL ;

	if( adjacent[parent] == NULL ) {
		adjacent[parent] = p ;
		return ;
	}

	q = adjacent[parent] ;
	while( q->next != NULL ) {
		q = q->next ;
	}
	q->next = p ;
}


/* グラフの初期化：GraphDataをadjacent[]に代入する */
void InitGraph( void )
{
	
    int i;
    Cell *p, *q ;
	for( i=0 ;i < MAXSIZE ; i++ ){
		visited[i]=FALSE;
	    p = (Cell*)malloc( sizeof(Cell) ) ;
		p->no =  i;
		p->name = 'A' + i ;
		p->next = NULL ;
		adjacent[i] = p;

		p = (Cell*)malloc( sizeof(Cell) ) ;
		p->no =  *GraphData[i] - 'A';
		p->name = *GraphData[i]++ ;
		p->next = NULL ;
		adjacent[i]->next = p;
		
		q = p;

		while(*GraphData[i] != '\0'){
			p = (Cell*)malloc( sizeof(Cell) ) ;
	    	p->no =  *GraphData[i] - 'A';
		    p->name = *GraphData[i]++ ;
		    p->next = NULL ;
			q->next = p;
			q = p;
		}

	}
    
	/*《実装①》*/
	/* 課題説明に従いadjacent[]を初期化するプログラムを作成せよ．*/
	/* ノードの追加はAdd()関数を使用すること．*/

	Disp( ) ;
}


/* 探索した経路を表示 */
void PrintPath( int num )
{
	int i=0 ;
	for( i=0 ; i<=num ; i++){
		printf("%c", path[i] + 'A' );
	}
	printf("\n");
	/*《実装②》*/
	/* 探索した経路を実行例にならって表示するプログラムを作成せよ．*/
}


/* 経路探索 */
void Search( int num, int now, int end )
{
	Cell *p;
	p = adjacent[now];
	visited[now] = TRUE;
	path[num] = now;
	
	if(end == now){
		PrintPath( num );
	}else{
		while(p->next != NULL){
		    p = p->next;
		    if(visited[p->no] == FALSE){
		        Search( num + 1 , p->no , end );
		    }
		}
	}
	visited[now]=FALSE;
	/*《実装③》*/
	/* 課題説明に従い経路を深さ優先探索で探索するプログラムを作成せよ．*/
	/* 再帰呼出を用いて実装すること．*/
	/* now : 現在注目しているノード */
	/* end : ゴールのノード */
	/* num : 現在考えているパスに含まれるノード数から1を引いた数 */
}


/* メイン関数 */
int main( void )
{
	InitGraph( ) ;
	printf( "探索結果\n" ) ;
	Search(0,0,10);
	return 0 ;
}

