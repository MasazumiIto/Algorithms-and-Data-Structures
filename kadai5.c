#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	NAME_LEN	16

typedef struct _Station {
	char	name[NAME_LEN] ;
	int		time ;
	struct _Station *next ;
} Station ;

Station	*head ;
int		station_num = 0 ;

/* キーボードから入力された番号を読み取る */
int get_num( void )
{
	int i = 0;
	int d = 0 ;
	int c = 0 ;

	rewind( stdin ) ;
	for( i = 0 ; i < 5 && c != '\n' ; i++ ) { /*5桁まで*/
		c = getchar( ) ;
		if( c == '\n' ) break ;
		d = d * 10 + c - '0' ;
	}
	rewind( stdin ) ;
	return d ;
}

/* ファイルからデータを読み込む */
int read_data( char *fn )
{
	FILE	*fp ;
	Station	*s, *tmp ;
	/*char	name[NAME_LEN] ;*/
	/*int		time ;*/

	/*《実装》*/
	/* 初期データファイルをオープン．失敗したら-1を返り値として終了 */

	/*《実装》*/
	/* ファイルの内容を読み込み線形リストを作成する．*/
	/* 線形リストの先頭はheadに記憶するものとし，最後のデータのnext */
	/* 構造体メンバーはNULLとする．*/
    fp=fopen(fn,"r");
    	if(fp == NULL) {
		printf("%s file not open!\n", fn);
		return -1;
	} else {
		printf("%s file opened!\n", fn);
	}
	s=(Station*)malloc(sizeof(Station));
	head = s;
    while(fscanf(fp,"%s %d",s->name,&(s->time))!=EOF){
		tmp=s;
		s++;
		s=(Station*)malloc(sizeof(Station));
		tmp->next=s;
    }
	tmp->next=NULL;
	free(s);
	fclose( fp ) ;
	return 0 ;
}

/* 線形リストを表示する */
void station_disp( void )
{
	Station	*s = head ;

	while( 1 ) {
		printf( "ADDR %p\n", s ) ;
		printf( "NAME %s\n", s->name ) ;
		printf( "TIME %d\n", s->time ) ;
		printf( "NEXT %p\n", s->next ) ;
		printf( "\n" ) ;
        s=s->next;
		if(s==NULL){
			break;
		}
		/*《実装》*/
		/* sがNULLなら終了．そうでない場合は，sが次のデータを */
		/* 指すように変更する．*/

	}
}

/* 引数で渡された駅名がリストに存在するか確認する */
Station *check( char *target )
{
	Station *s = head ;
	int i =0,count_l =0,count_tar=0;
	while(target[count_tar]!= '\0'){
		/*printf("%c",target[count_tar]);*/
        count_tar++;
	}
	while(s != NULL){
		while(s->name[count_l]!= '\0'){
			/*printf("%c",s->name[count_l]);*/
            count_l++;
	    }
		/*printf("%d",count_l);*/
		/*printf("\n")*/;
	    for(i=0;i<count_l;i++){
            if(target[i]!=s->name[i]){
	    		break;
	    	}
	    }
	    if(i==count_l && count_l==count_tar){
	    	return s;
	    }
		s=s->next;
		count_l=0;
	}
	return NULL;

	/*《実装》*/
	/* 線形リストの中にtargetの駅名がある場合は，その構造体の */
	/* ポインタを返す．リストにtargetがない場合はNULLを返す．*/

}

/* データの追加 */
void add( void )
{
	Station *s, *ns ;
	char	name[NAME_LEN] ;
	int		i ;

	/*《実装》*/
	/* 追加するデータのための，Station型のメモリを確保し，*/
	/* そのポインタをnsに代入する．*/

	/*《実装》*/
	/* 追加する駅名と前駅からの所要時間をキーボードから入力し，*/
	/* 構造体メンバーに代入する．*/
	/* 所要時間はget_num()を使って読み込む．*/

	ns=(Station*)malloc(sizeof(Station));
	rewind(stdin);
	printf("NAME = ");
	fgets( ns->name, NAME_LEN, stdin ) ;
	for( i = 0 ; ns->name[i] != '\n' && i < NAME_LEN - 1 ; i++ ) ;
	ns->name[i] = '\0' ;
	do{
	    printf("TIME = ");
	    scanf("%d",&(ns->time));
	    rewind(stdin);
	}while((ns->time)<0);

	station_disp( ) ;

	do {
		printf( "どの駅の後に追加しますか？\n" ) ;
		printf( "NAME = " ) ;
		fgets( name, NAME_LEN, stdin ) ;
		for( i = 0 ; name[i] != '\n' && i < NAME_LEN - 1 ; i++ ) ;
		name[i] = '\0' ;
	} while( ( s = check( name ) ) == NULL ) ;

	ns->next = s->next;
	s->next = ns;
	/*《実装》*/
	/* データをつなぐ処理を行う */

	station_disp( ) ;
}

