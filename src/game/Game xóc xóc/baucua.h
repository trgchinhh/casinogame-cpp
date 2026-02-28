#include "..//..//lib//header.h"

void game_baucua(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    map<string,int> map_baucua = {
        {"bau",0},{"cua",1},{"tom",2},
        {"ca",3},{"nai",4},{"ga",5}
    };
    string ten_baucua[6] = {"Bầu", "Cua", "Tôm", "Cá", "Nai", "Gà"};
    string luachon; map<int, int> tiencuoc; int tongtiencuoc = 0; int solansai = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    //cout << YELLOW << "\tDanh sách chọn:" << RESET << " ['bau', 'cua', 'tom', 'ca', 'nai', 'ga']" << endl;
    cout << YELLOW << "\tDanh sách chọn:" << RESET
         << " ["
         << RED     << "'bau'" << RESET << ", "
         << ORANGE  << "'cua'" << RESET << ", "
         << YELLOW  << "'tom'" << RESET << ", "
         << GREEN   << "'ca'"  << RESET << ", "
         << BLUE    << "'nai'" << RESET << ", "
         << MAGENTA << "'ga'"  << RESET
         << "]"
     << endl;
    cout << "\t(?) Nhập lựa chọn: ";
    getline(cin, luachon); stringstream ss(luachon);
    string tam;
    vector<int> danhsachcon; // danh sách những con đã chọn 
    while(ss >> tam){
        if(map_baucua.count(tam)) danhsachcon.push_back(map_baucua[tam]);
        else {
            cout << YELLOW << "\t\t(!) Lựa chọn không hợp lệ !" << RESET << endl;
            return;
        }
    }
    if(danhsachcon.empty()){
        cout << YELLOW << "\t\t(!) Không được để trống lựa chọn !" << RESET << endl;
        return;
    }

    for(int c : danhsachcon){
        cout << "\t[";
        switch (c) {
            case 0: cout << RED;     break; 
            case 1: cout << ORANGE;  break; 
            case 2: cout << YELLOW;  break; 
            case 3: cout << GREEN;   break; 
            case 4: cout << BLUE;    break; 
            case 5: cout << INDIGO;  break; 
            case 6: cout << MAGENTA; break; 
        }
        cout << ten_baucua[c] << RESET << "]: ";
        int tc; if(!nhaptiencuoc(tc, nguoichoi)) return;
        tiencuoc[c] = tc; 
        tongtiencuoc += tc;
        nguoichoi->sodu -= tc;
    }

    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    clear();
    inbanner(bannerbaucua);
    cout << "\n" << RED << "[GAME] " << RESET << "BẦU CUA" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND\n";
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai <<  
            YELLOW << "\tCược: " << RESET; 
            for(int c : danhsachcon) cout << ten_baucua[c] << " ";
    cout << YELLOW << "\tTổng tiền cược: " << RESET << dinhdangtien(tongtiencuoc) << " VND" << endl;
    cout << YELLOW << "\tChi tiết cược: " << RESET << endl;
    for (auto &p : tiencuoc) {
    int con = p.first;
    int tien = p.second;
    cout << "\t    - " << ten_baucua[con] 
         << " : " << YELLOW << dinhdangtien(tien)
         << RESET << " VND" << endl;
    }
    cout << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); 
    loadraketqua(3);
    cout << YELLOW << "\tXúc xắc: " << RESET;
    int xucxac1 = rand() % 6;
    int xucxac2 = rand() % 6;
    int xucxac3 = rand() % 6;
    cout << "[" << ten_baucua[xucxac1] << "] [" << ten_baucua[xucxac2] << "] [" << ten_baucua[xucxac3] << "]" << endl; 
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(
            xucxacbaucua[xucxac1][i] + "        " 
          + xucxacbaucua[xucxac2][i] + "        " 
          + xucxacbaucua[xucxac3][i] 
        , WHITE); 
        cout << endl;
    }
    cout << endl;
    int dem[6] = {0};
    dem[xucxac1]++; 
    dem[xucxac2]++;
    dem[xucxac3]++;
    int tienthang = 0;
    int sodoantrung = 0;
    for(auto &p : tiencuoc){
        int con  = p.first; int tien = p.second;
        if(dem[con] > 0){
            sodoantrung += dem[con];
            tienthang   += tien * dem[con];
        }
    }

    string ketqua = (tienthang > 0) ? "Thắng" : "Thua";
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "]" << endl; 
    if(ketqua == "Thắng"){
        tienthang = tienthang * 2;
        nguoichoi->sodu += tienthang;
        cout << GREEN << "\tChúc mừng bạn đoán đúng " << sodoantrung << " xúc xắc" << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tBạn không trúng xúc xắc nào" << RESET
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tongtiencuoc) << RESET << " VND" << endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }

    nguoichoi->sotiendachoi += tongtiencuoc;
    nguoichoi->sotienthang  += tienthang;
    LichSu lichsu;
    lichsu.phien    = phienhientai;
    lichsu.trochoi  = "BauCua";
    lichsu.sodu     = nguoichoi->sodu;
    lichsu.tiencuoc = tongtiencuoc;
    lichsu.luachon  = luachon;
    lichsu.tongdiem = sodoantrung;
    lichsu.ketqua   = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}