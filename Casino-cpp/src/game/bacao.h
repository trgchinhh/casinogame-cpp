#include "..//lib//header.h"

struct Labaibacao {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

// Phân loại bài
enum Loaibai {
    Bu, Nut, Bacao
};

bool kiemtrabacao(const vector<Labaibacao>& bai){
    if(bai.size() != 3) return false;
    for(auto& b : bai){
        if(b.giatribai < 11) return false;
    }
    return true;
}

Loaibai loaibai(const vector<Labaibacao>& bai) {
    if (kiemtrabacao(bai)) return Bacao;
    int diem = 0;
    for (auto& b : bai) {
        if (b.giatribai == 1) diem += 1;
        else if (b.giatribai >= 10) diem += 0;
        else diem += b.giatribai;
    }
    diem %= 10;
    if (diem == 0) return Bu;
    return Nut;
}

void inlabai_bacao_oss(const Labaibacao& b, const int diemtungla) {
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
vector<Labaibacao> taobobai52la_bacao() {
    vector<Labaibacao> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobaibacao(vector<Labaibacao>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labaibacao rutbaibacao(vector<Labaibacao>& bobai) {
    Labaibacao b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbaibacao(const Labaibacao& b) {
    string ten;
    if (b.giatribai == 1) ten = "A";
    else if (b.giatribai == 11) ten = "J";
    else if (b.giatribai == 12) ten = "Q";
    else if (b.giatribai == 13) ten = "K";
    else ten = to_string(b.giatribai);
    return ten;
}

void game_bacao(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
    if (!kiemtrasodutaikhoan(nguoichoi)) {
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ !" << RESET << endl;
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
    inbanner(bannerbacao);
    cout << "\n" << RED << "[GAME] " << RESET << "BA CÀO\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai
         << YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    cout << endl;
    // Khởi tạo bài và xào bài
    vector<Labaibacao> bobai = taobobai52la_bacao();
    xaobaibacao(bobai);
    vector<Labaibacao> baibot, bainguoi;
    // Phát mỗi người 3 lá
    for (int i = 0; i < 3; i++) {
        baibot.push_back(rutbaibacao(bobai));
        bainguoi.push_back(rutbaibacao(bobai));
    }
    auto tinhdiembaicao = [](vector<Labaibacao>& bai) {
        int tong = 0;
        for (auto& b : bai) {
            if (b.giatribai == 1) tong += 1;
            else if (b.giatribai >= 10) tong += 0;
            else tong += b.giatribai;
        }
        return tong % 10;
    };
    int diembot = tinhdiembaicao(baibot);
    int diemnguoi = tinhdiembaicao(bainguoi);
    
    // In bài bot 
    cout << "\t[" << BLUE << "Bài bot" << RESET << "]: ";
    for (auto& b : baibot)
        cout << "[" << RED << tenbaibacao(b) << RESET << "] ";
    if(diembot == 0){
        if(kiemtrabacao(baibot)) 
            cout << " -->" << YELLOW << " Ba cào" << RESET << endl; 
        else cout << " -->" << YELLOW << " Bù" << RESET << endl;
    }
    else cout << " --> " << YELLOW << diembot << RESET << " nút" << endl;
    cout << endl;

    // Mở bài người chơi
    cout << "\t>> Nhấn phím bất kỳ để nặn bài !" << endl;
    cout << "\t[" << GREEN << "Bài bạn" << RESET << "]: ";
    cout << "[\\] [\\] [\\] (Đang che)" << endl;
    //cout << "\t    │" << endl;

    _getch();
    for (int i = 0; i < 3; i++) {
        //if(i < 2) cout << "\t├─ [" << GREEN << "Bài bạn" << RESET << "]: ";
        //else cout << "\t└─ [" << GREEN << "Bài bạn" << RESET << "]: ";
        if(i < 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else if(i == 1) cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": ";
        else cout << RED << "\t   -" << RESET << " Mở lá " << i + 1 << ": "; 

        int diemtungla = 0;
        //for (int j = 0; j <= i; j++){
        // in số nút của lá hiện tại (lá đang mở)
        if (bainguoi[i].giatribai == 1) diemtungla = 1;
        else if (bainguoi[i].giatribai >= 10) diemtungla = 0;
        else diemtungla = bainguoi[i].giatribai;
        cout << endl;
        inlabai_bacao_oss(bainguoi[i], diemtungla);
        cout << endl;
        //cout << "[" << RED << tenbaibacao(bainguoi[j]) << RESET << "] ";
        
        // in tổng nút những lá đã mở 
        // if (bainguoi[j].giatribai == 1) diemtungla += 1;
        // else if (bainguoi[j].giatribai >= 10) diemtungla += 0;
        // else diemtungla += bainguoi[j].giatribai;
    
        //}
        //for (int j = i + 1; j < 3; j++)
            //cout << "[-] ";
        if(i < 2) _getch();
    }
    cout << endl;
    if(diemnguoi == 0){
        if(kiemtrabacao(bainguoi)) cout << "\tTổng số nút của bạn: " << YELLOW << "3 Cào" << RESET << endl;
        else cout << "\tTổng số nút của bạn: " << YELLOW << "Bù" << RESET << endl;
    }
    else cout << "\tTổng số nút của bạn: " << YELLOW << diemnguoi << RESET << " nút" << endl;
    cout << endl;

    Loaibai loaibainguoi = loaibai(bainguoi);
    Loaibai loaibaibot = loaibai(baibot); 

    string ketqua;
    
    if (loaibainguoi == Bacao && loaibaibot != Bacao) ketqua = "Thắng";
    else if (loaibainguoi != Bacao && loaibaibot == Bacao) ketqua = "Thua";
    else if (loaibainguoi == Bacao && loaibaibot == Bacao) ketqua = "Hòa";
    else {
        if (diemnguoi > diembot) ketqua = "Thắng";
        else if (diemnguoi < diembot) ketqua = "Thua";
        else ketqua = "Hòa";
    }

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
    }
    LichSu lichsu;
    lichsu.phien = phienhientai;
    lichsu.trochoi = "BaCao";
    lichsu.sodu = nguoichoi->sodu;
    lichsu.tiencuoc = tiencuoc;
    lichsu.luachon = "Lat bai tung la";
    lichsu.tongdiem = diemnguoi;
    lichsu.ketqua = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}