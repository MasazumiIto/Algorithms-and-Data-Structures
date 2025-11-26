#include <stdio.h>
#include <string.h>

#define	TRUE	1
#define	FALSE	0
#define	MAXSIZE	11
#define	NONE	-1

char	*GraphData[] = {
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
int visited[MAXSIZE];

/*
 * 隣接行列(adj)を表示する
 */
void	PrintAdjMatrix( int adj[MAXSIZE][MAXSIZE] )
{
	int	i, j ;

	printf( "[Adjacent Matrix]\n" ) ;
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		for( j = 0 ; j < MAXSIZE ; j++ ) {
			printf( "%1d ", adj[i][j] ) ;
		}
		printf( "\n" ) ;
	}
	printf( "\n" ) ;
}

/*
 * グラフデータ(GraphData)から隣接行列(adj)を生成する
 */
void	InitGraph( int adj[MAXSIZE][MAXSIZE] )
{
    int i, j;//iが縦、jが横
    
    for ( i=0; i<MAXSIZE; i++){
        visited[i]=FALSE;
        for ( j=0; j<MAXSIZE; j++){
            if(*GraphData[i]-'A' == j ){
                adj[i][j]=TRUE;
                GraphData[i]++;
            }else{
                adj[i][j]= FALSE;
            }
        }
    }

	/*《実装①》*/
	/* GraphDataから隣接行列adj[][]を生成する */
	/* リンクがある場合は1，ない場合は0とする */

	PrintAdjMatrix( adj ) ;
}

/*
 * キュー(q)を表示する
 */
void	PrintQueue( int *q )
{
	int		i ;

	printf( "[queue] { " ) ;
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		if( q[i] != NONE ) {
			printf( "%c ", q[i]+'A' ) ;
		}
	}
	printf( "}\n" ) ;
}

/*
 * キュー(q)の中にデータ(d)が存在するかどうか確認する
 */
int	CheckQueue( int *q, int d )
{
	int		i ;

	for( i = 0 ; i < MAXSIZE ; i++ ) {
		if( q[i] == d ) return TRUE ;
	}
	return FALSE ;
}

/*
 * キュー(q)にデータ(d)を追加する
 */
void	Enqueue( int *q, int d )
{
    int i=0;
    while( q[i] != NONE){
        i++;
    }
    q[i] = d;
	/*《実装②》*/
	/* キューqの最後尾にデータdを追加する */
}

/*
 * キュー(q)からデータを取り除く
 */
int	Dequeue( int *q )
{
    int i=0, j=1, h;
    h=q[i];
    while(q[j]!=NONE){
        q[i] = q[j];
        i++;
        j++;
    }
    q[i] = NONE;
    return h;
	/*《実装③》*/
	/* キューqの先頭の値を返す */
	/* キューの残りの値は先頭方向に1つずつ順送りする */
	/* キューの最後q[MAXSIZE-1]にNONEを入れることを忘れずに */
}

/*
 * 隣接行列(adj)を用いて，
 * 指定地点(now)からゴール(end)まで幅優先経路探索を行う
 */
void	Search( int adj[MAXSIZE][MAXSIZE], int now, int end )
{
    int i;
    int que[MAXSIZE];
    for(i=0;i<=MAXSIZE;i++){
        que[i]=NONE;
    }
    que[0]=now;
    visited[now]=TRUE;
    PrintQueue(que);
    

    while(que[0]!=NONE){
        now=que[0];
        printf("[now] %c ",'A' + now);
        PrintQueue(que);
        Dequeue(que);
        visited[now]=TRUE;
        if(now == end){
            printf("Found");
        }else{
            for(i=0;i<MAXSIZE;i++){
                if(adj[now][i]==1 && visited[i]==FALSE){
                    if(CheckQueue(que,i)==FALSE){
                        Enqueue(que,i);
                    }
                }
            }
        }
    }
    
	/*《実装④》*/
	/* アルゴリズムに従って幅優先探索アルゴリズムを実装せよ */
	/* 幅優先探索の状況出力は実行例のようになるようにすること */
}

/*
 * メイン関数
 */
int main( void )
{
	int	adjacent[MAXSIZE][MAXSIZE] ;	/*隣接行列*/

	InitGraph( adjacent ) ;	/* 隣接行列の初期化 */
	Search( adjacent, 0, MAXSIZE-1 ) ;	/* A(0)からK(10)までの経路 */
	return 0 ;
}