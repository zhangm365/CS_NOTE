


#include<bits/stdc++.h>

using namespace std;

int a[1025][1025];

// 记录每部分左上角的坐标跟长度
void fx(int x, int y, int len){
 if (len == 2){
  a[x + 1][y] = 1;
  a[x][y + 1] = 1;
  a[x + 1][y + 1] = 1;
  return;
 }
 // 左上区域 全部为0
 for (int i = x; i < x + len / 2; i++){
  for (int j = y; j < y + len / 2; j++){
   a[i][j] = 0;
  }
 }
        // 左下区域
 fx(x + len / 2, y, len / 2);
        // 右上区域
 fx(x, y + len/2, len/2);
        // 右下区域
 fx(x + len / 2, y + len / 2, len / 2);
}

int main(){
 int n, m;
 cin >> n;
 m = pow(2, n);
 fx(0, 0, m);
 for (int i = 0; i < m; i++){
  for (int j = 0; j < m; j++){
   cout << a[i][j];
   if (j != m - 1) cout << " ";
  }
  cout << endl;
 }
 return 0;
}