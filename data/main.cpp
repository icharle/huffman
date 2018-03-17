//
//  main.cpp
//  哈夫曼编码译码器系统
//
//  Created by John on 2018/3/1.
//  Copyright © 2018年 John. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


int main() {
    string str;
    cout << "请输入一串字符串" <<endl;
    getline(cin, str);
    int cnt[256] = {};                          //ascii总共256个
    for (int i=0; i<str.length(); i++) {
        cnt[(int)(tolower(str[i]))]++;          //不区分大小写  tolower函数转换成小写
    }
    for (int i=0; i<256; i++) {                 //输出统计的各字符的个数
        if (cnt[i]!=0) {
            cout << (char)i << ":" <<cnt[i] <<endl;
        }
    }
    return 0;
}
