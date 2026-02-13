#include "..//..//lib//header.h"

struct Labai1la2nguoi {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

void inlabai_1la_oss_2nguoi(const Labai1la2nguoi& b, const int diemtungla) {
    ostringstream oss;
    string giatri = giatrilabai[b.giatribai - 1];
    string kyhieu = Kyhieulabai[b.kyhieubai];
    ingiuamanhinh("┌──────────┐\n", WHITE);
    if (giatri.length() == 1) ingiuamanhinh("│ " + giatri + "        │\n", WHITE);
    else ingiuamanhinh("│ " + giatri + "       │\n", WHITE);
    ingiuamanhinh("│          │\n", WHITE);
    ingiuamanhinh("│    " + kyhieu + "     │\n", WHITE); 
    //cout << "  --> " << YELLOW + to_string(diemtungla) << " nút\n"; 
    ingiuamanhinh("│          │\n", WHITE);
    if (giatri.length() == 1) ingiuamanhinh("│        " + giatri + " │\n", WHITE);
    else ingiuamanhinh("│       " + giatri + " │\n", WHITE);
    ingiuamanhinh("└──────────┘\n", WHITE);
    ingiuamanhinh(RED "-->" RESET " Lá hiện tại: " YELLOW + to_string(diemtungla) + RESET + " nút\n", WHITE);
}

// tạo bộ bài 52 lá với 13 lá và 4 loại khác nhau
vector<Labai1la2nguoi> taobobai52la_1la_2nguoi() {
    vector<Labai1la2nguoi> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobaibacao2nguoi(vector<Labai1la2nguoi>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labai1la2nguoi rutbai1la2nguoi(vector<Labai1la2nguoi>& bobai) {
    Labai1la2nguoi b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbai1la2nguoi(const Labai1la2nguoi& b) {
    string ten;
    if (b.giatribai == 1) ten = "A";
    else if (b.giatribai == 11) ten = "J";
    else if (b.giatribai == 12) ten = "Q";
    else if (b.giatribai == 13) ten = "K";
    else ten = to_string(b.giatribai);
    return ten;
}

string hienthiten(int diem){
    if(diem == 1) return "(Ách)";
    if(diem == 11) return "(Bồi)";
    if(diem == 12) return "(Đầm)";
    if(diem == 13) return "(Già)";
    return"";
}

void game_sobai1la2nguoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
    if (!kiemtrasodutaikhoan(nguoichoi)) {
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ !" << RESET << endl;
        return;
    }
    intennguoichoi1(nguoichoi);
    string tennguoichoi2; int solansaiten = 0; 
    bool hopletennguoichoi2 = false;
    do {
        cout << "\t(?) Nhập tên người chơi 2: ";
        getline(cin, tennguoichoi2);
        if(tennguoichoi2.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên người chơi !" << RESET << endl;
            solansaiten++;
            continue;
        } else if(tennguoichoi2 == nguoichoi->tentaikhoan 
               || tennguoichoi2 == nguoichoi->tennguoichoi){
            cout << YELLOW << "\t\t(!) Vui lòng đặt tên khác !" << RESET << endl;
            solansaiten++;
            continue;
        } else hopletennguoichoi2 = true;
    } while(!hopletennguoichoi2 && solansaiten < solansaitoida);
    if(solansaiten == solansaitoida){
        return;
    }
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    system("cls");
    inbanner(bannersobai);
    cout << "\n" << RED << "[GAME] " << RESET << "SO BÀI 1 LÁ\n\n";
    
    // Khởi tạo bài và xào bài
    vector<Labai1la2nguoi> bobai = taobobai52la_1la_2nguoi();
    xaobaibacao2nguoi(bobai);
    vector<Labai1la2nguoi> bainguoi1, bainguoi2;
    // Phát mỗi người 1 lá
    bainguoi1.push_back(rutbai1la2nguoi(bobai));
    bainguoi2.push_back(rutbai1la2nguoi(bobai));

    int diemnguoi1 = bainguoi1[0].giatribai;
    int diemnguoi2 = bainguoi2[0].giatribai;
    
    // Mở bài người chơi
    cout << "\t>> Nhấn phím bất kỳ để lật bài !" << endl << endl;
    
    // Lượt người chơi 1 
    cout << "\t>> Lượt " << YELLOW << nguoichoi->tentaikhoan << RESET << endl;
    cout << "\t[" << GREEN << "Bài " << nguoichoi->tentaikhoan << RESET << "]: ";
    cout << "[\\] (Đang che)" << endl;
    _getch();
    inlabai_1la_oss_2nguoi(bainguoi1[0], diemnguoi1);
    cout << endl;
    cout << "\t" << YELLOW << nguoichoi->tentaikhoan << RESET 
         << " ra: " << YELLOW << diemnguoi1 << RESET << " nút " 
         << hienthiten(diemnguoi1) << endl; 

    cout << endl;

    // Lượt người chơi 2 
    cout << "\t>> Lượt " << YELLOW << tennguoichoi2 << RESET << endl;
    cout << "\t[" << GREEN << "Bài " << tennguoichoi2 << RESET << "]: ";
    cout << "[\\] (Đang che)" << endl;
    _getch();
    inlabai_1la_oss_2nguoi(bainguoi2[0], diemnguoi2);
    cout << endl;
    cout << "\t" << YELLOW << tennguoichoi2 << RESET 
         << " ra: " << YELLOW << bainguoi2[0].giatribai << RESET << " nút "
         << hienthiten(diemnguoi2) << endl; 
    cout << endl;

    string ketqua;
    if (diemnguoi1 > diemnguoi2) ketqua = "Thắng";
    else if (diemnguoi1 < diemnguoi2) ketqua = "Thua";
    else ketqua = "Hòa";

    cout << YELLOW << "\tKết quả: " << RESET;
    if(ketqua == "Thắng"){
        cout << YELLOW << nguoichoi->tentaikhoan << RESET << " thắng " 
             << "(" << diemnguoi1 << " > " << diemnguoi2 << ")" << endl;
    } else if(ketqua == "Thua"){
        cout << YELLOW << tennguoichoi2 << RESET << " thắng "
             << "(" << diemnguoi2 << " > " << diemnguoi1 << ")" << endl;
    } else {
        cout << YELLOW << "Cả 2 cùng hòa " << RESET 
             << "(" << diemnguoi1 << " = " << diemnguoi2 << ")" << endl;
    }
}