//
//  main.cpp
//  哈夫曼编码译码器系统
//
//  Created by John on 2018/3/1.
//  Copyright © 2018年 Icharle. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <cassert>
using namespace std;
#define MAXBIT 100             //存放编码
#define MAXVALUE 1000000       //为后面选取权值最小的两个结点
#define MAXLEAF 30             //叶子结点数
#define MAXNODE MAXLEAF*2-1    //结点总数

typedef struct {
    double weight;
    int parent,lchild,rchild;
    char value;
}HNodeType;


typedef struct {
    int bit[MAXBIT];
    int start;
}HCodeType;

HNodeType HuffNode[MAXNODE];    //定义一个结点结构体数组
HCodeType HuffCode[MAXLEAF];    // 定义一个编码结构体数组


//构建哈夫曼树
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
        HuffNode[n+i].parent = -1;          //构建一个新根
        HuffNode[n+i].weight = min1+min2;
        HuffNode[n+i].lchild = p1;
        HuffNode[n+i].rchild = p2;
        cout << HuffNode[n+i].weight <<"\t" << HuffNode[p1].weight << "\t" << HuffNode[p2].weight <<endl;
        //cout<<"x1.weight and x2.weight in round "<<i+1<<"\t"<<HuffNode[p1].lchild<<"\t"<<HuffNode[p1].rchild<<"\t"<<HuffNode[p1].weight<<"\t"<<HuffNode[p2].weight<<"\t"<<HuffNode[p2].lchild<<"\t"<<HuffNode[p2].rchild<<"\t"<<endl;
    }
    
}


//哈夫曼编码
void HuffmanCode(HCodeType HuffCode[MAXLEAF], int n){
    HCodeType temp;         //定义临时变量
    int i,j,c,p;
    for(i=0;i<n;i++)
    {
        temp.start=n-1;
        c=i;
        p=HuffNode[c].parent;
        while(p!=-1)
        {
            if(HuffNode[p].lchild==c)
                temp.bit[temp.start]=0;
            else
                temp.bit[temp.start]=1;
            temp.start--;
            c=p;
            p=HuffNode[c].parent;    // 循环
        }
        for (j=temp.start+1; j<n; j++)                      // 把叶子结点的编码信息从临时变量中复制出来，放入编码结构体数组
            HuffCode[i].bit[j]=temp.bit[j];
        HuffCode[i].start=temp.start;
    }
    
    //输出结果
    for(i=0;i<n;i++)
    {
        cout<<HuffNode[i].value<<": Huffman code is: ";
        for(j=HuffCode[i].start+1;j<n;j++)
            cout<<HuffCode[i].bit[j];
        cout<<endl;
    }
}

//哈夫曼编码压缩(所有字符的)
void HuffmanCodeAll(string arr,int n){
    cout << "下列输出所有文字的Huffman code: " << endl;
    int arrcount = arr.length();                        //原文章的字符总数
    int codecount = 0 ;                                     //编码后的所有总数
    for(int i=0; i<arr.length(); i++){
        for (int j=0; j<n; j++) {
            if ( tolower(arr[i]) == HuffNode[j].value) {
                for(int z=HuffCode[j].start+1;z < n; z++){
                    cout<<HuffCode[j].bit[z];
                    codecount++;
                }
            }
        }
    }
    cout << endl;
    cout << "压缩的效率为：" <<endl;
    codecount = codecount / 8;                                              //计算编码后的字符串总数
    if( codecount%8 != 0 ){                                                 //除不完情况下，加一处理
        codecount++;
    }
    printf("%.2lf%%\n",(double)(arrcount-codecount)/arrcount*100);          //输出压缩百分比
}

//哈夫曼译码操作
void HuffmandeCode(int count){
    string arr;
    cout << "请输入一串字符串" <<endl;
    int j = count*2 -2;
    getline(cin, arr);
    cout << "下面为译码的结果" <<endl;
    for (int i=0; i<arr.length(); i++) {
        if (arr[i] == '0') {
            j = HuffNode[j].lchild;
        }else if (arr[i] == '1'){
            j = HuffNode[j].rchild;
        }
        if (HuffNode[j].lchild == -1 && HuffNode[j].rchild == -1) {
            cout << HuffNode[j].value;
            j = count*2 -2;;
        }
    }
    cout <<endl;
}


int main() {
    string str;
    int count=0;                                  //统计字符的种类数
    cout << "请输入一串字符串" <<endl;
    ifstream inFile("test.txt");    // fileName内容读取到file中 （按照实际情况修改)
    getline(inFile, str);
    int cnt[256] = {};                          //ascii总共256个
    for (int i=0; i<str.length(); i++) {
        cnt[(int)(tolower(str[i]))]++;          //不区分大小写  tolower函数转换成小写
        //计算字符的种类数
        if(cnt[(int)(tolower(str[i]))] == 1){
            count++;
        }
    }
    HuffmanTree(HuffNode, cnt, count);             //构建哈夫曼树
    HuffmanCode(HuffCode,count);                   //哈夫曼编码
    HuffmanCodeAll(str,count);                     //哈夫曼编码压缩(所有字符的)
    HuffmandeCode(count);
    return 0;
}
