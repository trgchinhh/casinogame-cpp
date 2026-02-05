#include "..//lib//header.h"

void game_taixiu3xx(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc = 0; int tongxucxac = 0; int solansai = 0; 
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (t/x): "; 
        getline(cin, luachon);
        if(!(luachon == "t" || luachon == "tai" || luachon == "x" || luachon == "xiu")){
            cout << YELLOW << "\t\t(!) Vui lòng nhập t/tai hoặc x/xiu" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "t" || luachon == "tai" || luachon == "x" || luachon == "xiu" || solansai == 3));
    if(solansai == 3) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannertaixiu);
    cout << "\n" << RED << "[GAME] " << RESET << "TÀI XỈU 3 XÚC XẮC" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "t" || luachon == "tai" ? "Tài" : "Xỉu") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); loadraketqua(5);
    cout << YELLOW << "\tXúc xắc: " << RESET;
    int xucxac1 = rand() % 6 + 1;
    int xucxac2 = rand() % 6 + 1;
    int xucxac3 = rand() % 6 + 1;
    tongxucxac = xucxac1 + xucxac2 + xucxac3;
    cout << "[" << xucxac1 << "] [" << xucxac2 << "] [" << xucxac3 << "]" << endl; 
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matxucxac[xucxac1][i] + "        " + matxucxac[xucxac2][i] + "        " + matxucxac[xucxac3][i], WHITE);
        cout << endl;
    }
    cout << endl;
    string ketqua = (tongxucxac > 10 ? "Tài" : "Xỉu");
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "] - [" << tongxucxac << "]" << endl;
    if (
        ((luachon == "t" || luachon == "tai") && ketqua == "Tài") ||
        ((luachon == "x" || luachon == "xiu") && ketqua == "Xỉu")) {
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Taixiu3xx";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = tongxucxac;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
    return;
}
