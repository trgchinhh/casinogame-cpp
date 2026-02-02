/*****************************************\
 * Casino game code in C++
 * Cấu trúc dữ liệu dựa trên DSLK kép 
 * Gồm màu sắc và hiệu ứng âm thanh 
\*****************************************/

#include <iostream>
using namespace std;

const string tenchuongtrinh = "Casino.exe";
const string lenhbiendich = string("g++ src\\main.cpp ") 
                          + "-IC:\\OpenSSL-Win64\\include "  
                          + "-LC:\\OpenSSL-Win64\\lib src\\resource\\resource.o -o " 
                          + tenchuongtrinh 
                          + " -lwinmm -lssl -lcrypto -w";
                          
int main(){
    system(lenhbiendich.c_str());
    cout << "Đã biên dịch xong ! Chạy file (y/n): ";
    char c; cin >> c;
    if(c == 'y') {
        system(tenchuongtrinh.c_str());
    }
    return 0;
}
