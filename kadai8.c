#include <stdio.h>
#include <stdlib.h>

#define	KeyNum	8

typedef struct _Node {
	struct _Node	*left ;
	int				value ;
	struct _Node	*right ;
} Node ;

/* 数値を入力する関数 */

int	GetNum( void )
{
	int	i, d=0, c=0 ;

	rewind( stdin ) ;

	for( i = 0 ; i < 5 && c != '\n' ; i++ ) {	/* 5桁まで */
		c = getchar( ) ;
		if( c == '\n' ) break ;
		d = d * 10 + c - '0' ;
	}
	rewind( stdin ) ;

	return d ;
}

/* ノードを追加する */

Node* AddNode( int value )
{
	Node	*node ;

	node = (Node*)malloc( sizeof(Node) ) ;
	node->left = NULL ;
	node->value = value ;
	node->right = NULL ;
	return node ;
}

/* 木にノードを追加する */

Node* MakeTree( Node *node, int value )
{
	if( node == NULL ) {
		node = AddNode( value ) ;
		return node ;
	}

	if( value > node->value ) {
		node->right = MakeTree( node->right, value ) ;
	} else if( value < node->value ) {
		node->left = MakeTree( node->left, value ) ;
	}
	return node ;
}

/* ツリーの表示 */

void PrintTree( Node *node )
{
	int			i ;
	static int	depth = 0 ;

	if( node->left != NULL ) {
		depth++ ;
		PrintTree( node->left ) ;
		depth-- ;
	}

	for( i = 0 ; i < depth ; i++ ) {
		printf( "\t" ) ;
	}
	printf( "[%2d]\n", node->value ) ;

	if( node->right != NULL ) {
		depth++ ;
		PrintTree( node->right ) ;
		depth-- ;
	}
}

/* ツリー内の探索を行う */

void Search( Node *node, int value )
{
	int			i ;


    printf("[%d]->",node->value);
    if( node->value == value ) {
        printf("Found!\n");
        return;

    }
	if( node->value > value ) {
        if(node->left != NULL){
    		Search( node->left , value ) ;
        }else{
			printf("Not Found\n");
		}
	}
	if( node->value < value ) {
        if(node->right != NULL){
    		Search( node->right , value ) ;
        }else{
			printf("Not Found\n");
		}
	}
 
    /*《実装①》*/
	/* 課題説明に従い，実行例と同様の表示を行うよう関数を実行せよ．*/
	/* PrintTree()が参考になる．*/
}

/* メイン関数 */

int main( void )
{
	Node	*root ;
	int		i, value ;

	for( i = 0 ; i < KeyNum ; i++ ) {
		printf( "%d> ", i+1 ) ;
		value = GetNum( ) ;
		if( i == 0 ) {
			root = MakeTree( NULL, value ) ;
		} else {
			MakeTree( root, value ) ;
		}
	}

	PrintTree( root ) ;
    
    while ( value != 0){
        printf("key> ");
        value = GetNum( ) ;
        if( value != 0){
            Search( root, value);
        }
    }
	/*《実装②》*/
	/* (1)探索キーの入力，(2)探索とその結果の表示，を繰り返し行う．*/
	/* 探索キーとして0が入力されたらプログラムを終了する．*/
	/* 課題説明および実行例の画面を参照のこと．*/

	return 0 ;
}