/* データの削除 */
void del( void )
{
	Station *current, *prev ,*p;
	char	name[NAME_LEN] ;
	int		i =0;

    prev=head;
    while(prev != NULL){
		prev=prev->next;
		i++;
	}
    if(i>1){
	    station_disp( ) ;

	    do {
    		printf( "どの駅を削除しますか？\n");
    		printf( "NAME = " ) ;
    		fgets( name, NAME_LEN, stdin ) ;
     		for( i = 0 ; name[i] != '\n' && i < NAME_LEN - 1 ; i++ ) ;
    		name[i] = '\0' ;
    	} while( ( current = check( name ) ) == NULL ) ;

    	if(current==head){
    		head=current->next;
    	}else{
	        prev=head;
	        while(prev->next != current){
	        	prev=prev->next;
	        }
    	    p=(prev->next)->next;
    	    prev->next=p;
	    }
	/*《実装》*/
	/* 指定された駅を削除し，ポインタを張り替えて線形リストを */
	/* 再構成する．リスト中に要素が1つしかない場合は削除できない */
	/* ものとする．*/
	    free(current);
	    station_disp( ) ;
	}else{
		printf("消去できません\n");
	}
}

/* 所用時間の計算 */
void calc( void )
{
	Station *from, *to ,*p;
	char	name[NAME_LEN] ;
	int		sum = 0 ;
	int		i =0;
	p=head;
    while(p!=NULL){
		p=p->next;
		i++;
	}
	if(i>1){
	    station_disp( ) ;
	    do {
	    	printf( "どの駅からどの駅までの所要時間を計算しますか？\n" ) ;
	    	printf( "FROM = " ) ;
	    	fgets( name, NAME_LEN, stdin ) ;
	    	for( i = 0 ; name[i] != '\n' && i < NAME_LEN - 1 ; i++ ) ;
	    	name[i] = '\0' ;
	    } while( ( from = check( name ) ) == NULL || (from->next)==NULL) ;
	    do {
	    	printf( "TO = " ) ;
	    	fgets( name, NAME_LEN, stdin ) ;
	    	for( i = 0 ; name[i] != '\n' && i < NAME_LEN - 1 ; i++ ) ;
	    	name[i] = '\0' ;
	    } while( ( to = check( name ) ) == NULL || to==head) ;

	    printf( "%sから%sまでの所要時間は", from->name, to->name ) ;

	/*《実装》*/
	/* 所要時間を計算しsumに代入する */
	    p=from->next;
	   while(p != to->next){
	       sum=sum+(p->time);
	        p=p->next;
	    }
	    printf( "%d分です．\n", sum ) ;
	    }else{
            printf("計算できません");
	    }
}


/* メニューの表示 */
int menu( void )
{
	int		c ;

	while( 1 ) {
		printf( "1 : 表示\n" ) ;	/* \はおまじない．外すとどうなるか試して見よ */
		printf( "2 : 追加\n" ) ;
		printf( "3 : 削除\n" ) ;
		printf( "4 : 所要時間\n" ) ;
		printf( "5 : 終了\n" ) ;

		c = get_num( ) ;

		if( 1 <= c && c <= 5 )
			break ;
		else
			printf( "1から5までの数字を入力してください．\n" ) ;
	}

	switch( c ) {
		case 1:
			station_disp( ) ; break ;
		case 2:
			add( ) ; break ;
		case 3:
			del( ) ; break ;
		case 4:
			calc( ) ; break ;
		case 5:
			return 1 ;
	}
	return 0 ;
}

/* メイン関数 */
int main( int argc, char *argv[] )
{
	int end ;
	Station *p=head,*prev;

	if( argc == 2 ) {
		end = read_data( argv[1] ) ;
	} else {
		fprintf( stderr, "初期データファイルを指定してください．\n" ) ;
		return -1 ;
	}

	while( !end ) {
		end = menu( ) ;
	}
	while(p!=NULL){
		prev=p;
		p=p->next;
		free(prev);
	}
	return 0 ;
}
/*6-プログラム初期データ.txt*/