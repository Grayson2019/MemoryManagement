//
//  main.cpp
//  MemoryManagent
//
//  Created by 杨浩 on 2019/5/6.
//  Copyright © 2019 Grayson. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;
#define MAPSIZE 8

typedef struct map{
    int num = 1;
    int addr = 20; // 分区起始地址为20KB
    int size = 12;
    string status = "未分配";
}map;
map Map[MAPSIZE];

void outputResult(){
    cout << "--------------------------\n";
    cout << "分 区 号 " << " 大 小 " << " 起 址 " << " 状 态" << "\n";
    for (int i = 0; i < MAPSIZE; i++) {
        if (Map[i].size > 99 && Map[i].size < 1000) {
            cout << "   " << Map[i].num <<"      "<<  Map[i].size <<"   "<< Map[i].addr <<"  "<< Map[i].status;
            cout << "\n";
            continue;
        }else if (Map[i].size > 999 && Map[i].size < 8192){
            cout << "   " << Map[i].num <<"     "<<  Map[i].size <<"  "<< Map[i].addr <<"  "<< Map[i].status;
            cout << "\n";
            continue;
        }else if (Map[i].size > 8191){
            cout << "   " << Map[i].num <<"    "<<  Map[i].size <<"  "<< Map[i].addr <<"  "<< Map[i].status;
            cout << "\n";
            continue;
        }
        cout << "   " << Map[i].num <<"      "<<  Map[i].size <<"    "<< Map[i].addr <<"   "<< Map[i].status;
        cout << "\n";
    }
    cout << "--------------------------\n";
}

void mfree(map *mp, int num){
    if (mp[num-1].status == "已分配") {
        mp[num-1].status = "未分配";
        outputResult();
    }else
        cout << "指定分区号未分配内存";
    

}

void FF_malloc(map *mp, int size){
    int flag = 0;
    for (int i = 0; i < MAPSIZE; i++) {
        if (mp[i].status == "已分配" || mp[i].size < size) {
            flag++;
            continue;
        }else{
            mp[i].status = "已分配";
            break;
        }
    }
    if (flag == MAPSIZE) {
        cout << "申请内存空间失败！没有合适的内存空间！\n";
    }
}

int main(int argc, const char * argv[]) {
    for (int i = 1; i < MAPSIZE; i++) {
        Map[i].num = i+1;
        Map[i].addr = Map[i-1].addr + Map[i-1].size;
        Map[i].size = Map[i].addr;
        Map[i].status = "未分配";
    }
    outputResult();
    int code;
    do {
        cout << "1.申请内存空间\n";
        cout << "2.回收内存空间\n";
        cout << "3.退出程序\n";
        cout << "请输入对应数字指令:\n";
        cin >> code;
        switch (code) {
            case 1:
                int size;
                cout << "请输入需要申请的内存空间大小:";
                cin >> size;
                FF_malloc(Map, size);
                outputResult();
                break;
                
            case 2:
                int num;
                cout << "请输入需要回收的分区号:";
                cin >> num;
                mfree(Map, num);
                break;
            
            case 3:
                cout << "成功退出程序!";
                break;
            default:
                cout << "输入指令有误，请重新输入:\n";
                break;
        }
    } while (code != 3);
}



