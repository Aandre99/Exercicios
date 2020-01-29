#include <iostream>
#include <string.h>

#define M(x,y) (x > y) ? (x):(y)

using namespace std;

int Memo[1000][1000];

int BackPack(int i, int n, int wid[], int cap[], int cap_Cur){

    if(i == n || cap_Cur <= 0){
        return 0;
    }else{

        if(cap_Cur - wid[i] < 0){
            return BackPack(i+1,n,wid,cap,cap_Cur);
        }else{
            return M(BackPack(i+1,n,wid,cap,cap_Cur), wid[i] + BackPack(i+1,n,wid,cap,cap_Cur-cap[i]));
        }
    }
}
int main(){

    int i,n, capacity;

    cin >> n >> capacity;

    memset(Memo,0,sizeof(Memo));

    int price[n], width[n];

    for (i = 0; i < n; ++i){
        cin >> price[i];
    }

    for (i = 0; i < n; ++i){
        cin >> width[i];
    }

    cout << BackPack(0,n,price,width,capacity);
    return 0;
}
