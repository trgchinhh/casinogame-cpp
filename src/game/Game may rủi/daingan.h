#include "..//..//lib//header.h"

// hàm di chuyển thanh đến vị trí giữa màn terminal 
void dichuyenXY(int x, int y){
#ifdef _WIN32
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
#endif
}

void game_daingan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc; int solansai = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (d/n): "; 
        getline(cin, luachon);
        if(!(luachon == "d" || luachon == "dai" || luachon == "n" || luachon == "ngan")){
            cout << YELLOW << "\t\t(!) Vui lòng chọn d/dai hoặc n/ngan" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "d" || luachon == "dai" || luachon == "n" || luachon == "ngan" || solansai == solansaitoida));
    if(solansai == solansaitoida) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    clear();
    inbanner(bannerdaingan);
    cout << "\n" << RED << "[GAME] " << RESET << "DÀI NGẮN" << "\n\n";
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "d" || luachon == "dai" ? "Dài" : "Ngắn") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl; 
    //hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); //loadraketqua(5);
    int tongdodai = 50;
    int diemcandat = tongdodai / 2 + 5; 
    int dodai = rand() % tongdodai + 1;
    int chieurongterminal = laychieurongterminal();
    int chieurongthanhload = tongdodai + 2;
    int diemXbatdau = (chieurongterminal - chieurongthanhload) / 2;
    int diemYbatdau = 16;

    // Câu lưu ý
    if(luachon == "d" || luachon == "dai"){
        cout << RED << "\tLưu ý: " 
             << RESET << "Để thắng thanh cần đạt tối thiểu [" 
             << RED << diemcandat << RESET << " / " << tongdodai << "] điểm" << endl;
    } else {
        cout << RED << "\tLưu ý: " 
             << RESET << "Để thắng thanh cần dưới [" 
             << RED << diemcandat << RESET << "] điểm" << endl;
    }
    cout << endl;
    dichuyenXY(diemXbatdau, diemYbatdau);
    cout << RED << "[" << RESET;
    for(int i = 0; i < tongdodai; i++) { 
        cout << " ";
        if(i == diemcandat) {
            cout << CYAN << "|" << RESET;
        }
    }
    cout << RED << "]" << RESET;
    cout << " " << "[0 / " << tongdodai << "]";
    sleep(1500);
    for(int i = 0; i < dodai; i++){
        dichuyenXY(diemXbatdau + 1 + i, diemYbatdau);
        cout << "▆";
        if(i == diemcandat){
            dichuyenXY(diemXbatdau + 1 + i, diemYbatdau);
            cout << CYAN << "|" << RESET;
        }
        dichuyenXY(diemXbatdau + tongdodai + 4, diemYbatdau);
        cout << "[" << (i + 1) << " / " << tongdodai << "]";
        sleep(150);
    }
    cout << endl << endl;
    //cout << YELLOW << "\tĐộ dài: " << RESET << "[" << dodai << "/" << tongdodai << "]" << endl;
    string ketqua = ((dodai > diemcandat && (luachon == "d" || luachon == "dai")) ||
                     (dodai < diemcandat && (luachon == "n" || luachon == "ngan")) 
        ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "] - " 
         << YELLOW << "Độ dài: " << RESET << "[" << dodai << " / " << tongdodai << "]" << endl;
    if(ketqua == "Thắng"){
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
    lichsu.trochoi    = "Daingan";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = dodai;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
}