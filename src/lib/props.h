#pragma once
#include <string>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else 
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

// icon 
#define ICON_USER       "👤 "
#define ICON_HGAME      "🎮️ "
#define ICON_DICE       "🎲 "
#define ICON_CARD       "🂡 "
#define ICON_COIN       "🪙 "
#define ICON_HAND       "✊ "
#define ICON_COLOR      "🎨 "
#define ICON_NUMBER     "🔢 "
#define ICON_HISTORY    "📜 "
#define ICON_PERSON     "👥 "
#define ICON_WARN       "⚠ "

// màu background dùng trong game đoán màu
#define BG_WHITE        "\033[47m"
#define BG_RED          "\033[48;5;196m"
#define BG_ORANGE       "\033[48;5;208m"
#define BG_YELLOW       "\033[48;5;226m"
#define BG_GREEN        "\033[48;5;46m"
#define BG_BLUE         "\033[48;5;27m"
#define BG_INDIGO       "\033[48;5;54m"
#define BG_VIOLET       "\033[48;5;201m"
#define BG_RESET        "\033[0m"

// định nghĩa gạch chân 
#define UNDERLINE       "\033[4m"
#define NO_UNDERLINE    "\033[24m"

// Định nghĩa màu và hiệu ứng in (42 màu)
#define RESET           "\033[0m"
#define WHITE           "\033[38;2;255;255;255m"
#define RED             "\033[38;2;255;120;120m"
#define GREEN           "\033[38;2;120;255;120m"
#define YELLOW          "\033[38;2;255;255;150m"
#define BLUE            "\033[38;2;100;150;255m"
#define MAGENTA         "\033[38;2;255;100;255m"    
#define CYAN            "\033[38;2;0;255;255m"
#define ORANGE          "\033[38;2;255;200;80m"
#define INDIGO          "\033[38;2;75;0;130m"     
#define VIOLET          "\033[38;2;180;90;255m"
#define GRAY            "\033[38;2;150;150;150m"
#define PINK            "\033[38;2;255;105;180m"
#define LIGHT_BLUE      "\033[38;2;100;200;255m"
#define LIME            "\033[38;2;180;255;100m"
#define TEAL            "\033[38;2;0;200;200m"
#define GOLD            "\033[38;2;255;215;0m"
#define SALMON          "\033[38;2;255;140;120m"
#define SKY             "\033[38;2;135;206;235m"
#define MINT            "\033[38;2;170;255;195m"
#define LAVENDER        "\033[38;2;200;160;255m"
#define PEACH           "\033[38;2;255;180;120m"
#define NEON_GREEN      "\033[38;2;57;255;20m"
#define NEON_BLUE       "\033[38;2;77;77;255m"
#define NEON_PINK       "\033[38;2;255;20;147m"
#define NEON_CYAN       "\033[38;2;0;255;200m"
#define NEON_ORANGE     "\033[38;2;255;140;0m"
#define SOFT_RED        "\033[38;2;224;108;117m"
#define SOFT_GREEN      "\033[38;2;152;195;121m"
#define SOFT_YELLOW     "\033[38;2;229;192;123m"
#define SOFT_BLUE       "\033[38;2;97;175;239m"
#define SOFT_PURPLE     "\033[38;2;198;120;221m"
#define SOFT_CYAN       "\033[38;2;86;182;194m"
#define PASTEL_PINK     "\033[38;2;255;179;186m"
#define PASTEL_GREEN    "\033[38;2;186;255;201m"
#define PASTEL_BLUE     "\033[38;2;186;225;255m"
#define PASTEL_PURPLE   "\033[38;2;216;191;255m"
#define PASTEL_YELLOW   "\033[38;2;255;255;186m"
#define BLOOD_RED       "\033[38;2;180;0;0m"
#define FIRE_ORANGE     "\033[38;2;255;69;0m"
#define DEEP_BLUE       "\033[38;2;0;0;139m"
#define DARK_GREEN      "\033[38;2;0;100;0m"
#define GOLDEN          "\033[38;2;255;180;0m"
#define DARK_BLUE       "\033[38;2;10;25;80m"
#define DARK_RED        "\033[38;2;120;0;0m"
#define DARK_PURPLE     "\033[38;2;60;0;90m"
#define DARK_CYAN       "\033[38;2;0;100;100m"
#define DARK_GRAY       "\033[38;2;80;80;80m"
#define AQUA            "\033[38;2;0;255;180m"
#define TURQUOISE       "\033[38;2;64;224;208m"
#define CORAL           "\033[38;2;255;127;80m"
#define ROSE            "\033[38;2;255;0;127m"
#define FUCHSIA         "\033[38;2;255;0;255m"
#define ELECTRIC_BLUE   "\033[38;2;44;117;255m"
#define LASER_GREEN     "\033[38;2;0;255;100m"
#define HOT_PINK        "\033[38;2;255;20;180m"
#define CYBER_YELLOW    "\033[38;2;255;255;0m"
#define MATRIX_GREEN    "\033[38;2;0;255;70m"
#define SAND            "\033[38;2;244;164;96m"
#define OLIVE           "\033[38;2;128;128;0m"
#define FOREST_GREEN    "\033[38;2;34;139;34m"
#define SEA_BLUE        "\033[38;2;70;130;180m"
#define SUNSET          "\033[38;2;255;94;77m"

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

const string giatrilabai[13] = {
    "A","2","3","4","5","6","7",
    "8","9","10","J","Q","K"
};

const string Kyhieulabai[4] = {
    RED "♥" RESET,   // Cơ
    RED "♦" RESET,   // Rô
    WHITE "♣" RESET,  // Chuồn
    WHITE "♠" RESET, // Bích
};