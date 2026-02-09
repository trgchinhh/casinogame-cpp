#include "..//lib//header.h"

struct Labaixidach {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

void inlabai_xidach_oss(const Labaixidach& b) {
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

vector<Labaixidach> taobobai52la_xidach() {
    vector<Labaixidach> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobaixidach(vector<Labaixidach>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labaixidach rutbaixidach(vector<Labaixidach>& bobai) {
    Labaixidach b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbaixidach(const Labaixidach& b) {
    string ten;
    if (b.giatribai == 1) ten = "A";
    else if (b.giatribai == 11) ten = "J";
    else if (b.giatribai == 12) ten = "Q";
    else if (b.giatribai == 13) ten = "K";
    else ten = to_string(b.giatribai);
    return ten;
}

int tinhdiemxidach(const vector<Labaixidach>& bai) {
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
int ruthaydung(int& chon, int& nguoi_solanrut){
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
    } while(!nhaphople && solansai < 3);
    cout << endl;
    if(solansai == 3) return 2;
    return 1;
}

void game_xidach(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
    if (!kiemtrasodutaikhoan(nguoichoi)) {
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    int tiencuoc = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if (!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;        
    } 
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerxidach);
    cout << "\n" << RED << "[GAME] " << RESET << "XÌ DÁCH\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai
         << YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    cout << endl;
    // Khởi tạo bộ bài 52 lá 
    vector<Labaixidach> bobai = taobobai52la_xidach();
    // xào bài 
    xaobaixidach(bobai);
    // Tạo mảng lưu bài người và bot (khi rút)
    vector<Labaixidach> bainguoi, baibot;
    // chia 2 lá đầu
    bainguoi.push_back(rutbaixidach(bobai));
    bainguoi.push_back(rutbaixidach(bobai));
    baibot.push_back(rutbaixidach(bobai));
    baibot.push_back(rutbaixidach(bobai));
    int nguoi_solanrut = 0;
    // Số lá đã in (không in lá cũ)
    int soladain = 0;
    while (true) {
        int diem = tinhdiemxidach(bainguoi);
        cout << "\t[" << GREEN << "Bài bạn" << RESET << "]: ";
        cout << endl;
        for (int i = soladain; i < bainguoi.size(); i++){
            //cout << "[" << RED << tenbaixidach(b) << RESET << "] ";
            inlabai_xidach_oss(bainguoi[i]);
        }
        soladain = bainguoi.size();
        cout << RED << "\t\t--> " << RESET << "Điểm hiện tại: " << YELLOW << diem << RESET << " điểm";
        cout << endl;
        if (diem > 21) break;
        int chon; ruthaydung(chon, nguoi_solanrut);
        cin.ignore();
        if (chon == 1 && !bobai.empty()) bainguoi.push_back(rutbaixidach(bobai));
        else break;
    }
    while (tinhdiemxidach(baibot) < 17 && !bobai.empty()) {
        baibot.push_back(rutbaixidach(bobai));
    }
    int diemnguoi = tinhdiemxidach(bainguoi);
    int diembot   = tinhdiemxidach(baibot);
    cout << "\t[" << BLUE << "Bài bot" << RESET << "]: ";
    cout << endl;
    for (auto& b : baibot)
        //cout << "[" << RED << tenbaixidach(b) << RESET << "] ";
        inlabai_xidach_oss(b);
    cout << RED << "\t\t--> " << RESET << "Điểm bot: " << diembot << " điểm";
    cout << endl;

    string ketqua;
    if (diemnguoi > 21 && diembot > 21) ketqua = "Hòa";
    else if (diemnguoi > 21) ketqua = "Thua";
    else if (diembot > 21) ketqua = "Thắng";
    else if (diemnguoi > diembot) ketqua = "Thắng";
    else if (diemnguoi < diembot) ketqua = "Thua";
    else ketqua = "Hòa";
    cout << endl;
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "]" << endl;
    if (ketqua == "Hòa") {
        nguoichoi->sodu += tiencuoc;
        cout << "\tTrả lại tiền: " << YELLOW << "~" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else if (ketqua == "Thắng") {
        int tienthang = tiencuoc * 2;
        nguoichoi->sodu += tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng bot" << RESET
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien    = phienhientai;
    lichsu.trochoi  = "XiDach";
    lichsu.sodu     = nguoichoi->sodu;
    lichsu.tiencuoc = tiencuoc;
    lichsu.luachon  = "Rut " + to_string(nguoi_solanrut) + " lan";
    lichsu.tongdiem = diemnguoi;
    lichsu.ketqua   = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}
