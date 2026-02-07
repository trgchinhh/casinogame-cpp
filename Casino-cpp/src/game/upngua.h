#include "..//lib//header.h"

void game_upngua(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc = 0; int tongxucxac = 0; int solansai = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (u/n): "; 
        getline(cin, luachon);
        if(!(luachon == "u" || luachon == "up" || luachon == "n" || luachon == "ngua")){
            cout << YELLOW << "\t\t(!) Vui lòng nhập u/up hoặc n/ngua" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "u" || luachon == "up" || luachon == "n" || luachon == "ngua" || solansai == 3));
    if(solansai == 3) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannertungxu);
    cout << "\n" << RED << "[GAME] " << RESET << "ÚP NGỬA" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "u" || luachon == "up" ? "Úp" : "Ngửa") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    hieuungamthanh_mp3(dd_1dongxuroi, trangthaiamthanh); loadraketqua(5);
    int songaunhien = rand() % 2 + 1;
    cout << YELLOW << "\tMặt đồng xu: " << RESET << "[" << (songaunhien == 1 ? "Úp" : "Ngửa") << "]" << endl;
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matdongxu[songaunhien][i], ORANGE);
        cout << endl;
    }
    cout << endl;
    string ketqua = (((luachon == "u" || luachon == "up") && songaunhien == 1) || 
                    ((luachon == "n" || luachon == "ngua") && songaunhien == 2) ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "]" << endl;
    if(ketqua == "Thắng"){
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng " << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET 
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Upngua";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = songaunhien;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}
