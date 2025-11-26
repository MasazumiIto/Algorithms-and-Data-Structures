#include <stdio.h>
#include <time.h>

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 1  /* 1:通常版，  0:番兵版   */
#define LOOP   1  /* 1:ループ版，0:再帰版   */

#define N  41000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */ 

int compair = 0;
/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
        	compair = i;
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
    data[N+1]=target;
    while(target != data[count]) count++;
    compair=count;
    if(count >= N) return -1;
    else return count;
    
#endif
}

/* クイックソート */
void quick(int list[], int left, int right)
{
    int i, last;
    int temp;

    if (left >= right)
        return;

    last = left;
    for (i=left+1; i <= right; i++){
        if (list[i] < list[left] ){
            last++;
            temp=list[last];
            list[last]=list[i];
            list[i]=temp;
        }
    }

    temp=list[left];
    list[left]=list[last];
    list[last]=temp;

    quick(list, left, last-1);
    quick(list, last+1, right);
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
    int mid;
#if LOOP 
	// 完成
    /* ループバージョン */
    /* 実装せよ */
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
    while(low <= high){
    	mid = (low + high) / 2;
    	if(data[mid] > target){
    		high = mid-1;
    		compair++;
    	} else if(data[mid] < target) {
    		low = mid+1;
    		compair++;
    	}else return mid;
    }
    return -1;
#else
	// 完成
    /* 再帰バージョン */
    /* 実装せよ */
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */
    if(low > high) return -1;
    mid = (low + high) / 2;
    if(data[mid] > target){
    	compair++;
    	b_search(data,low,mid-1,target);
    }else if(data[mid] < target){
    	compair++;
    	b_search(data,mid+1,high,target);
    }else{
    	return mid;
    }
#endif
}

/* メイン */
int main(void)
{
    int i, target, work[N+1], index;
    long cpu_time;
    double time;
    for( i = 0; i < N; i++ ){
    	work[i] = rand() % N;
    }
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
    compair = 0;
#if LINEAR
        work[N] = target; // 番兵版を実行する場合を想定して、配列の最後に"番兵"を置く
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("○");
        else
            printf("×");
        printf("Compaired %d times\n",compair);
    }
    cpu_time = clock();
    time = cpu_time / 1000.0;
    printf("\nExecution time = %f second\nSearched record = %d",time,N);
    return 0;
}

//線形探索通常版
/*
	
*/

//線形探索番兵版
/*
	
*/

//二分探索ループ版
/*
	
*/

//二部探索再帰版
/*
	
*/