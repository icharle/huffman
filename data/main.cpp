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
#define MAXVALUE 1000000       //为后面选取权值最小的两个结点
#define MAXLEAF 30             //叶子结点数
#define MAXNODE MAXLEAF*2-1    //结点总数

typedef struct {
    double weight;
    int parent,lchild,rchild;
    char value;
}HNodeType;

HNodeType HuffNode[MAXNODE]; /* 定义一个结点结构体数组 */

void HuffmanTree(HNodeType HuffNode[MAXNODE], int arr[], int n){
    int i,j,z,p1,p2;          //p1,p2哈夫曼树过程中最小的两个权值数组的下标
    double min1,min2;       //哈夫曼树过程中最小的两个权值
    
    //初始化
    for(i=0; i<n; i++){
        HuffNode[i].weight = 0;
        HuffNode[i].parent = -1;
        HuffNode[i].lchild = -1;
        HuffNode[i].rchild = -1;
    }
    
    //输入n个叶子的权值
    z=0;
    for(i=0; i<256; i++){
        if(arr[i]!=0){
            HuffNode[z].value = (char)i;
            HuffNode[z].weight = arr[i];
            z++;
//            cout << (char)i << ":" <<arr[i] << endl;
//            cout << z << endl;
//            z++;
        }
    }
    
    
    
    //构建哈夫曼树
    for(i=0; i<n-1; i++){
        min1=min2=MAXVALUE;
        p1=p2=0;
        for (j=0; j<n+i; j++) {
            if (HuffNode[j].weight<min1 && HuffNode[j].parent==-1)
            {
                min2 = min1;
                p2 = p1;
                min1 = HuffNode[j].weight;
                p1 = j;
            }
            else if (HuffNode[j].weight < min2 && HuffNode[j].parent==-1)
            {
                min2=HuffNode[j].weight;
                p2=j;
            }
        }
        
        HuffNode[p1].parent  = n+i;
        HuffNode[p2].parent  = n+i;
        HuffNode[n+i].parent = -1;
        HuffNode[n+i].weight = min1+min2;
        HuffNode[n+i].lchild = p1;
        HuffNode[n+i].rchild = p2;
        cout<<"x1.weight and x2.weight in round "<<i+1<<"\t"<<HuffNode[p1].weight<<"\t"<<HuffNode[p2].weight<<endl;
    }
    
}

int main() {
    string str;
    int count=0;                                  //统计字符的种类数
    cout << "请输入一串字符串" <<endl;
    getline(cin, str);
    int cnt[256] = {};                          //ascii总共256个
    for (int i=0; i<str.length(); i++) {
        cnt[(int)(tolower(str[i]))]++;          //不区分大小写  tolower函数转换成小写
        //计算字符的种类数
        if(cnt[(int)(tolower(str[i]))] == 1){
            count++;
        }
    }
    
    HuffmanTree(HuffNode, cnt, count);
//    for (int i=0; i<256; i++) {                 //输出统计的各字符的个数
//        if (cnt[i]!=0) {
//            cout << (char)i << ":" <<cnt[i] <<endl;
//        }
//    }
//    cout << count <<endl;
    return 0;
}
