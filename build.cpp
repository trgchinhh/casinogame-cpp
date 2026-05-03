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
             << RESET << " Vui lòng chờ biên dịch" << flush;
        i = (i + 1) % 10;
        sleep_for(milliseconds(100));
    }
    cout << "\r                                             \r";
    ancontrochuot(true);
}

void clear(){
    #ifdef _WIN32 
        system("cls");
    #else 
        system("clear");
    #endif
}

int doronghienthi(const char* s){
    int chieurong = 0;
    for(int i = 0; s[i] != '\0'; ){
        unsigned char c = s[i];
        if(c < 128){ 
            chieurong += 1; i += 1; 
        } else{ 
            chieurong += 1; 
            i += 2; 
        }
    }
    return chieurong;
}

int docphim() {
    #ifdef _WIN32
        int c = _getch();
        if (c == 0 || c == 224) {
            switch (_getch()) {
                case 72: return 72; 
                case 80: return 80; 
                case 75: return 75; 
                case 77: return 77; 
            }
        }
        if (c == 13) 
            return 13;
        return c;
    #else
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN]  = 1;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int c = getchar();
        if (c == 27) {
            int c1 = getchar();
            if (c1 == '[') {
                int c2 = getchar();
                switch (c2) {
                    case 'A': c = 72; break; 
                    case 'B': c = 80; break; 
                    case 'C': c = 77; break; 
                    case 'D': c = 75; break; 
                }
            }
        }
        if (c == 10) 
            c = 13;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return c;
    #endif
}

void menu_build(){
    const int somuc = 2;
    const char* menu[somuc] = {
        "Chạy file",
        "Thoát"
    };
    int chon = 0;
    while(true){
        clear();
        cout << "Không có thay đổi -> dùng file build cũ" << RESET << endl;
        cout << "┌───────────────┐" << RESET << endl;

        for (int i = 0; i < somuc; i++) {
            if (i == chon) {
                cout << "│" << RED << " ● " << RESET << menu[i];
                int spaces = 12 - doronghienthi(menu[i]);
                cout << RESET << string(spaces, ' ') << "│" << endl;
            } else {
                cout << "│   " << menu[i];
                int spaces = 12 - doronghienthi(menu[i]);
                cout << RESET << string(spaces, ' ') << "│" << endl;
            }
        }
        cout << "└───────────────┘" << RESET << "\n";
        int phim = docphim();
        if (phim == 72) 
            chon = (chon - 1 + somuc) % somuc;
        else if (phim == 80)
            chon = (chon + 1) % somuc;
        else if (phim == 13) {
            if(chon == 0){
                #ifdef _WIN32
                    system("cd bin && Casino.exe");
                #else
                    system("cd bin && ./Casino");
                #endif
                ancontrochuot(true);
                exit(0);
            } 
            else if(chon == 1){
                ancontrochuot(true);
                exit(0);
            }
        }
    }
}

int main(){
    ancontrochuot(false);
    try {
        #ifdef _WIN32
            system("if not exist bin mkdir bin");
        #else
            system("mkdir -p bin");
        #endif
        if(cacfilecanbiendich()){
            atomic<bool> stop(false);
            thread loading(hieuung_cho, ref(stop));
            int ketqua = system(lenhbiendich.c_str());
            stop = true;
            loading.join();
            if(ketqua != 0){
                throw runtime_error(RED "Biên dịch thất bại !");
            }
            cout << "Biên dịch thành công !" << endl;
            #ifdef _WIN32
                system("cd bin && Casino.exe");
            #else
                system("cd bin && ./Casino");
            #endif
        } 
        else{
            menu_build();
        } 
    } catch(const exception& e){
        cout << RED << "\nLỗi: " << e.what() << RESET << endl;
    }
    ancontrochuot(true);
    return 0;
}
