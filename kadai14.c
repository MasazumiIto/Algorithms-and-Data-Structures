#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define	TYPES		6						/* 荷物の種類数 */
#define	MAXCAPACITY	200						/* ナップザックの大きさの上限 */

int	Size[]  = {  2,  3,  5,  7,  9, 15 } ;	/* 荷物の大きさ */
int Value[] = {  2,  4,  7, 11, 14, 24 } ;	/* 荷物の価値 */
/*【注】同じ添え字どうしが対応している．例：荷物1の大きさはSize[1]=3,荷物1の価値はValue[1]=4 */

/*
 *	価値の合計total[]，最後に選んだ荷物choice[]を表示する
 */
void PrintList(int total[], int choice[], int capacity, int step )
{
    int i;
    printf("\nsize   =");
    for(i=0;i<capacity;i++){
        printf("%3d",i);
    }
    printf("\ntotal  =");
    for(i=0;i<capacity;i++){
        printf("%3d",total[i]);
    }
    printf("\nchoise =");
    for(i=0;i<capacity;i++){
        printf("%3d",choice[i]);
    }
	/*
	 *《実装①》
	 *	実行結果の例を参考に，ナップザックのサイズ毎に価値の合計及び最後に選んだ荷物を
	 *	表形式で表示する関数を実装せよ
	 */





}

void DP( int capacity, int Size[], int Value[] ) {

	int	i, j ,t ,n ;
	int	total[MAXCAPACITY] ;	/* 現時点でナップザックに詰め込んだ荷物の価値の合計 */
	int	choice[MAXCAPACITY] ;	/* 最後に選んだ荷物 */
	int	totalsize ;				/* ナップザックに詰め込んだ荷物のサイズの合計 */

	/*
	 *	配列のクリア
	 */
	for( i = 0 ; i < MAXCAPACITY ; i++ ) {
		total[i] = 0 ;
		choice[i] = -1 ;
	}

    for(j=0;j<=capacity;j++){
        for(i=0;i<j/Size[0];i++){
            total[j] += Size[0];
			choice[j]=0;
        }
    }
	/*
	 *《実装②》
	 *	大きさ最小(サイズ2)の荷物を各ナップザックに可能なだけ詰め込むプログラムを実装せよ
	 *	total[]およびchoice[]に適切な値が代入すること．
	 *	なお，実はこの処理は下記の実装③の部分にまとめることができる．
	 *	余力のある人は挑戦してみること．
	 */

    printf("step = 0");
	PrintList( total, choice, capacity, 0 ) ;


	for(j=0;j<TYPES;j++){
		for(i=0;i<capacity;i++){
			for(t=0;t<i;t++){
				n=i-t;
				if(total[i]<total[t] + n / Size[j] * Value[j] ){
					total[i] = total[t] + n / Size[j] * Value[j];
					choice[i] = j;
				}
			}
		}
        printf("\nstep  = %d",j);
		PrintList( total, choice, capacity, j ) ;
			
	}
	/*
	 *《実装③》
	 *	道的計画法の中枢部分の実装
	 *	サイズがSize[i]の荷物をサイズjのナップザックに詰め込む
	 *	Size[0]は実装②で処理済みなのでiを1～TYPES-1の範囲で処理すること．
	 *	iのループが1つ終わるごとにPrintList()を呼び出し，現時点の状況を表示すること．
	 */

	i--;
	while(total[i] != 0){
		printf("\n荷物　%d (サイズ %d,価値 %d)を詰め込む",choice[i],Size[choice[i]],Value[choice[i]]);
		i = i - Size[choice[i]];
	}
	/*
	 *《実装④》
	 *	ナップザックに入れた荷物を表示する
	 */





}

int main( int argc, char *argv[] ) {

	int	capacity,t=0 ; /* ナップザックの大きさ */
    double i;

    capacity = atoi( argv[1] ) ;
    i = atof(argv[1]);
    while (isdigit(argv[1][t])!=0){
        t++; 
    }
    if(argv[1][t]!=NULL){
        capacity=-1;
    }
    while(capacity<0 || capacity>200 || i!=capacity){
        printf("erorr one more input number->");
        gets(argv[1]);
        capacity = atoi( argv[1] ) ;
        i = atof(argv[1]);
        while (isdigit(argv[1][t])!=0){
          t++; 
        }
        printf("%c",argv[1][t]);
        if(argv[1][t]!=NULL){
            capacity=-1;
        }
        printf("\n%d--%s",capacity,argv[1]);
    }
	/*
	 *《実装⑤》
	 *	下記の条件をチェックし，引数が正しく設定されていない場合は，
	 *	再度入力を求めるようにプログラムを実装せよ．
	 *	(1) コマンドラインの引数の数が誤っていないか
	 *	(2) ナップザックの大きさが整数で指定されているかどうか
	 *	(3) ナップザックの大きさが1以上，かつ上限未満になっているかどうか
	 *	再度入力を求める場合，その具体的な方法は各自が決めてよい．
	 */



	/*
	 *	コマンドラインで指定された引数をsizeに代入する．
	 */
	capacity = atoi( argv[1] ) ;
	printf( "Capacity of knapsack is %d\n", capacity ) ;

    DP( ++capacity, Size, Value ) ;
	/*
	 *	動的計画法を実行
	 */

	return 0 ;
}
