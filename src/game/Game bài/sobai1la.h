#include "..//..//lib//header.h"

struct Labai1la {
    int giatribai;   // 1-13 (ách đến già) A -> K
    int kyhieubai;   // 0-3  (4 ký hiệu cơ/rô/chuồng/bích)
};

void inlabai_1la_oss(const Labai1la& b, const int diemtungla) {
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
vector<Labai1la> taobobai52la_1la() {
    vector<Labai1la> bobai;
    for (int c = 0; c < 4; c++) {
        for (int g = 1; g <= 13; g++) {
            bobai.push_back({g, c}); 
        }
    }
    return bobai;
}

void xaobai1la(vector<Labai1la>& bobai) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(bobai.begin(), bobai.end(), gen);
}

Labai1la rutbai1la(vector<Labai1la>& bobai) {
    Labai1la b = bobai.back();
    bobai.pop_back();
    return b;
}

string tenbai1la(const Labai1la& b) {
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

void game_sobai1la(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
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
    clear();
    inbanner(bannersobai);
    cout << "\n" << RED << "[GAME] " << RESET << "SO BÀI 1 LÁ\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai
         << YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    cout << endl;
    // Khởi tạo bài và xào bài
    vector<Labai1la> bobai = taobobai52la_1la();
    xaobai1la(bobai);
    vector<Labai1la> bainguoichoi, baibot;
    // Phát mỗi người 1 lá
    bainguoichoi.push_back(rutbai1la(bobai));
    baibot.push_back(rutbai1la(bobai));

    int diemnguoichoi = bainguoichoi[0].giatribai;
    int diembot = baibot[0].giatribai;
        
    // Lượt bot lật
    cout << "\t[" << BLUE << "Bài bot" << RESET << "]: " << endl;
    inlabai_1la_oss(baibot[0], diembot);
    cout << endl;
    cout << "\t" << BLUE << "Bot" << RESET 
         << " ra: " << YELLOW << diembot << RESET << " nút " 
         << hienthiten(diembot) << endl; 
    cout << endl;

    // Mở bài người chơi
    cout << "\t>> Nhấn phím bất kỳ để lật bài !" << endl << endl;

    // Lượt người chơi lật
    cout << "\t[" << GREEN << "Bài bạn" << RESET << "]: ";
    cout << "[\\] (Đang che)" << endl;
    getchar();
    inlabai_1la_oss(bainguoichoi[0], diemnguoichoi);
    cout << endl;
    cout << "\t" << GREEN << nguoichoi->tentaikhoan << RESET 
         << " ra: " << YELLOW << diemnguoichoi << RESET << " nút "
         << hienthiten(diemnguoichoi) << endl; 
    cout << endl;

    string ketqua;
    if (diemnguoichoi > diembot) ketqua = "Thắng";
    else if (diemnguoichoi < diembot) ketqua = "Thua";
    else ketqua = "Hòa";

    cout << YELLOW << "\tKết quả: " << RESET;
    int tienthang = 0;
    if(ketqua == "Thắng"){
        tienthang = tiencuoc * 2;
        nguoichoi->sodu += tienthang;
        cout << YELLOW << nguoichoi->tentaikhoan << RESET << " thắng " 
             << "(" << diemnguoichoi << " > " << diembot << ")" << endl;
        cout << GREEN << "\tChúc mừng bạn đã thắng bot" << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else if(ketqua == "Hòa") {
        nguoichoi->sodu += tiencuoc;
        cout << YELLOW << "Cả 2 cùng hòa " << RESET 
             << "(" << diemnguoichoi << " = " << diembot << ")" << endl;
        cout << "\tTrả lại tiền: " << YELLOW << "~" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << YELLOW << "Bot" << RESET << " thắng "
             << "(" << diembot << " > " << diemnguoichoi << ")" << endl;
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }

    nguoichoi->sotiendachoi += tiencuoc;
    nguoichoi->sotienthang  += tienthang;
    LichSu lichsu;
    lichsu.phien = phienhientai;
    lichsu.trochoi = "SoBai";
    lichsu.sodu = nguoichoi->sodu;
    lichsu.tiencuoc = tiencuoc;
    lichsu.luachon = "Lat bai 1 la";
    lichsu.tongdiem = diemnguoichoi;
    lichsu.ketqua = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}
