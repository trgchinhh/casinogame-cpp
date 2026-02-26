#include "..//..//lib//header.h"

void game_keobuabao(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc = 0; string luachoncuabot; int solansai = 0; 
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    //cout << "\tDanh sách chọn: ['keo', 'bua', 'bao']" << endl;
    cout << YELLOW << "\tDanh sách chọn:" << RESET 
         << " ["
         << RED << "'keo'" << RESET << ", "
         << GREEN << "'bua'" << RESET << ", "
         << YELLOW << "'bao'" << RESET
         << "]" 
    << endl;
    do {
        cout << "\t(?) Nhập lựa chọn: ";
        getline(cin, luachon);
        if(!(luachon == "keo" || luachon == "bua" || luachon == "bao")){
            cout << YELLOW << "\t\t(!) Vui lòng nhập kéo hoặc búa hoặc bao" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "keo" || luachon == "bua" || luachon == "bao" || solansai == solansaitoida));
    if(solansai == solansaitoida) return;
    if (luachon == "keo") luachon = "Kéo";
    else if (luachon == "bua") luachon = "Búa";
    else if (luachon == "bao") luachon = "Bao";
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    cout << "\t[";
    if (luachon == "Kéo")      cout << RED;
    else if (luachon == "Búa") cout << GREEN;
    else if (luachon == "Bao") cout << YELLOW;
    cout << luachon << RESET << "]: ";
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    clear();
    inbanner(bannerkeobuabao);
    cout << "\n" << RED << "[GAME] " << RESET << "KÉO BÚA BAO" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << luachon <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    //hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); //loadraketqua(5);
    cout << YELLOW << "\tBot ra: " << RESET; 
    int random_keobuabao = rand() % 3;
    string ten_keobuabao[3] = {"Kéo", "Búa", "Bao"};
    luachoncuabot = ten_keobuabao[random_keobuabao]; 
    cout << "[" << luachoncuabot << "]" << endl;
    cout << endl;
    for(int i = 0; i < 6; i++){
        ingiuamanhinh(keobuabao[random_keobuabao][i], WHITE);
        cout << endl;
    }
    cout << endl;
    string ketqua;
    if (luachon == luachoncuabot) ketqua = "Hòa";
    else if (
        (luachon == "Kéo" && luachoncuabot == "Bao") ||
        (luachon == "Búa" && luachoncuabot == "Kéo") ||
        (luachon == "Bao" && luachoncuabot == "Búa")
    ) ketqua = "Thắng";
    else ketqua = "Thua";
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "] " << endl;
    if(ketqua == "Hòa"){
        int tienhoa = nguoichoi->sodu + tiencuoc;
        cout << "\tTrả lại tiền: " << YELLOW << "~" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh); 
    } else if(ketqua == "Thắng"){
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += int(tienthang);
        cout << GREEN << "\tChúc mừng bạn đã thắng bot" << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh); 
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET 
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Keobuabao";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = random_keobuabao;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}