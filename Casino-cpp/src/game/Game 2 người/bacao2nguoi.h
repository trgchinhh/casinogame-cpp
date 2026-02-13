#include "..//..//lib//header.h"

struct Labaibacao2nguoi {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

// Phân loại bài
enum Loaibai2nguoi {
    Bu2nguoi, Nut2nguoi, Bacao2nguoi
};

bool kiemtrabacao2nguoi(const vector<Labaibacao2nguoi>& bai){
    if(bai.size() != 3) return false;
    for(auto& b : bai){
        if(b.giatribai < 11) return false;
    }
    return true;
}

Loaibai2nguoi loaibai2nguoi(const vector<Labaibacao2nguoi>& bai) {
    if (kiemtrabacao2nguoi(bai)) return Bacao2nguoi;
    int diem = 0;
    for (auto& b : bai) {
        if (b.giatribai == 1) diem += 1;
        else if (b.giatribai >= 10) diem += 0;
        else diem += b.giatribai;
    }
    diem %= 10;
    if (diem == 0) return Bu2nguoi;
    return Nut2nguoi;
}

void inlabai_bacao_oss_2nguoi(const Labaibacao2nguoi& b, const int diemtungla) {
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
vector<Labaibacao2nguoi> taobobai52la_bacao_2nguoi() {
    vector<Labaibacao2nguoi> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobaibacao2nguoi(vector<Labaibacao2nguoi>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labaibacao2nguoi rutbaibacao2nguoi(vector<Labaibacao2nguoi>& bobai) {
    Labaibacao2nguoi b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbaibacao2nguoi(const Labaibacao2nguoi& b) {
    string ten;
    if (b.giatribai == 1) ten = "A";
    else if (b.giatribai == 11) ten = "J";
    else if (b.giatribai == 12) ten = "Q";
    else if (b.giatribai == 13) ten = "K";
    else ten = to_string(b.giatribai);
    return ten;
}

void game_bacao2nguoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
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
    inbanner(bannerbacao);
    cout << "\n" << RED << "[GAME] " << RESET << "BA CÀO 2 NGƯỜI\n\n";
    
    // Khởi tạo bài và xào bài
    vector<Labaibacao2nguoi> bobai = taobobai52la_bacao_2nguoi();
    xaobaibacao2nguoi(bobai);
    vector<Labaibacao2nguoi> bainguoi1, bainguoi2;
    // Phát mỗi người 3 lá
    for (int i = 0; i < 3; i++) {
        bainguoi1.push_back(rutbaibacao2nguoi(bobai));
        bainguoi2.push_back(rutbaibacao2nguoi(bobai));
    }
    auto tinhdiembaicao = [](vector<Labaibacao2nguoi>& bai) {
        int tong = 0;
        for (auto& b : bai) {
            if (b.giatribai == 1) tong += 1;
            else if (b.giatribai >= 10) tong += 0;
            else tong += b.giatribai;
        }
        return tong % 10;
    };
    int diemnguoi1 = tinhdiembaicao(bainguoi1);
    int diemnguoi2 = tinhdiembaicao(bainguoi2);
    
    // Mở bài người chơi
    cout << "\t>> Nhấn phím bất kỳ để nặn bài !" << endl << endl;
    
    // Lượt người chơi 1 
    cout << "\t>> Lượt " << YELLOW << nguoichoi->tentaikhoan << RESET << endl;
    cout << "\t[" << GREEN << "Bài " << nguoichoi->tentaikhoan << RESET << "]: ";
    cout << "[\\] [\\] [\\] (Đang che)" << endl;
    _getch();
    for (int i = 0; i < 3; i++) {
        if(i < 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else if(i == 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": "; 
        int diemtungla = 0;
        if (bainguoi1[i].giatribai == 1) diemtungla = 1;
        else if (bainguoi1[i].giatribai >= 10) diemtungla = 0;
        else diemtungla = bainguoi1[i].giatribai;
        cout << endl;
        inlabai_bacao_oss_2nguoi(bainguoi1[i], diemtungla);
        cout << endl;
        if(i < 2) _getch();
    }
    cout << endl;
    if(diemnguoi1 == 0){
        if(kiemtrabacao2nguoi(bainguoi1)) cout << "\tTổng số nút của bạn: " << YELLOW << "3 Cào" << RESET << endl;
        else cout << "\tTổng số nút của bạn: " << YELLOW << "Bù" << RESET << endl;
    }
    else cout << "\tTổng số nút của bạn: " << YELLOW << diemnguoi1 << RESET << " nút" << endl;
    cout << endl;

    // Lượt người chơi 2 
    cout << "\t>> Lượt " << YELLOW << tennguoichoi2 << RESET << endl;
    cout << "\t[" << GREEN << "Bài " << tennguoichoi2 << RESET << "]: ";
    cout << "[\\] [\\] [\\] (Đang che)" << endl;
    _getch();
    for (int i = 0; i < 3; i++) {
        if(i < 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else if(i == 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": "; 
        int diemtungla = 0;
        if (bainguoi2[i].giatribai == 1) diemtungla = 1;
        else if (bainguoi2[i].giatribai >= 10) diemtungla = 0;
        else diemtungla = bainguoi2[i].giatribai;
        cout << endl;
        inlabai_bacao_oss_2nguoi(bainguoi2[i], diemtungla);
        cout << endl;
        if(i < 2) _getch();
    }
    cout << endl;
    if(diemnguoi2 == 0){
        if(kiemtrabacao2nguoi(bainguoi2)) cout << "\tTổng số nút của bạn: " << YELLOW << "3 Cào" << RESET << endl;
        else cout << "\tTổng số nút của bạn: " << YELLOW << "Bù" << RESET << endl;
    }
    else cout << "\tTổng số nút của bạn: " << YELLOW << diemnguoi2 << RESET << " nút" << endl;
    cout << endl;

    Loaibai2nguoi loaibainguoi1 = loaibai2nguoi(bainguoi1); 
    Loaibai2nguoi loaibainguoi2 = loaibai2nguoi(bainguoi2);

    string ketqua;
    if (loaibainguoi1 == Bacao2nguoi && loaibainguoi2 != Bacao2nguoi) ketqua = "Thắng";
    else if (loaibainguoi1 != Bacao2nguoi && loaibainguoi2 == Bacao2nguoi) ketqua = "Thua";
    else if (loaibainguoi1 == Bacao2nguoi && loaibainguoi2 == Bacao2nguoi) ketqua = "Hòa";
    else {
        if (diemnguoi1 > diemnguoi2) ketqua = "Thắng";
        else if (diemnguoi1 < diemnguoi2) ketqua = "Thua";
        else ketqua = "Hòa";
    }

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