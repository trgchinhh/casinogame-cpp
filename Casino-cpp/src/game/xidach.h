#include "..//lib//header.h"

int rutbaixidach() {
    return rand() % 13 + 1;
}

int tinhdiemxidach(const vector<int>& bai) {
    int tong = 0;
    for (int b : bai) {
        if (b == 1)           tong += 1;    // Ách
        else if (b >= 11)     tong += 10;   // J Q K
        else                  tong += b;    // 2-10
    }
    return tong;
}

string tenbaixidach(int b) {
    if (b == 1)  return "A";
    if (b == 11) return "J";
    if (b == 12) return "Q";
    if (b == 13) return "K";
    return to_string(b);
}

// tiếp tục hay dừng (dằn dơ)
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
    if (!nhaptiencuoc(tiencuoc, nguoichoi)) return;
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerxidach);
    cout << "\n" << RED << "[GAME] " << RESET << "XÌ DÁCH\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai
         << YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND\n\n";
    vector<int> bainguoi, baibot;
    // Chia 2 lá đầu
    bainguoi.push_back(rutbaixidach());
    bainguoi.push_back(rutbaixidach());
    baibot.push_back(rutbaixidach());
    baibot.push_back(rutbaixidach());
    int nguoi_solanrut = 0;
    while (true) {
        int diem = tinhdiemxidach(bainguoi);
        cout << "\t[" << GREEN << "Bài bạn" << RESET "]: ";
        for (int b : bainguoi)
            cout << "[" << RED << tenbaixidach(b) << RESET << "] ";
        cout << " --> " << diem << " điểm";
        cout << endl;
        if (diem > 21) break;
        int chon; ruthaydung(chon, nguoi_solanrut);
        cin.ignore();
        if (chon == 1) bainguoi.push_back(rutbaixidach());
        else break;
    }
    while (tinhdiemxidach(baibot) < 17) {
        baibot.push_back(rutbaixidach());
    }
    int diemnguoi = tinhdiemxidach(bainguoi);
    int diembot   = tinhdiemxidach(baibot);
    cout << "\t[" << BLUE << "Bài bot" << RESET "]: ";
    for (int b : baibot)
        cout << "[" << RED << tenbaixidach(b) << RESET << "] ";
    cout << " --> " << diembot << " điểm";
    cout << endl;

    string ketqua;
    if(diemnguoi > 21 && diembot > 21) ketqua = "Hòa";
    else if (diemnguoi > 21) ketqua = "Thua";
    else if (diembot > 21) ketqua = "Thắng";
    else if (diemnguoi > diembot) ketqua = "Thắng";
    else if (diemnguoi < diembot) ketqua = "Thua";
    else ketqua = "Hòa";
    cout << endl;
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "]" << endl;
    if (ketqua == "Hòa") {
        nguoichoi->sodu += tiencuoc;
        cout << "\tTrả lại tiền: " << YELLOW << "~" <<dinhdangtien(tiencuoc) << RESET << " VND" << endl;
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
