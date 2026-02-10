#include "..//lib//header.h"

void game_doanmau(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    map<string,int> map_mau = {
        {"do",0},{"cam",1},{"vang",2},
        {"luc",3},{"lam",4},{"cham",5},{"tim",6}
    };
    string ten_mau[7] = {
        "Đỏ","Cam","Vàng","Lục","Lam","Chàm","Tím"
    };
    string luachon;
    vector<int> danhsachmau; map<int,int> tiencuoc; int tongtiencuoc = 0;
    //cout << "\tDanh sách chọn: ['do', 'cam', 'vang', 'luc', 'lam', 'cham', 'tim']" << endl;
    // hiện danh sách có màu theo tên màu 
    cout << YELLOW << "\tDanh sách chọn:" << RESET
         << " ["
         << RED     << "'do'"   << RESET << ", "
         << ORANGE  << "'cam'"  << RESET << ", "
         << YELLOW  << "'vang'" << RESET << ", "
         << GREEN   << "'luc'"  << RESET << ", "
         << BLUE    << "'lam'"  << RESET << ", "
         << INDIGO  << "'cham'" << RESET << ", "
         << MAGENTA << "'tim'"  << RESET
         << "]"
    << endl;
    cout << "\t(?) Nhập lựa chọn: ";
    getline(cin, luachon); stringstream ss(luachon);
    string tam;
    while(ss >> tam){
        if(map_mau.count(tam)) danhsachmau.push_back(map_mau[tam]);
        else {
            cout << YELLOW << "\t\t(!) Lựa chọn không hợp lệ !" << RESET << endl;
            return;
        }
    }
    if(danhsachmau.empty()){
        cout << YELLOW << "\t\t(!) Không được để trống lựa chọn !" << RESET << endl;
        return;
    }
    if(danhsachmau.size() > 3){
        cout << YELLOW << "\t\t(!) Chỉ được cược tối đa 3 màu !" << RESET << endl;
        return;
    }
    for(int m : danhsachmau){
        cout << "\t["; 
        switch (m) {
            case 0: cout << RED;     break; 
            case 1: cout << ORANGE;  break; 
            case 2: cout << YELLOW;  break; 
            case 3: cout << GREEN;   break; 
            case 4: cout << BLUE;    break; 
            case 5: cout << INDIGO;  break; 
            case 6: cout << MAGENTA; break; 
        }
        cout << ten_mau[m] << RESET << "]: ";
        int tc; if(!nhaptiencuoc(tc, nguoichoi)) return;
        tiencuoc[m] = tc;
        tongtiencuoc += tc;
        nguoichoi->sodu -= tc;
    }
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerdoanmau);
    cout << "\n" << RED << "[GAME] " << RESET << "ĐOÁN MÀU" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;  
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai
         << YELLOW << "\tCược: " << RESET;
        for(int c : danhsachmau) cout << ten_mau[c] << " ";
    cout << YELLOW << "\tTổng tiền cược: " << RESET << dinhdangtien(tongtiencuoc) << " VND" << endl;
    cout << YELLOW << "\tChi tiết cược:\n" << RESET;
    for(auto &p : tiencuoc){
        cout << "\t   - " << ten_mau[p.first] 
             << ": " << YELLOW << dinhdangtien(p.second)
             << RESET << " VND\n";
    }
    cout << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); loadraketqua(5);
    int ketquamau1 = rand() % 7;
    int ketquamau2 = rand() % 7;
    cout << YELLOW << "\tMàu kết quả: " << RESET << "[" << ten_mau[ketquamau1] << "] - [" << ten_mau[ketquamau2] << "]" << endl;
    cout << endl;
    for(int i = 0; i < 5 ;i++){
        ingiuamanhinh(
            xucxac7mau[ketquamau1][i] + "        "
          + xucxac7mau[ketquamau2][i] 
        , WHITE);
        cout << endl;
    }
    cout << endl;
    int dem[7] = {0};
    dem[ketquamau1]++;
    dem[ketquamau2]++;
    int tienthang = 0;
    int sodoantrung = 0;
    for(auto &p : tiencuoc){
        int mau  = p.first;
        int tien = p.second;
        if(dem[mau] > 0){
            sodoantrung += dem[mau];
            tienthang   += tien * dem[mau];
        }
    }
    string ketqua = (tienthang > 0) ? "Thắng" : "Thua";
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "]" << endl;
    if(ketqua == "Thắng"){
        tienthang = tienthang * 2;
        nguoichoi->sodu += tienthang;
        cout << GREEN << "\tChúc mừng bạn đã đoán đúng " << sodoantrung << " màu" << RESET
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tBạn không đoán trúng màu nào" << RESET
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tongtiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien    = phienhientai;
    lichsu.trochoi  = "Doanmau";
    lichsu.sodu     = nguoichoi->sodu;
    lichsu.tiencuoc = tongtiencuoc;
    lichsu.luachon  = luachon;
    lichsu.tongdiem = sodoantrung;
    lichsu.ketqua   = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}