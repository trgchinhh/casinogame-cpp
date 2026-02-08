#pragma once
#include <string>
#include <windows.h>
using namespace std;

// Định nghĩa màu và hiệu ứng in 
#define RESET        "\033[0m"
#define WHITE        "\033[38;2;255;255;255m"
#define RED          "\033[38;2;255;120;120m"
#define GREEN        "\033[38;2;120;255;120m"
#define YELLOW       "\033[38;2;255;255;150m"
#define BLUE         "\033[36m"
#define MAGENTA      "\033[95m"     
#define CYAN         "\033[38;2;0;255;255m"
#define ORANGE       "\033[38;2;255;200;80m"
#define INDIGO       "\033[38;2;75;0;130m"     
#define VIOLET       "\033[38;2;180;90;255m"
#define UNDERLINE    "\033[4m"
#define NO_UNDERLINE "\033[24m"

// màu background dùng trong game đoán màu
#define BG_WHITE   "\033[47m"
#define BG_RED     "\033[48;5;196m"
#define BG_ORANGE  "\033[48;5;208m"
#define BG_YELLOW  "\033[48;5;226m"
#define BG_GREEN   "\033[48;5;46m"
#define BG_BLUE    "\033[48;5;27m"
#define BG_INDIGO  "\033[48;5;54m"
#define BG_VIOLET  "\033[48;5;201m"
#define BG_RESET   "\033[0m"

// icon 
#define ICON_USER    "👤 "
#define ICON_DICE    "🎲 "
#define ICON_CARD    "🂡 "
#define ICON_COIN    "🪙 "
#define ICON_HAND    "✊ "
#define ICON_COLOR   "🎨 "
#define ICON_NUMBER  "🔢 "
#define ICON_HISTORY "📜 "
#define ICON_WARN    "⚠ "


// Đạo cụ trong game 
const string matxucxac[7][5] = {
    { "", "", "", "", "" },

    { // 1
        "┌─────────┐",
        "│         │",
        "│    " RED "•" RESET "    │",
        "│         │",
        "└─────────┘"
    },

    { // 2
        "┌─────────┐",
        "│  " RED "•" RESET "      │",
        "│         │",
        "│      " RED "•" RESET "  │",
        "└─────────┘"
    },

    { // 3
        "┌─────────┐",
        "│  " RED "•" RESET "      │",
        "│    " RED "•" RESET "    │",
        "│      " RED "•" RESET "  │",
        "└─────────┘"
    },

    { // 4
        "┌─────────┐",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "│         │",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "└─────────┘"
    },

    { // 5
        "┌─────────┐",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "│    " RED "•" RESET "    │",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "└─────────┘"
    },

    { // 6
        "┌─────────┐",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "│  " RED "•" RESET "   " RED "•" RESET "  │",
        "└─────────┘"
    }
};

const string songuyen[11][7] = {
    { // 0
        "███████",
        "██   ██",
        "██   ██",
        "██   ██",
        "██   ██",
        "██   ██",
        "███████"
    },
    { // 1
        "   ██  ",
        "   ██  ",
        "   ██  ",
        "   ██  ",
        "   ██  ",
        "   ██  ",
        "   ██  "
    },
    { // 2
        "███████",
        "     ██",
        "     ██",
        "███████",
        "██     ",
        "██     ",
        "███████"
    },
    { // 3
        "███████",
        "     ██",
        "     ██",
        "███████",
        "     ██",
        "     ██",
        "███████"
    },
    { // 4
        "██   ██",
        "██   ██",
        "██   ██",
        "███████",
        "     ██",
        "     ██",
        "     ██"
    },
    { // 5
        "███████",
        "██     ",
        "██     ",
        "███████",
        "     ██",
        "     ██",
        "███████"
    },
    { // 6
        "███████",
        "██     ",
        "██     ",
        "███████",
        "██   ██",
        "██   ██",
        "███████"
    },
    { // 7
        "███████",
        "     ██",
        "     ██",
        "     ██",
        "     ██",
        "     ██",
        "     ██"
    },
    { // 8
        "███████",
        "██   ██",
        "██   ██",
        "███████",
        "██   ██",
        "██   ██",
        "███████"
    },
    { // 9
        "███████",
        "██   ██",
        "██   ██",
        "███████",
        "     ██",
        "     ██",
        "███████"
    },
};

