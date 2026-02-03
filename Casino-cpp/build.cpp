/*****************************************\
 * Casino game code in C++
 * Cấu trúc dữ liệu dựa trên DSLK kép 
 * Gồm màu sắc và hiệu ứng âm thanh 
\*****************************************/

#include <exception>
#include <iostream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[38;2;255;120;120m"

const string tenchuongtrinh = "Casino.exe";
const string lenhbiendich = string("g++ src\\main.cpp") 
                          + " -IC:\\OpenSSL-Win64\\include "  
                          + " -LC:\\OpenSSL-Win64\\lib src\\resource\\resource.o -o " 
                          + tenchuongtrinh 
                          + " -lwinmm -lssl -lcrypto -w";

int main(){
    cout << "Đang biên dịch ! Vui lòng chờ..." << endl; 
    try {
        int ketquabiendich = system(lenhbiendich.c_str());
        if(ketquabiendich != 0){
            throw runtime_error("Biên dịch thất bại !");
        }
        cout << "Đã biên dịch xong ! Chạy file (y/n): ";
        char c; cin >> c;
        if(c == 'y') system(tenchuongtrinh.c_str());
    } catch(const exception& e){
        cout << RED << "\nLỗi: " << e.what() << RESET << endl;
    }
    return 0;
}
