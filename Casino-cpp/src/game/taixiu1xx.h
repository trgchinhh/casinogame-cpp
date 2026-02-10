#include "..//lib//header.h"

void game_taixiu1xx(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc; int solansai = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (t/x): "; 
        getline(cin, luachon);
        if(!(luachon == "t" || luachon == "tai" || luachon == "x" || luachon == "xiu")){
            cout << YELLOW << "\t\t(!) Vui lòng chọn t/tai hoặc x/xiu" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "t" || luachon == "tai" || luachon == "x" || luachon == "xiu" || solansai == solansaitoida));
    if(solansai == solansaitoida) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannertaixiu);
    cout << "\n" << RED << "[GAME] " << RESET << "TÀI XỈU 1 XÚC XẮC" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "t" || luachon == "tai" ? "Tài" : "Xỉu") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); 
    loadraketqua(3);
    int xucxac = rand() % 6 + 1;
    cout << YELLOW << "\tXúc xắc: " << RESET << "[" << xucxac << "]" << endl;
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matxucxac[xucxac][i], WHITE);
        cout << endl;
    } 
    cout << endl;
    string ketqua = ((xucxac > 3 && (luachon == "t" || luachon == "tai")) ||
                     (xucxac <= 3 && (luachon == "x" || luachon == "xiu")) 
        ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "] - [" << xucxac << "]" << endl;
    if (ketqua == "Thắng"){
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" 
             << RESET << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" 
             << RESET << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Taixiu1xx";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = xucxac;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}
