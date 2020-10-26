#include <stdio.h>
#include <stdlib.h>

#define Elemtype int
#define m 4
#define n 3


void Findminmax(Elemtype a[m][n]) {//m行n列
    int flag = 0;
    Elemtype point;
    for (int i = 0; i < m; i++) {
        int max_index = 0;
        int min_index = 0;
        if (!flag) {
            for (int j = 0; j < n; j++) { //找每行最小的下标
                if (a[i][j] < a[i][max_index]) { max_index = j; }
            }
            point = a[i][max_index];
        }
        else { ; }
            for (int j = 0; j < n; j++) {
                if (a[i][j] == point) {
                    int k = 0;
                    for (; k < m; k++) {//比较该列元素与当前point的大小关系
                        if (point < a[k][j]) { break; }
                        //if (a[k][j] > a[min_index][j]) { min_index = k; }
                    }
                    if (k == m) {
                        printf("%d %d\n", i, j); flag = 1;
                    }
                }
                else { ; }
            }
    }
    if (!flag) { printf("NONE"); }
    return 0;
}

int main(){
    Elemtype a[4][3] = {2,2,2,
                        5,4,5,
                        2,2,2,
                        2,2,2,};
    Findminmax(a);
    return 0;
}