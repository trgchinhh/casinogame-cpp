//   _____          _             
//  / ____|        (_)            
// | |     __ _ ___ _ _ __   ___  
// | |    / _` / __| | '_ \ / _ \    Casino game C++ 
// | |___| (_| \__ \ | | | | (_) |   https://github.com/trgchinhh/casinogame-cpp
//  \_____\__,_|___/_|_| |_|\___/    Tác giả: Nguyễn Trường Chinh
//                    
// Bản quyền: MIT LICENSE 2026

/*******************************************************\
 * Hoàn thành ngày 20/03/2026 - Bản đa nền tảng        *
 * Cấu trúc dữ liệu dựa trên danh sách liên kết kép    *
 * Gồm màu sắc chữ và hiệu ứng âm thanh                *
 * Lưu data và lịch sử ở các file định dạng JSON       *
 * Bảo mật bằng hash SHA256 (player) và RSA (admin)    *
 * Có thể viết thêm game trong folder src/game/        *
\*******************************************************/

#include <iostream>
#include <exception>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

#define RESET   "\033[0m"
#define RED     "\033[38;2;255;120;120m"

#ifdef _WIN32
    const string tenchuongtrinh = "bin\\Casino.exe";
    const string lenhbiendich = string("g++ src\\main.cpp")
                              + " -IC:\\OpenSSL-Win64\\include"
                              + " -LC:\\OpenSSL-Win64\\lib src\\resource\\resource.o -o "
                              + tenchuongtrinh + 
                              " -lwinmm -lssl -lcrypto -lcurl -w";
#else
    const string tenchuongtrinh = "bin/Casino";
    const string lenhbiendich = string("g++ src/main.cpp")
                              + " -o " 
                              + tenchuongtrinh + 
                              " -lssl -lcrypto -lcurl -w";
#endif

bool cacfilecanbiendich() {
    if(!fs::exists(tenchuongtrinh))
        return true;
    auto thoigiandich_exe = fs::last_write_time(tenchuongtrinh);
    for(auto &p : fs::recursive_directory_iterator("src")){
        if(p.path().extension() == ".cpp" || p.path().extension() == ".h"){
            if(fs::last_write_time(p) > thoigiandich_exe)
                return true;
        }
    }
    return false;
}

int main(){
    try {
        // Kiểm tra tồn tại bin (tạo thư mục bin)
        #ifdef _WIN32
            system("if not exist bin mkdir bin");
        #else
            system("mkdir -p bin");
        #endif
        if(cacfilecanbiendich()){
            cout << "Đang biên dịch ! Vui lòng chờ..." << endl;
            //cout << "Source thay đổi -> Đang biên dịch lại..." << RESET << endl;
            int ketqua = system(lenhbiendich.c_str());
            if(ketqua != 0){
                throw runtime_error(RED "Biên dịch thất bại !");
                exit(0);
            }
        } 
        else cout << "Không có thay đổi -> dùng file build cũ" << RESET << endl;
        cout << "Chạy chương trình (y/n): ";
        char c; cin >> c;
        if(c == 'y'){
            #ifdef _WIN32
                system("cd bin && Casino.exe");
            #else
                system("cd bin && ./Casino");
            #endif
        }
    } catch(const exception& e){
        cout << RED << "\nLỗi: " << e.what() << RESET << endl;
    }
    return 0;
}