const string matdongxu[3][5] = {
    { "", "", "", "", "" }, 

    { // úp 
        "┌┬┬┬┬┬┬┬┬┬┐",
        "├┼┼┼┼┼┼┼┼┼┤",
        "├┼┼┼┼┼┼┼┼┼┤",
        "├┼┼┼┼┼┼┼┼┼┤",
        "└┴┴┴┴┴┴┴┴┴┘"
    },
    { // ngửa
        "┌─────────┐",
        "│         │",
        "│         │",
        "│         │",
        "└─────────┘"
    },

};

const string keobuabao[3][6] = {
    { // kéo
        "    _______       ",
        "---'   ____)____  ",
        "          ______) ",
        "       __________)",
        "      (____)      ",
        "---.__(___)       "
    },
    { // búa
        "    _______  ",
        "---'   ____) ",
        "      (_____)",
        "      (_____)",
        "      (____) ",
        "---.__(___)  "
    },
    { // bao
        "    _______       ",
        "---'   ____)____  ",
        "          ______) ",
        "          _______)",
        "         _______) ",
        "---.__________)   "
    },
};

const string xucxacbaucua[6][5] = {
    { // Bầu
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "BẦU" RESET "   │",
        "│         │",
        "└─────────┘"
    },
    { // Cua
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "CUA" RESET "   │",
        "│         │",
        "└─────────┘"
    },
    { // Tôm
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "TÔM" RESET "   │",
        "│         │",
        "└─────────┘"
    },
    { // Cá
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "CÁ" RESET "    │",
        "│         │",
        "└─────────┘"
    },
    { // Nai
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "NAI" RESET "   │",
        "│         │",
        "└─────────┘"
    },
    { // Gà
        "┌─────────┐",
        "│         │",
        "│   " YELLOW "GÀ" RESET "    │",
        "│         │",
        "└─────────┘"
    }
};

const string xucxac7mau[7][5] = {
    { // ĐỎ
        "┌─────────┐",
        "│" BG_RED "         " RESET "│",
        "│" BG_RED "         " RESET "│",
        "│" BG_RED "         " RESET "│",
        "└─────────┘"
    },
    { // CAM
        "┌─────────┐",
        "│" BG_ORANGE "         " RESET "│",
        "│" BG_ORANGE "         " RESET "│",
        "│" BG_ORANGE "         " RESET "│",
        "└─────────┘"
    },
    { // VÀNG 
        "┌─────────┐",
        "│" BG_YELLOW "         " RESET "│",
        "│" BG_YELLOW "         " RESET "│",
        "│" BG_YELLOW "         " RESET "│",
        "└─────────┘"
    },
    { // XANH LÁ
        "┌─────────┐",
        "│" BG_GREEN "         " RESET "│",
        "│" BG_GREEN "         " RESET "│",
        "│" BG_GREEN "         " RESET "│",
        "└─────────┘"
    },
    { // XANH DƯƠNG
        "┌─────────┐",
        "│" BG_BLUE "         " RESET "│",
        "│" BG_BLUE "         " RESET "│",
        "│" BG_BLUE "         " RESET "│",
        "└─────────┘"
    },
    { // CHÀM
        "┌─────────┐",
        "│" BG_INDIGO "         " RESET "│",
        "│" BG_INDIGO "         " RESET "│",
        "│" BG_INDIGO "         " RESET "│",
        "└─────────┘"
    },
    { // TÍM
        "┌─────────┐",
        "│" BG_VIOLET "         " RESET "│",
        "│" BG_VIOLET "         " RESET "│",
        "│" BG_VIOLET "         " RESET "│",
        "└─────────┘"
    }
};

