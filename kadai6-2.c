#include <stdio.h>
#include <stdlib.h>

#define	HASH_SIZE	9
#define	Hash( key )	( key % HASH_SIZE )

typedef struct _Character {
	int		no ;				/* キー */
	char	name[16] ;			/* 名前 */
	struct _Character	*next ;	/* 次のデータのアドレス */
} Character ;

Character	*HashTable[ HASH_SIZE ] ;

/*
 *	数値の読み込み　(5桁までの正数)
 */
int GetNum(void)
{
	int i, c = 0, d = 0 ;

	rewind( stdin ) ;

	for( i = 0 ; i < 5 && c != '\n' ; i++ ) {
		c = getchar( ) ;
		if( c == '\n' ) break ;
		d = d * 10 + c - '0' ;
	}

	rewind( stdin ) ;
	return d ;
}

/*
 *	データの表示
 */
void Disp( void )
{
	int	i = 0 ;
	Character	*c ;

	for( i = 0 ; i < HASH_SIZE ; i++ ) {
		printf( "[%d|%p]-", i , HashTable[i] ) ;

		/*《実装》*/
		/* HashTable[i]に繋がっているリスト構造の表示 */
        c=HashTable[i];
        while(c!=NULL){ 
            printf("[%p|%d|%s|%p]-",c,c->no,c->name,c->next);
            c=c->next;
        }
        printf("\n");
	}
}

/*
 *	データの追加
 */
void Add( void )
{
	Character	*p, *q ;
	int			key, i,t=0 ;

	p = (Character*)malloc( sizeof(Character) ) ;

	if( p == NULL ) {
		fprintf( stderr, "memory allocation error\n" ) ;
		Disp( ) ;
		return ;
	}

	printf( "No= " ) ;
	p->no = GetNum( ) ;

	printf( "Name= " ) ;
	fgets( p->name, 16, stdin ) ;
	for( i = 0 ; p->name[i] != '\n' && i != 15 ; i++ ) ;
	p->name[i] = '\0' ;

	p->next = NULL ;

	key = Hash(p->no) ;
    
    while(HashTable[key]!=NULL){
        key = Hash(p->no++);
        t++; 
    }
    p->no -= t;
    HashTable[key]=p;
    key -= t;
	/*《実装》*/
	/* HashTable[key]にまだデータが連結していないときは第一要素として，*/
	/* そうでない場合は線形リストの最後にデータを追加する．*/

	Disp( ) ;
}

/*
 *	データの削除
 */
int Del( void )
{
	Character	*head, *target, *prev, *tmp ;
	int	no, key ,count=0,t=1;

    
	Disp( ) ;

	printf( "No= " ) ;
	no = GetNum( ) ;
	key = Hash( no ) ;
	head = HashTable[key] ;
    target = head ;
    while(no != target->no){
        no = no + t;
        key = Hash(no);
        head = HashTable[key] ;
        t++;
        no = no - t; 
        break;
    }

	target = head ;
    if(target == NULL){
        printf("key was not found!\n");
        return -1;
    }else if(target->next==NULL ){
		if(target->no==no){
            HashTable[key]=NULL;
            free(target);
            Disp();
			return 1;
		}
	    printf("key was not found!\n");
        return -1;	
    }else{
        while(target != NULL){
            if(target->no==no && count==0){
                prev=target;
                target=target->next;
                HashTable[key]=target;
                free(prev);
                Disp();
                return 1;
            }else if(target->no==no){
                tmp=(prev->next)->next;
                prev->next=tmp;
                free(target);
                Disp();
                return 1;
            }
        prev=target;
        target=target->next;
        count++;
        }
        printf("key was not found!\n");
        return -1;
    }
	/*《実装》*/
	/* キーが見つかったら該当データを削除してDisp()を呼び出し終了 */
	/* キーが見つからなかったらエラーメッセージを表示し-1を返す */
}

/*
 *	データの検索
 */
int Search( void )
{
	Character	*c ;
	int	no, key ;

	printf( "No= " ) ;
	no = GetNum( ) ;
	key = Hash( no ) ;
	c = HashTable[key] ;
    if(c==NULL){
        printf("key was not found!\n");
        return -1;
    }
    while(c!=NULL){
        if(c->no==no){
            printf("key was found!\n NUM :%d NAME :%s\n",c->no,c->name);
			printf("%dに対するデータは%sです\n",c->no,c->name);
            Disp();
            return 1;
        }
        c=c->next;
    }
    printf("key was not found!\n");
    return -1;
	/*《実装》*/
	/* キーが見つかったら対応する名前を表示してDisp()を呼び出す */
	/* 見つからなかったらエラーメッセージを表示し-1を返す */
}

/*
 *	メニュー表示
 */
int Menu( void )
{
	int	c ;

	while( 1 ) {
		printf( "1 表示\n" ) ;
		printf( "2 追加\n" ) ;
		printf( "3 削除\n" ) ;
		printf( "4 探索\n" ) ;
		printf( "5 終了\n" ) ;
		c = GetNum( ) ;
		if( 1 <= c && c <= 5 ) break ;
	}

	switch( c ) {
		case 1 :	Disp( ) ; break ;
		case 2 :	Add( ) ; break ;
		case 3 :	Del( ) ; break ;
		case 4 :	Search( ) ; break ;
		case 5 :	return 1 ;
	}
	return 0 ;
}

/*
 *	メイン関数
 */
int main( void )
{
	int i, end = 0 ;
    Character *p,*prev;

	for( i = 0 ; i < HASH_SIZE ; i++ ) {
		HashTable[i] = NULL ;
	}

	while( !end ) {
		end = Menu( ) ;
	}

    for(i=0;i<HASH_SIZE;i++){
        p=HashTable[i];
        while(p!=NULL){
            prev=p;
            p=p->next;
            free(prev);
        }
    }
	return 0 ;
}
