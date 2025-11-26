#include <stdio.h>
#include <string.h>

#define	TRUE	1
#define	FALSE	0
#define	MAXSIZE	13
#define	NONE	-1

char	*GraphData[] = {
	"BD",		/* 東京A : B D */
	"ACDEF",	/* 埼玉B : A C D E F */
	"BFGH",		/* 群馬C : B F G H */
	"ABE",	/* 千葉D : A B E */
	"BDFG",		/* 茨城E : B D F G */
	"BCEG",		/* 栃木F :  B C E G*/
	"CEFHIJ",		/* 福島G : C E F H I J */
	"CGI",		/* 新潟H :  C G I */
	"GHJK",		/* 山形I :  G H J K*/
	"GIKL",		/* 宮城J :  G I K L*/
	"IJLM",		/* 秋田K :  I J L M*/
	"JKM",       /* 岩手L :  J K M*/
	"KL"        /* 青森M :  K L*/
} ;
int visited[MAXSIZE];
char name[MAXSIZE][20] = {
    "Tokyo    ",
    "Saitama  ",
    "Gunnma   ",
    "Chiba    ",
    "Ibaraki  ",
    "Tochigi  ",
    "Fukushima",
    "Niigata  ",
    "Yamagata ",
    "Miyagi   ",
    "Akita    ",
    "Iwate    ",
    "Aomori   "
} ;
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
void	PrintQueue( int e )
{
	int		i,t=0,n,p ;

    for(i=1; i<=visited[e];i++){
	    while(visited[t] != i ){
    	    t++;
    	}
    	t++;
    	for(n=0;n<MAXSIZE;n++){
    	    if(visited[n] == i+1){
    	        for(p=1;p<i;p++){
    	            printf("             ");
    	        }
    	        printf("[%s]->[%s](%d)\n",name[t-1],name[n],t);
    	    }
    	}
    }
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


    while(que[0]!=NONE){
        now=que[0];
        Dequeue(que);
        if(now == end){
            PrintQueue(end);
        }else{
            for(i=0;i<MAXSIZE;i++){
                if(adj[now][i]==1 && visited[i]==FALSE){
                    if(CheckQueue(que,i)==FALSE){
                        Enqueue(que,i);
                        visited[i] = visited[now]+1;
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
	
	
	int i;
	for(i=0;i<MAXSIZE;i++){
	    printf("%d_",visited[i]);
	}
	return 0 ;
}