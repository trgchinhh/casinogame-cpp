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

#ifdef _WIN32               // Nếu là Windows 
    #define NOMINMAX
    #include <windows.h>
    #include <conio.h>
    #include <mmsystem.h>       // phát hiệu ứng âm thanh
#else                       // Nếu là Linux hoặc HDH khác
    #include <sys/ioctl.h>
    #include <unistd.h> 
    #include <termios.h>
#endif

#include <iostream>
#include <exception>
#include <filesystem>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
namespace fs = filesystem;
using namespace chrono;
using namespace this_thread;

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

void ancontrochuot(bool trangthaicontrochuot){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = trangthaicontrochuot;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #else
        if (trangthaicontrochuot) cout << "\033[?25h"; 
        else cout << "\033[?25l";
    #endif
}

void hieuung_cho(atomic<bool>& dung){
    ancontrochuot(false);
    const char* spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    int i = 0;
    while(!dung){
        cout << "\r" << spinner[i] 
             << RESET << " Vui lòng chờ biên dịch !" << flush;
        i = (i + 1) % 10;
        sleep_for(milliseconds(100));
    }
    cout << "\r                                             \r";
    ancontrochuot(true);
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
            //cout << "Đang biên dịch ! Vui lòng chờ..." << endl;
            //cout << "Source thay đổi -> Đang biên dịch lại..." << RESET << endl;
            atomic<bool> stop(false);
            thread loading(hieuung_cho, ref(stop));
            int ketqua = system(lenhbiendich.c_str());
            stop = true;
            loading.join();
            if(ketqua != 0){
                throw runtime_error(RED "Biên dịch thất bại !");
                exit(0);
            }
            cout << "Biên dịch thành công !" << endl;
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
