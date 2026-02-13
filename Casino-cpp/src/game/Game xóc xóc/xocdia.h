#include "..//..//lib//header.h"

// 0 = trắng, 1 = đỏ
vector<int> batxoc(4);

void xocdia(vector<int>& bat) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    for (int i = 0; i < 4; i++) bat[i] = dist(gen);
}

int demdo(const vector<int>& bat) {
    int dem = 0;
    for (int b : bat)
        if (b == 1) dem++;
    return dem;
}

void inxocdia(const vector<int>& bat) {
    cout << "\t[Bát xóc]: ";
    for (int b : bat) {
        if (b == 1) 
            cout << "["<< RED << "●" << RESET << "]" << " ";
        else        
            cout << "[●]" << " ";
    }
}

void game_xocdia(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi) {
    if (!kiemtrasodutaikhoan(nguoichoi)) {
        cout << YELLOW << "\t(!) Số dư không đủ !" << RESET << endl;
        return;
    }
    int tiencuoc = 0, solansai = 0; string luachon; 
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
    if (!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    } 
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerxocdia);
    cout << "\n" << RED << "[GAME] " << RESET << "XÓC ĐĨA\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai 
         << YELLOW << "\tCược: " << RESET << (luachon == "c" || luachon == "chan" ? "Chẵn" : "Lẽ") 
         << YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << RESET << " VND" << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); loadraketqua(5);
    //cout << YELLOW << "\tMặt quân vị: " << RESET;
    cout << endl;
    vector<int> batxoc(4);
    xocdia(batxoc);
    int sodo = demdo(batxoc);
    int sotrang = 4 - sodo;
    inxocdia(batxoc);

    bool lachan = (sodo % 2 == 0);

    cout << endl;
    cout << "\t    └─>" << " Quân vị: "; 
    if (batxoc[0] == 1){
        cout << YELLOW << sodo << RESET << " đỏ "
             << YELLOW << sotrang << RESET << " trắng ("; 
    } else {
        cout << YELLOW << sotrang << RESET << " trắng "
             << YELLOW << sodo << RESET << " đỏ (";
    }
    cout << YELLOW << (lachan ? "Chẵn" : "Lẻ") << RESET << ")" << endl;

    cout << endl;
    string ketqua;
    if ((luachon == "c" || luachon == "chan") && lachan) ketqua = "Thắng";
    else if ((luachon == "l" || luachon == "le") && !lachan) ketqua = "Thắng";
    else ketqua = "Thua";
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "]" << endl;
    if (ketqua == "Thắng") {
        int tienthang = tiencuoc * 2;
        nguoichoi->sodu += tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET 
             << "\n\tTiền thắng: " << YELLOW << "+" << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET 
             << "\n\tTiền thua: " << YELLOW << "-" << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }

    LichSu lichsu;
    lichsu.phien = phienhientai;
    lichsu.trochoi = "XocDia";
    lichsu.sodu = nguoichoi->sodu;
    lichsu.tiencuoc = tiencuoc;
    lichsu.luachon = luachon;
    lichsu.tongdiem = sodo;
    lichsu.ketqua = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}