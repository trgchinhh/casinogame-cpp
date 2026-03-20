#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "..//lib//props.h"
using namespace std; 

char __getch() {
    #ifdef _WIN32
        return _getch();
    #else
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); 
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    #endif
}

bool tranghuongdan(const string& noidung, int kichthuoctrang = 20) {
    vector<string> cacdong;
    string dong;
    stringstream ss(noidung);
    while (getline(ss, dong)) {
        cacdong.push_back(dong);
    }
    int tongdong = cacdong.size();
    int tongtrang = (tongdong + kichthuoctrang - 1) / kichthuoctrang;
    for (int i = 0; i < tongdong; i++) {
        cout << cacdong[i] << endl;
        if ((i + 1) % kichthuoctrang == 0 && i + 1 < tongdong) {
            int tranghientai = (i + 1) / kichthuoctrang;
            cout << endl << flush;
            cout << RESET 
                 << "[Enter: tiếp | q: thoát]  --"
                 << tranghientai << "/" << tongtrang << "--"
                 << RESET << flush;
            char c = __getch();
            if (c == 'q' || c == 'Q')
                return false;
            cout << "\r";        // về đầu dòng
            cout << "\033[2K";   // xóa dòng
            cout << "\033[1A";   // lên 1 dòng
            cout << "\033[2K";   // xóa dòng trên
            cout << "\r";
        }
    }
    return true;
}

const string noidunghuongdan =
"\n"

CYAN ICON_USER "** TẠO TÀI KHOẢN **\n" RESET
"\t• Tạo tên người dùng (Tên này có thể là nickname)\n"
"\t• Tạo tên đăng nhập (ghi nhớ)\n"
"\t• Tạo mật khẩu (ghi nhớ)\n"
"\t• Tạo mã 6 số (buộc nhớ nếu muốn đổi mật khẩu)\n"
"\t• Tạo số dư (tối đa 100.000.000)\n\n"

CYAN ICON_USER "** CÀI ĐẶT **\n" RESET
"\t• Thông tin game (bản quyền)\n"
"\t• Hiệu ứng âm thanh\n"
"\t• AI gợi ý kết quả\n\n"

CYAN ICON_HGAME "** CÁC THỂ LOẠI GAME **\n" RESET
"\t• Xóc xóc: tài xỉu, xóc dĩa, úp ngửa xu, lắc bầu cua\n"
"\t• Game bài: ba cào, xì dách, so bài\n"
"\t• May rủi: dài ngắn, 3/7 màu, đoán số A->B, đoán chẵn lẻ, kéo búa bao\n\n"

CYAN ICON_DICE "** TÀI XỈU 1xx / 3xx **\n" RESET
"\t• Nhập lựa chọn Tài hoặc Xỉu và nhập tiền cược\n"
"\t• Chờ 5 giây sẽ có kết quả\n"
"\t• Tài xỉu 1xx: 1 → 3 (Xỉu), 4 → 6 (Tài)\n"
"\t• Tài xỉu 3xx: 3 → 10 (Xỉu), 11 → 18 (Tài)\n\n"

CYAN ICON_NUMBER "** ĐOÁN DÀI NGẮN **\n" RESET
"\t• Nhập lựa chọn Dài hoặc Ngắn và nhập tiền cược\n"
"\t• Có hiệu ứng chạy số\n"
"\t• Trên 30 là Dài, dưới hoặc bằng 30 là Ngắn\n\n"

CYAN ICON_COLOR "** ĐOÁN 3 / 7 MÀU **\n" RESET
"\t• Chọn màu bạn tin là sẽ ra (2 màu) và nhập tiền cược\n"
"\t• Hệ thống random màu (2/7 màu)\n"
"\t• Trúng 1/2 màu là ăn tiền\n\n"

CYAN ICON_NUMBER "** ĐOÁN SỐ A → B **\n" RESET
"\t• Nhập khoảng số A đến B và nhập tiền cược\n"
"\t• Đoán số trong khoảng đó\n"
"\t• Trúng số random thì thắng\n\n"

CYAN ICON_NUMBER "** CHẴN LẺ 0 → 9 **\n" RESET
"\t• Nhập lựa chọn Chẵn hoặc Lẻ và nhập tiền cược\n"
"\t• Hệ thống random số từ 0 đến 9\n"
"\t• Trùng kết quả thì thắng\n\n"

CYAN ICON_COIN "** ÚP NGỬA XU **\n" RESET
"\t• Nhập kết quả Úp hoặc Ngửa và nhập tiền cược\n"
"\t• Tung đồng xu ngẫu nhiên\n"
"\t• Đúng thì thắng, sai thì thua\n\n"

CYAN ICON_CARD "** BA CÀO **\n" RESET
"\t• Nhập tiền cược đầu tiên\n"
"\t• Kết quả bot sẽ ra trước\n"
"\t• Bài 3 lá được phát (che), mình sẽ nặn từng lá\n"
"\t• Bên nào cao điểm hơn thì thắng\n\n"

CYAN ICON_CARD "** XÌ DÁCH **\n" RESET
"\t• Nhập tiền cược đầu tiên\n"
"\t• Rút sẵn 2 lá sau đó chọn rút tiếp hoặc dừng\n"
"\t• A = 1 điểm, J/Q/K = 10 điểm\n"
"\t• Tổng điểm gần hoặc bằng 21 hơn bot thì thắng\n"
"\t• Quá 21 là quắc\n\n"

CYAN ICON_DICE "** XÓC DĨA **\n" RESET
"\t• Chọn chẵn lẽ và nhập tiền cược\n"
"\t• Chờ lắc kết quả\n"
"\t• Gồm 4 quân vị (mỗi quân vị gồm 2 mặt đỏ và trắng)\n"
"\t• Nếu 2 trắng 2 đỏ hoặc 4 trắng hoặc 4 đỏ thì kết quả chẵn\n"
"\t• Còn lại là lẽ\n"
"\t• Đoán trúng kết quả thì ăn tiền\n\n"

CYAN ICON_DICE "** LẮC BẦU CUA **\n" RESET
"\t• Chọn linh vật muốn cược (Không giới hạn) \n"
"\t• Nhập tiền cược\n"
"\t• Lắc 3 xúc xắc\n"
"\t• Trùng bao nhiêu mặt thì ăn bấy nhiêu lần\n\n"

CYAN ICON_HAND "** KÉO BÚA BAO **\n" RESET
"\t• Chọn kéo / búa / bao và nhập tiền cược\n"
"\t• So kết quả với bot\n"
"\t• Thắng thì lụm tiền\n\n"

CYAN ICON_PERSON "** GAME 2 NGƯỜI **\n" RESET
"\t• Đầu tiên nhập tên người chơi thứ 2\n"
"\t• Tiếp theo đến lượt ai người đó nhấn bất kỳ phím để ra kết quả\n"
"\t• Những trò đó luật như trên\n"
"\t• Game 2 người chơi vui\n"
"\t• Không cần tiền cược và không lưu lịch sử game\n\n"

CYAN ICON_WARN "** LƯU Ý **\n" RESET
"\t[->] Thắng có thể x1.9 hoặc x2 tùy game\n"
"\t[->] Nạp tiền vào acc Admin:\n\t\tUser: admin - Pass: admin\n"
"\t[->] Có thể tạo tối đa 100 tài khoản\n"
"\t[->] Nên bật hiệu ứng âm thanh để chơi vui hơn\n"
"\t[->] Mỗi lượt AI gợi ý phí -5.000 (VND)\n"
"\t[->] Bật tắt AI trong cài đặt\n"
"\t[->] Tiền cược ít nhất cho phép: 5.000 (VND)\n";
