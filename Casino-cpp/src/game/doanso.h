#include "..//lib//header.h"

void game_doanso(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    int luachon; int tiencuoc = 0; int solansai = 0; 
    int sobatdau, soketthuc; bool kiemtrahople = false;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập 2 số làm khoảng số muốn đoán (VD: 1 5): ";
        cin >> sobatdau; cin >> soketthuc;
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập số hợp lệ !" << RESET << endl;
            solansai++;
            continue;
        }
        if(sobatdau > soketthuc || sobatdau == soketthuc){
            cout << YELLOW << "\t\t(!) Vui lòng nhập số đầu < số cuối !" << RESET << endl;
            solansai++;
        } else kiemtrahople = true;
    } while(!kiemtrahople && solansai < 3);
    if(solansai == 3) return;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerdoanso);
    cout << "\n" << RED << "[GAME] " << RESET << "ĐOÁN SỐ" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    int solansai_1 = 0; bool kiemtrahople_1 = false;
    do {
        cout << "\t(?) Chọn 1 số trong khoảng " << sobatdau << " -> " << soketthuc << ": ";
        cin >> luachon; 
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập số hợp lệ !" << RESET << endl;
            solansai_1++;
            continue;
        }
        if(luachon < sobatdau || luachon > soketthuc){
            cout << YELLOW << "\t\t(!) Vui lòng nhập trong khoảng " << sobatdau << " -> " << soketthuc << RESET << endl;
            solansai_1++;
        } else kiemtrahople_1 = true;
    } while(!kiemtrahople_1 && solansai_1 < 3);
    if(solansai_1 == 3) return;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    hieuungamthanh_mp3(dd_nhieudongxuroi, trangthaiamthanh); loadraketqua(5); 
    int songaunhien = sobatdau + rand() % (soketthuc - sobatdau + 1);
    cout << YELLOW << "\tKết quả:" << RESET << " [" << songaunhien << "]" << endl << endl;
    string str_songaunhien = to_string(songaunhien);
    for(int i = 0; i < 7; i++){
        string dong = "";
        for(char s : str_songaunhien){
            dong += songuyen[s - '0'][i];
            dong += "    "; 
        }
        ingiuamanhinh(dong, ORANGE);
        cout << endl;
    }
    cout << endl;
    string ketqua = (luachon == songaunhien ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả: " << RESET << " [" << ketqua << "]" << endl;
    if(luachon == songaunhien){
        int tienthang = tiencuoc * (soketthuc - sobatdau + 1);
        nguoichoi->sodu += tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Doanso";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = to_string(luachon);
    lichsu.tongdiem   = songaunhien;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
    return;
}
