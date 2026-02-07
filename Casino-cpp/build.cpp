//   _____          _             
//  / ____|        (_)            
// | |     __ _ ___ _ _ __   ___  
// | |    / _` / __| | '_ \ / _ \    Casino game C++ 
// | |___| (_| \__ \ | | | | (_) |   https://github.com/trgchinhh/casinogame-cpp
//  \_____\__,_|___/_|_| |_|\___/    Tác giả: Nguyễn Trường Chinh
//                    
// Bản quyền: MIT LICENSE 2026

/*******************************************************\
 * Hoàn thành ngày 07/02/2026                          *
 * Cấu trúc dữ liệu dựa trên danh sách liên kết kép    *
 * Gồm màu sắc chữ và hiệu ứng âm thanh                *
 * Lưu data và lịch sử ở các file định dạng JSON       *
 * Bảo mật bằng hash SHA256 (player) và RSA (admin)    *
 * Có thể viết thêm game trong folder src/game/        *
\*******************************************************/

#include <iostream>
#include <exception>
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
        if(ketquabiendich != 0) 
            throw runtime_error("Biên dịch thất bại !");
        cout << "Đã biên dịch xong ! Chạy file (y/n): ";
        char c; cin >> c;
        if(c == 'y') 
            system(tenchuongtrinh.c_str());
    } catch(const exception& e){
        cout << RED << "\nLỗi: " << e.what() << RESET << endl;
    }
    return 0;
}
