#include <iostream>
using namespace std;

int main() {  
    const int maxSize = 100; // 定义最大输入长度  
    char col[maxSize];       // 声明字符数组，大小为maxSize  
  
	printf("请输入颜色:"); scanf("%s",col);
    // 输出颜色字符串的前10个字符，每个字符后面跟一个'|'  
    for (int i = 0; i < 10; i++) {  
        cout << col[i] << '|';  
    }  
    cout << endl; // 换行，以美化输出  
  
    cout << "Hello World" << endl;  
  
    return 0;  
}