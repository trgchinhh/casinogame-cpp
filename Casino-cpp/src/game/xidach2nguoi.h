#include "..//lib//header.h"

struct Labaixidach2nguoi {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

void inlabai_xidach_oss_2nguoi(const Labaixidach2nguoi& b) {
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
    cout << endl;
}

vector<Labaixidach2nguoi> taobobai52la_xidach_2nguoi() {
    vector<Labaixidach2nguoi> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobaixidach2nguoi(vector<Labaixidach2nguoi>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labaixidach2nguoi rutbaixidach2nguoi(vector<Labaixidach2nguoi>& bobai) {
    Labaixidach2nguoi b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbaixidach2nguoi(const Labaixidach2nguoi& b) {
    string ten;
    if (b.giatribai == 1) ten = "A";
    else if (b.giatribai == 11) ten = "J";
    else if (b.giatribai == 12) ten = "Q";
    else if (b.giatribai == 13) ten = "K";
    else ten = to_string(b.giatribai);
    return ten;
}

int tinhdiemxidach2nguoi(const vector<Labaixidach2nguoi>& bai) {
    int tong = 0;
    // tính điểm cho A luôn bằng 1 
    // J Q K thì bằng 10 
    for (auto& b : bai) {
        if (b.giatribai == 1) tong += 1;
        else if (b.giatribai >= 11) tong += 10;
        else tong += b.giatribai;
    }
    return tong;
}

// tiếp tục hay dừng (dằn ngay 16 là dằn dơ :)
int ruthaydung2nguoi(int& chon, int& nguoi_solanrut){
    int solansai = 0; bool nhaphople = false;
    do {
        cout << "\t\t(?) [1] Rút bài - [2] Dừng: "; cin >> chon;
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập lựa chọn hợp lệ !" << RESET << endl;
            solansai++;
            continue;
        } else if(chon != 1 && chon != 2){
            cout << YELLOW << "\t\t(!) Vui lòng nhập 1 hoặc 2 !" << RESET << endl;
            solansai++;
            continue;  
        } else { 
            nhaphople = true;
            nguoi_solanrut += 1;
        }
    } while(!nhaphople && solansai < solansaitoida);
    cout << endl;
    if(solansai == solansaitoida) return 2;
    return 1;
}

void game_xidach2nguoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
    if (!kiemtrasodutaikhoan(nguoichoi)) {
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
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
    inbanner(bannerxidach);
    cout << "\n" << RED << "[GAME] " << RESET << "XÌ DÁCH 2 NGƯỜI\n\n";
    
    // Khởi tạo bộ bài 52 lá 
    vector<Labaixidach2nguoi> bobai = taobobai52la_xidach_2nguoi();
    // xào bài 
    xaobaixidach2nguoi(bobai);
    // Tạo mảng lưu bài người và bot (khi rút)
    vector<Labaixidach2nguoi> bainguoi1, bainguoi2;
    // chia 2 lá đầu
    bainguoi1.push_back(rutbaixidach2nguoi(bobai));
    bainguoi1.push_back(rutbaixidach2nguoi(bobai));
    bainguoi2.push_back(rutbaixidach2nguoi(bobai));
    bainguoi2.push_back(rutbaixidach2nguoi(bobai));
    int nguoi_solanrut = 0;
    // Số lá đã in (không in lá cũ)
    int soladainnguoi1 = 0, soladainnguoi2 = 0;

    // người 1 rút  
    while (true) {
        int diem = tinhdiemxidach2nguoi(bainguoi1);
        cout << "\t[" << GREEN << "Bài " << nguoichoi->tentaikhoan << RESET << "]: ";
        cout << endl;
        for (int i = soladainnguoi1; i < bainguoi1.size(); i++){
            inlabai_xidach_oss_2nguoi(bainguoi1[i]);
        }
        soladainnguoi1 = bainguoi1.size();
        cout << RED << "\t\t--> " << RESET << "Điểm hiện tại: " << YELLOW << diem << RESET << " điểm";
        cout << endl;
        if (diem > 21) break;
        int chon; ruthaydung2nguoi(chon, nguoi_solanrut);
        cin.ignore();
        if (chon == 1 && !bobai.empty()) bainguoi1.push_back(rutbaixidach2nguoi(bobai));
        else break;
    }
    
    // người 2 rút
    while (true) {
        int diem = tinhdiemxidach2nguoi(bainguoi2);
        cout << "\t[" << GREEN << "Bài " << tennguoichoi2 << RESET << "]: ";
        cout << endl;
        for (int i = soladainnguoi2; i < bainguoi2.size(); i++){
            inlabai_xidach_oss_2nguoi(bainguoi2[i]);
        }
        soladainnguoi2 = bainguoi2.size();
        cout << RED << "\t\t--> " << RESET << "Điểm hiện tại: " << YELLOW << diem << RESET << " điểm";
        cout << endl;
        if (diem > 21) break;
        int chon; ruthaydung2nguoi(chon, nguoi_solanrut);
        cin.ignore();
        if (chon == 1 && !bobai.empty()) bainguoi2.push_back(rutbaixidach2nguoi(bobai));
        else break;
    }

    int diemnguoi1 = tinhdiemxidach2nguoi(bainguoi1);
    int diemnguoi2 = tinhdiemxidach2nguoi(bainguoi2);

    string ketqua;
    if (diemnguoi1 > 21 && diemnguoi2 > 21) ketqua = "Hòa";
    else if (diemnguoi1 > 21) ketqua = "Thua";
    else if (diemnguoi2 > 21) ketqua = "Thắng";
    else if (diemnguoi1 > diemnguoi2) ketqua = "Thắng";
    else if (diemnguoi1 < diemnguoi2) ketqua = "Thua";
    else ketqua = "Hòa";
    cout << endl;
    cout << YELLOW << "\tKết quả: " << RESET;
    if(ketqua == "Thắng"){
        cout << YELLOW << nguoichoi->tentaikhoan << RESET << " thắng " << endl;
    } else if(ketqua == "Thua"){
        cout << YELLOW << tennguoichoi2 << RESET << " thắng " << endl;
    } else {
        cout << YELLOW << "Cả 2 cùng hòa " << RESET << endl;
    }
}
