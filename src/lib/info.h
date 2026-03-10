#include <iostream>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
#endif
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[38;2;255;120;120m"
#define GREEN   "\033[38;2;120;255;120m"
#define YELLOW  "\033[38;2;255;255;150m"
#define CYAN         "\033[38;2;0;255;255m"
#define UNDERLINE    "\033[4m"
#define NO_UNDERLINE "\033[24m"

const string noidungthongtin =
"\n"
"\t┌───────────────────────────────────────────────────┐\n"
"\t│          " RED "CASINO GAMES CONSOLE CUSTOM TUI" RESET "          │\n"
"\t├───────────────────────────────────────────────────┤\n"
"\t│ (" RED "◉" RESET ") " CYAN "Phiên bản:" RESET " v1.3.0                             │\n"
"\t│ (" RED "◉" RESET ") " CYAN "Hoàn thành:" RESET " 28/02/2026                        │\n"
"\t│ (" RED "◉" RESET ") " CYAN "Giấy phép:" RESET " MIT                                │\n"
"\t│ (" RED "◉" RESET ") " CYAN "Bản quyền:" RESET " © 2026 - Nguyễn Trường Chinh       │\n"
"\t│ (" RED "◉" RESET ") " CYAN "Github: " RESET UNDERLINE "github.com/trgchinhh/casinogame-cpp" NO_UNDERLINE "   │\n"
"\t└───────────────────────────────────────────────────┘\n";
