#include "..//..//lib//header.h"

void game_chanle(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc = 0; int tongxucxac = 0; int solansai = 0; 
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (c/l): "; 
        getline(cin, luachon);
        if(!(luachon == "c" || luachon == "chan" || luachon == "l" || luachon == "le")){
            cout << YELLOW << "\t\t(!) Vui lòng nhập c/chan hoặc l/le" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "c" || luachon == "chan" || luachon == "l" || luachon == "le" || solansai == solansaitoida));
    if(solansai == solansaitoida) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerchanle);
    cout << "\n" << RED << "[GAME] " << RESET << "ĐOÁN CHẴN LẼ" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "c" || luachon == "chan" ? "Chẵn" : "Lẻ") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
     hieuungamthanh_mp3(dd_nhieudongxuroi, trangthaiamthanh); loadraketqua(5);
    int songaunhien = rand() % 9 + 0;
    string str_songaunhien = to_string(songaunhien);
    cout << YELLOW << "\tSố ngẫu nhiên: " << RESET << "[" << songaunhien << "]" << endl;
    cout << endl;
    for(int i = 0; i < 7; i++){
        for(char s : str_songaunhien){
            ingiuamanhinh(songuyen[s-'0'][i], ORANGE);
        }
        cout << endl;
    }
    string ketqua = ((songaunhien % 2 == 0 && luachon == "c" || luachon == "chan") ||
                     (songaunhien % 2 != 0 && luachon == "l" || luachon == "le")
        ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "] - [" << songaunhien << "]" << endl;
    if (ketqua == "Thắng") {
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET 
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Chanle";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = songaunhien;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}