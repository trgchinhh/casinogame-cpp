#include "include.h"
#include "lib/header.h"

void inbanner(const string tenbanner){
    stringstream ss(tenbanner);
    string line;
    cout << endl;
    while (getline(ss, line)) {
        ingiuamanhinh(line, CYAN);
        cout << endl;
    }
}

void hieuungamthanh_mp3(string duongdanamthanh, bool trangthaiamthanh) {
    if(!trangthaiamthanh) return;
    string cmd = "play \"" + duongdanamthanh + "\" from 0";
    mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}

void hieuungamthanh_wav(string duongdanamthanh, bool trangthaiamthanh){
    if(!trangthaiamthanh) return;
    PlaySoundA(duongdanamthanh.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void chuyendoitrangthaiamthanh(bool& trangthaiamthanh){
    if(!trangthaiamthanh) trangthaiamthanh = true;
    else trangthaiamthanh = false;
}

string xoa_ansi(string s) {
    static regex ansi(R"(\x1B\[[0-9;]*m)");
    return regex_replace(s, ansi, "");
}

void khoitaolist(DanhSachNguoiChoi& danhsachnguoichoi){
    danhsachnguoichoi.first = NULL;
    danhsachnguoichoi.last = NULL;
}

bool kiemtrarongdanhsach(DanhSachNguoiChoi& danhsachnguoichoi){
    return danhsachnguoichoi.first == NULL 
        && danhsachnguoichoi.last == NULL;
}

int kiemtrasoluongtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi){
    if(kiemtrarongdanhsach(danhsachnguoichoi)){
        return 0;
    } 
    ThongTinPtr p = danhsachnguoichoi.last;
    return p->sothutu;
}

// thêm kiểm tra số dư, tiền cược hợp lệ và hàm nap thêm tiền 
bool kiemtrasodutaikhoan(ThongTinPtr& nguoichoi){
    if(nguoichoi->sodu == 0) return false;
    return true;
}

ThongTinPtr khoitaotaikhoan(ThongTinNguoiChoi& thongtinnguoichoi){
    ThongTinPtr tt = new ThongTinNguoiChoi();
    tt->sothutu = thongtinnguoichoi.sothutu;
    tt->tennguoichoi = thongtinnguoichoi.tennguoichoi;
    tt->tentaikhoan = thongtinnguoichoi.tentaikhoan;
    tt->matkhau = thongtinnguoichoi.matkhau;
    tt->sodu = thongtinnguoichoi.sodu;
    tt->next = NULL; tt->prev = NULL;
    return tt;
}

ThongTinPtr timtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, string& tentaikhoan){
    ThongTinPtr tt = danhsachnguoichoi.first;
    while(tt != NULL){
        if(tt->tentaikhoan == tentaikhoan) return tt;
        tt=tt->next;
    }
    return NULL;
}

void themcuoidanhsachtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr thongtinnguoichoi){
    if(kiemtrarongdanhsach(danhsachnguoichoi)){
        danhsachnguoichoi.first = danhsachnguoichoi.last = thongtinnguoichoi;
    } else {
        danhsachnguoichoi.last->next = thongtinnguoichoi;
        thongtinnguoichoi->prev = danhsachnguoichoi.last;
        danhsachnguoichoi.last = thongtinnguoichoi;
    }
}

int sothutucuoicung(DanhSachNguoiChoi& danhsachnguoichoi){
    if(kiemtrarongdanhsach(danhsachnguoichoi)){
        return 0;
    } 
    return danhsachnguoichoi.last->sothutu;
}

int phiencuoicung(string& tentaikhoan){
    ifstream file(dd_danhsachlichsu);
    if(!file.is_open()) return 0;
    json data;
    file >> data;
    file.close();
    if(!data.contains(tentaikhoan)) return 0;
    if(!data[tentaikhoan].is_array()) return 0;
    if(data[tentaikhoan].empty()) return 0;
    return data[tentaikhoan].back()["phien"].get<int>();
}   

string mahoamatkhau(string matkhau){
    return picosha2::hash256_hex_string(matkhau);
}

void ancontrochuot(bool trangthaichuot){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = !trangthaichuot;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

string dinhdangtien(int sotien){
    bool am = sotien < 0;
    string s = to_string(llabs(sotien));
    for (int i = s.length() - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }
    return am ? "-" + s : s;
}

bool xacthucthongtin(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi, int thongtin){
    ThongTinPtr tt = danhsachnguoichoi.first;
    while(tt != NULL){
        if(thongtin == 1){   // 1. kiem tra ten tai khoan
            if(tt->tentaikhoan == thongtinnguoichoi.tentaikhoan) return true;
        } else {             // 2. kiem tra mat khau
            if(tt->matkhau == mahoamatkhau(thongtinnguoichoi.matkhau) &&
               tt->tentaikhoan == thongtinnguoichoi.tentaikhoan) return true;
        }
        tt=tt->next;
    }
    return false;
}

bool dangkytaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    // neu tai khoan cuoi cung co stt = stktd thi out (so tai khoan toi da cho phep)
    if(sothutucuoicung(danhsachnguoichoi) == SoTaiKhoanToiDa){
        cout << RED << "\t\t(!) Đã hết lượt đăng ký tài khoản !" << RESET << endl;
        return false;
    }
    // nhap ten nguoi choi
    int solansainc = 0, solansaitk = 0, solansaimk = 0, solansaisd = 0;
    bool hoplenc = false, hopletk = false, hoplemk = false;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập tên người chơi: ";
        getline(cin, thongtinnguoichoi.tennguoichoi);
        if(thongtinnguoichoi.tennguoichoi.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansainc++;
            continue;
        }
        if(thongtinnguoichoi.tennguoichoi == TentaikhoanAdmin){
            cout << YELLOW << "\t\t(!) Vui lòng đặt tên khác !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansainc++;
            continue;
        }
        hoplenc = true;
    } while(!hoplenc && solansainc < 3);
    if(solansainc == 3) return false;
    // nhap ten tai khoan (dung de dang nhap)
    int check_ttk;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check_ttk = 0;
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check_ttk = 1;
            solansaitk++;
            continue;
        }    
        if(thongtinnguoichoi.tentaikhoan == TentaikhoanAdmin){
            cout << YELLOW << "\t\t(!) Vui lòng đặt tên khác !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansainc++;
            continue;
        }
        if(xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên tài khoản đã tồn tại ! Vui lòng nhập tên khác !" << RESET << endl;
            hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
            check_ttk = 1;
            solansaitk++;
            continue;
        }
        hopletk = true;
    } while(!hopletk && solansaitk < 3);
    if(solansaitk == 3) return false;
    // nhap mat khau (dung de dang nhap)
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập mật khẩu: ";
        getline(cin, thongtinnguoichoi.matkhau);
        if(thongtinnguoichoi.matkhau.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập mật khẩu hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaimk++;
            continue;
        }
        hoplemk = true;
    } while(!hoplemk && solansaimk < 3);
    if(solansaimk == 3) return false;
    // nhap so du 
    bool soduhople = false;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập số dư: ";
        cin >> thongtinnguoichoi.sodu;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập số dư hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaisd++;
            continue;
        }
        else if(thongtinnguoichoi.sodu < sodunhonhat || thongtinnguoichoi.sodu > sodulonnhat){
            cout << YELLOW << "\t\t(!) Vui lòng nhập số dư trong khoảng 1.000 - 100.000.000 VND" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaisd++;
        } else soduhople = true;
    } while(!soduhople && solansaisd < 3);
    if(solansaisd == 3) return false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    thongtinnguoichoi.sothutu = sothutucuoicung(danhsachnguoichoi) + 1;
    luudulieumatjson(thongtinnguoichoi.tentaikhoan, thongtinnguoichoi.matkhau);
    thongtinnguoichoi.matkhau = mahoamatkhau(thongtinnguoichoi.matkhau);
    ThongTinPtr tt = khoitaotaikhoan(thongtinnguoichoi);
    themcuoidanhsachtaikhoan(danhsachnguoichoi, tt);
    luudulieujson(danhsachnguoichoi);
    cout << GREEN << "\t(*) Tạo tài khoản thành công !" << RESET << endl;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    return true;
}

bool dangnhaptaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    if(kiemtrajsontrong(dd_danhsachtaikhoan)){
        cout << YELLOW << "\t(!) Chưa có tài khoản ! Vui lòng đăng ký trước !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return false;
    }
    // phân quyền là user tránh lỗi login vào tk admin
    thongtinnguoichoi.phanquyen = Nguoichoi;
    // nhap ten tai khoan
    int check1, solansaitk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check1 = 0;
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if (thongtinnguoichoi.tentaikhoan == TentaikhoanAdmin) {
            thongtinnguoichoi.phanquyen = Admin;
            break;
        } else thongtinnguoichoi.phanquyen = Nguoichoi;
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
            continue;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
            continue;
        }
    } while(check1 && solansaitk < 3);

    if(solansaitk == 3) return false;
    int check2, solansaimk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check2 = 0;
        cout << "\t(?) Nhập mật khẩu: ";
        getline(cin, thongtinnguoichoi.matkhau);
        if (thongtinnguoichoi.tentaikhoan == TentaikhoanAdmin) {
            if (thongtinnguoichoi.matkhau != MatkhauAdmin) {
                cout << YELLOW << "\t\t(!) Mật khẩu admin không hợp lệ !" << RESET << endl;
                hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
                check2 = 1;
                solansaimk++;
            } else break;
        }
        if(thongtinnguoichoi.matkhau.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống mật khẩu !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
            continue;
        } 
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 2)){
            cout << YELLOW << "\t\t(!) Mật khẩu không hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
            continue;
        }
    } while(check2 && solansaimk < 3);
    if(solansaimk == 3) return false;
    if (thongtinnguoichoi.phanquyen == Admin) {
        cout << GREEN << "\t(*) Đăng nhập Admin thành công !" << RESET << endl;
    } else cout << GREEN << "\t(*) Đăng nhập thành công !" << RESET << endl;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    return true;
}

bool xacthucdangnhapdangky(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi, int dangnhapdangky){
    if(dangnhapdangky == 1){
        if(!dangkytaikhoan(danhsachnguoichoi, thongtinnguoichoi)){
            cout << RED << "\t(!) Đăng ký tài khoản không thành công !" << RESET << endl;
            return false;
        }
    }
    if(dangnhapdangky == 2){
        if(!dangnhaptaikhoan(danhsachnguoichoi, thongtinnguoichoi)){
            cout << RED << "\t(!) Đăng nhập tài khoản không thành công !" << RESET << endl;
            dungchuongtrinh();
            return false;
        }
    }
    return true;
}

void xoataikhoannguoichoi(DanhSachNguoiChoi& danhsachnguoichoi){
    if(kiemtrajsontrong(dd_danhsachtaikhoan)){
        cout << YELLOW << "\t(!) Chưa có tài khoản để xóa" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    ThongTinNguoiChoi thongtinnguoichoi;
    int check1, solansaitk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check1 = 0;
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
            continue;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
        }
    } while(check1 && solansaitk < 3);

    if(solansaitk == 3) return;
    int check2, solansaimk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check2 = 0;
        cout << "\t(?) Nhập mật khẩu: ";
        getline(cin, thongtinnguoichoi.matkhau);
        if(thongtinnguoichoi.matkhau.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống mật khẩu !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
            continue;
        } 
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 2)){
            cout << YELLOW << "\t\t(!) Mật khẩu không hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
        }
    } while(check2 && solansaimk < 3);
    if(solansaimk == 3) return;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    if(xoataikhoanjson(thongtinnguoichoi.tentaikhoan)){
        cout << GREEN << "\t\t(*) Xóa tài khoản " << thongtinnguoichoi.tentaikhoan << " thành công !" << RESET << endl;
        return;
    }
    cout << RED << "\t\t(*) Xóa tài khoản " << thongtinnguoichoi.tentaikhoan << " không thành công !" << RESET << endl;
}

bool kiemtrajsontrong(string duongdanjson){
    ifstream file(duongdanjson);
    if(!file.is_open()) return true;
    json data;
    try {
        file >> data;
    } catch(...) {
        return true; 
    }
    return data.is_array() && data.empty();
}

void taidulieujson(DanhSachNguoiChoi& danhsachnguoichoi){
    ifstream file(dd_danhsachtaikhoan);
    if(!file.is_open()){
        cout << RED << "\t\t(!) Không thể mở file dữ liệu người chơi !" << RESET << endl;
        return;
    }
    if(kiemtrajsontrong(dd_danhsachtaikhoan)){
        return;
    }
    khoitaolist(danhsachnguoichoi);
    json data; file >> data; file.close();
    for(auto& i : data){
        ThongTinNguoiChoi ttnc;
        ttnc.sothutu      = i["sothutu"];
        ttnc.tennguoichoi = i["tennguoichoi"];
        ttnc.tentaikhoan  = i["tentaikhoan"];
        ttnc.matkhau      = i["matkhau"];
        ttnc.sodu         = i["sodu"];
        ThongTinPtr tt = khoitaotaikhoan(ttnc);
        themcuoidanhsachtaikhoan(danhsachnguoichoi, tt);
    }
}

void luudulieujson(DanhSachNguoiChoi& danhsachnguoichoi){
    json j = json::array();
    ThongTinPtr p = danhsachnguoichoi.first;
    while(p != NULL){
        json i;
        i["sothutu"]      = p->sothutu; 
        i["tennguoichoi"] = p->tennguoichoi;
        i["tentaikhoan"]  = p->tentaikhoan;
        i["matkhau"]      = p->matkhau;
        i["sodu"]         = p->sodu;
        j.push_back(i);
        p=p->next;
    }
    ofstream file(dd_danhsachtaikhoan);
    file << setw(4) << j; file.close();
}

vector<ThongTinNguoiChoi> taithongtinnguoichoi(DanhSachNguoiChoi& danhsachnguoichoi){
    vector<ThongTinNguoiChoi> danhsachthongtinnguoichoi;
    ifstream file(dd_danhsachtaikhoan);
    if(!file.is_open()) return danhsachthongtinnguoichoi;
    json data; file >> data; file.close();
    for(auto& i : data){
        ThongTinNguoiChoi thongtinnguoichoi;
        thongtinnguoichoi.sothutu       = i["sothutu"];
        thongtinnguoichoi.tennguoichoi  = i["tennguoichoi"];
        thongtinnguoichoi.tentaikhoan   = i["tentaikhoan"];
        thongtinnguoichoi.sodu          = i["sodu"];
        danhsachthongtinnguoichoi.push_back(thongtinnguoichoi); 
    }
    return danhsachthongtinnguoichoi;
}

vector<LichSu> tailichsujson(string& tentaikhoan){
    vector<LichSu> danhsachlichsu;
    ifstream file(dd_danhsachlichsu);
    if(!file.is_open()) return danhsachlichsu;
    json data; file >> data; file.close();
    if(!data.contains(tentaikhoan)) return danhsachlichsu;
    for(auto& i : data[tentaikhoan]){
        LichSu lichsu;
        lichsu.phien       = i["phien"];
        lichsu.trochoi     = i["trochoi"];
        lichsu.sodu        = i["sodu"];
        lichsu.tiencuoc    = i["tiencuoc"];
        lichsu.luachon     = i["luachon"];
        lichsu.tongdiem    = i["tongxucxac"];
        lichsu.ketqua      = i["ketqua"];
        danhsachlichsu.push_back(lichsu);
    }
    return danhsachlichsu;
}

void luulichsujson(string& tentaikhoan, LichSu& lichsu){
    json data;
    ifstream filein(dd_danhsachlichsu);
    if(filein.is_open()){
        if(!kiemtrajsontrong(dd_danhsachlichsu)) filein >> data;
        filein.close();
    }
    if(!data.contains(tentaikhoan)){
        data[tentaikhoan] = json::array();
    }
    json j;
    j["phien"]       = lichsu.phien;
    j["trochoi"]     = lichsu.trochoi;
    j["sodu"]        = lichsu.sodu;
    j["tiencuoc"]    = lichsu.tiencuoc;
    j["luachon"]     = lichsu.luachon;
    j["tongxucxac"]  = lichsu.tongdiem;
    j["ketqua"]      = lichsu.ketqua;
    data[tentaikhoan].push_back(j);
    if(data[tentaikhoan].size() > 10){
        data[tentaikhoan].erase(0);
    }
    ofstream fileout(dd_danhsachlichsu);
    fileout << setw(4) << data;
    fileout.close();
}

bool xoataikhoanjson(string& tentaikhoan){
    ifstream filein(dd_danhsachtaikhoan);
    if(!filein.is_open()) return false;
    json data_acc;
    filein >> data_acc;
    filein.close();
    if(!data_acc.is_array()) return false;
    bool daxoa = false;
    for(auto it = data_acc.begin(); it != data_acc.end(); ++it){
        if((*it)["tentaikhoan"] == tentaikhoan){
            data_acc.erase(it);
            daxoa = true;
            break;
        }
    }
    if(!daxoa) return false;
    int stt = 1;
    for(auto& acc : data_acc){
        acc["sothutu"] = stt++;
    }
    ofstream fileout(dd_danhsachtaikhoan);
    if(!fileout.is_open()) return false;
    fileout << setw(4) << data_acc;
    fileout.close();
    ifstream filels_in(dd_danhsachlichsu);
    if(filels_in.is_open()){
        json data_ls;
        filels_in >> data_ls;
        filels_in.close();
        if(data_ls.is_object() && data_ls.contains(tentaikhoan)){
            data_ls.erase(tentaikhoan);
            ofstream filels_out(dd_danhsachlichsu);
            if(filels_out.is_open()){
                filels_out << setw(4) << data_ls;
                filels_out.close();
            }
        }
    }
    xoadulieumatjson(tentaikhoan);
    return true;
}

int dodai_hienthi_utf8(const string& s){
    int dem = 0;
    for (size_t i = 0; i < s.size(); ++i){
        if ((s[i] & 0xC0) != 0x80) dem++;
    }
    return dem;
}

void ingiuamanhinh(const string& cau, string mau){
    int chieurong = laychieurongterminal();
    string cau_khong_mau = xoa_ansi(cau);
    int dodai = dodai_hienthi_utf8(cau_khong_mau);
    int khoangtrang = (chieurong - dodai) / 2;
    if(khoangtrang < 0) khoangtrang = 0;
    cout << mau << string(khoangtrang, ' ') << cau << RESET;
}

int do_rong_hien_thi_thuc(const string& str) {
    int length = 0;
    for (int i = 0; i < str.length(); ++i) {
        if ((str[i] & 0xC0) != 0x80) {
            length++;
        }
    }
    return length;
}

void xuatthongtinnguoichoi(ThongTinNguoiChoi& thongtinnguoichoi, int stt) {
    string matkhau = laymatkhau(thongtinnguoichoi.tentaikhoan);
    int r_tennguoichoi = do_rong_hien_thi_thuc(thongtinnguoichoi.tennguoichoi);
    int r_tentaikhoan  = do_rong_hien_thi_thuc(thongtinnguoichoi.tentaikhoan);
    int r_matkhau      = do_rong_hien_thi_thuc(matkhau);  
    int pad_tennguoichoi = (17 - r_tennguoichoi) > 0 ? (17 - r_tennguoichoi) : 0;
    int pad_tentaikhoan  = (16 - r_tentaikhoan)  > 0 ? (16 - r_tentaikhoan)  : 0;
    int pad_matkhau      = max(0, 14 - r_matkhau);
    ostringstream oss;
    oss << "│" << right << setw(5) << stt
        << "│" << string(pad_tennguoichoi, ' ') << thongtinnguoichoi.tennguoichoi
        << "│" << string(pad_tentaikhoan, ' ')  << thongtinnguoichoi.tentaikhoan
        << "│" << string(pad_matkhau, ' ') << matkhau 
        << "│" << right << setw(13) << dinhdangtien(thongtinnguoichoi.sodu)
        << "│";
    ingiuamanhinh(oss.str(), WHITE);
    cout << endl;
}

void xuatbangthongtinnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi) {
    ingiuamanhinh("DANH SÁCH THÔNG TIN NGƯỜI CHƠI", YELLOW); cout << endl << endl;
    ingiuamanhinh("┌─────┬─────────────────┬────────────────┬──────────────┬─────────────┐", WHITE); cout << endl;
    ingiuamanhinh(WHITE "│" RED " STT " WHITE "│" RED " Tên người chơi  " WHITE "│" RED " Tên tài khoản  " WHITE "│" RED "   Mật khẩu   " WHITE "│" RED "    Số dư    " WHITE "│", WHITE);  cout << endl;
    ingiuamanhinh("├─────┼─────────────────┼────────────────┼──────────────┼─────────────┤", WHITE); cout << endl;
    for (int i = 0; i < danhsachthongtinnguoichoi.size(); i++) {
        xuatthongtinnguoichoi(danhsachthongtinnguoichoi[i], danhsachthongtinnguoichoi[i].sothutu);
    }
    ingiuamanhinh("└─────┴─────────────────┴────────────────┴──────────────┴─────────────┘", WHITE);
    cout << endl;
}


void xuatlichsu(LichSu& lichsu, int stt) {
    int r_trochoi = do_rong_hien_thi_thuc(lichsu.trochoi);
    int r_luachon = do_rong_hien_thi_thuc(lichsu.luachon); 
    int r_ketqua  = do_rong_hien_thi_thuc(lichsu.ketqua);
    int pad_trochoi = (10 - r_trochoi) > 0 ? (10 - r_trochoi) : 0;
    int pad_luachon = (8 - r_luachon) > 0 ? (8 - r_luachon) : 0;
    int pad_ketqua  = (9 - r_ketqua) > 0 ? (9 - r_ketqua) : 0;
    ostringstream oss;
    oss << "│" << right << setw(5) << stt
        << "│" << right << setw(6) << lichsu.phien
        << "│" << string(pad_trochoi, ' ') << lichsu.trochoi
        << "│" << right << setw(10) << dinhdangtien(lichsu.tiencuoc)
        << "│" << string(pad_luachon, ' ') << lichsu.luachon
        << "│" << right << setw(6) << lichsu.tongdiem
        << "│" << string(pad_ketqua, ' ') << lichsu.ketqua
        << "│" << right << setw(13) << dinhdangtien(lichsu.sodu)
        << "│";
    string dong = oss.str();
    ingiuamanhinh(dong, WHITE); 
    cout << endl;
}

void xuatbanglichsu(vector<LichSu>& danhsachlichsu){
    if(danhsachlichsu.empty()){
        cout << YELLOW << "\t(!) Chua co lich su choi !" << RESET << endl;
        return;
    }
    hieuungamthanh_mp3(dd_hdpethingonluon, trangthaiamthanh);
    ingiuamanhinh("LỊCH SỬ CHƠI 10 PHIÊN GẦN NHẤT", YELLOW); cout << endl << endl;
    ingiuamanhinh("┌─────┬──────┬──────────┬──────────┬────────┬──────┬─────────┬─────────────┐", WHITE); cout << endl;
    ingiuamanhinh(WHITE "│" RED " STT " WHITE "│" RED " Phiên" WHITE "│" RED " Trò chơi " WHITE "│" RED " Tiền cược" WHITE "│" RED "  Chọn  " WHITE "│" RED " Tổng " WHITE "│" RED " Kết quả " WHITE "│" RED "    Số dư    " WHITE "│", WHITE); cout << endl;
    ingiuamanhinh("├─────┼──────┼──────────┼──────────┼────────┼──────┼─────────┼─────────────┤", WHITE); cout << endl;
    int stt = 1;
    for(auto i = danhsachlichsu.rbegin(); i != danhsachlichsu.rend(); i++){
        xuatlichsu(*i, stt++);
    }
    ingiuamanhinh("└─────┴──────┴──────────┴──────────┴────────┴──────┴─────────┴─────────────┘", WHITE); cout << endl;
}

void xemlichsunguoichoi(DanhSachNguoiChoi& danhsachnguoichoi){
    string tentaikhoan; 
    int solansaitentaikhoan = 0; 
    bool nhaphople = false;
    do {
        cout << "\t(?) Nhập tên tài khoản muốn xem lịch sử: ";
        getline(cin, tentaikhoan);
        if(tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên tài khoản hợp lệ !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        }
        else if(timtaikhoan(danhsachnguoichoi, tentaikhoan) == NULL){
            cout << YELLOW << "\t\t(!) Không tìm thấy tài khoản !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        } else nhaphople = true;
    } while(!nhaphople && solansaitentaikhoan < 3);
    ThongTinPtr nguoichoi = timtaikhoan(danhsachnguoichoi, tentaikhoan);
    vector<LichSu> danhsachlichsu = tailichsujson(nguoichoi->tentaikhoan);
    if(danhsachlichsu.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
    else {
        cout << endl;
        xuatbanglichsu(danhsachlichsu);
    }
}

int laychieurongterminal(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int chieurong = 0;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)){
        chieurong = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return chieurong;
}

int doronghienthi(const char* s){
    int chieurong = 0;
    for(int i = 0; s[i] != '\0'; ){
        unsigned char c = s[i];
        if(c < 128){ chieurong += 1; i += 1; }
        else{ chieurong += 1; i += 2; }
    }
    return chieurong;
}

void dungchuongtrinh(){
    cout << CYAN << "\n\tNhấn phím bất kỳ để tiếp tục ..." << RESET;
    _getch();
}

void hienthongtinadmin(const string& tenadmin){
    const int chieurong = 31;
    string ttk = tenadmin;
    string taikhoan = "(-) Tài khoản: ";
    cout << "┌────────────────────────────┐\n";
    cout << "│" << YELLOW << taikhoan << RESET << UNDERLINE << ttk << NO_UNDERLINE << string(chieurong - taikhoan.length() - ttk.length(), ' ') << "│\n";
    cout << "└────────────────────────────┘\n";
}

void hiensodunguoichoi(ThongTinPtr& nguoichoi){
    const int chieurong = 31;
    string ttk = nguoichoi->tennguoichoi;
    string sd  = dinhdangtien(nguoichoi->sodu);
    string taikhoan = "(-) Tài khoản: ";
    string sodu = "(-) Số dư: ";
    cout << "┌────────────────────────────┐\n";
    cout << "│" << YELLOW << taikhoan << RESET << UNDERLINE << ttk << NO_UNDERLINE << string(chieurong - taikhoan.length() - ttk.length(), ' ') << "│\n";
    cout << "│" << YELLOW << sodu << RESET << UNDERLINE << sd << NO_UNDERLINE << " (VND)" << string(chieurong - sodu.length() - sd.length() - 6, ' ') << "│\n";
    cout << "└────────────────────────────┘\n";
}

void trangchu(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    const int somuc = 4;
    const char* menu[somuc] = {
        "Âm thanh", "Đăng ký", "Đăng nhập", "Thoát",
    };
    int chon = 0; char phim;
    //hieuungamthanh_wav(dd_lindachaocanha, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannertrangchu);
        cout << "┌─────────── " << RESET << RED << "GỢI Ý" << RESET << " ────────────┐" << endl;
        cout << "│ " << YELLOW << "▶ " << WHITE << "Dùng phím " << RED << "↑ ↓" << WHITE << " để di chuyển │" << RESET << endl;
        cout << "│ " << YELLOW << "▶ " << WHITE << "Dùng phím " << RED << "Enter" << WHITE << " để chọn    │" << RESET << endl;
        cout << "└──────────────────────────────┘" << RESET << endl;
        cout << endl;

        cout << "┌──────── " << RED << "MENU" << RESET << " ────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string noidung;
            
            if(i == 0) noidung = string("Âm thanh: ") + (trangthaiamthanh ? "Bật" : "Tắt");
            else noidung = menu[i];

            int chieu_dai_dong = doronghienthi(noidung.c_str());
            int khoang_trang = 15 - chieu_dai_dong;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << (i == 4 ? 0 : i + 1)
                     << " - " << noidung << string(khoang_trang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << (i == 4 ? 0 : i + 1)
                     << " - " << noidung << string(khoang_trang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = _getch();
        int choncu = chon; 
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            //hieuungamthanh_mp3(dd_dichuyenmenu);
            if(chon == 0){
                chuyendoitrangthaiamthanh(trangthaiamthanh);
                hieuungamthanh_wav(dd_lindachaocanha, trangthaiamthanh);
                continue;
            } else if(chon == 1){
                cout << "\n[" << RED << chon << RESET << "] ĐĂNG KÝ TÀI KHOẢN" << RESET << "\n\n";
                xacthucdangnhapdangky(danhsachnguoichoi, thongtinnguoichoi, 1);
            } else if(chon == 2){
                cout << "\n[" << RED << chon << RESET << "] ĐĂNG NHẬP TÀI KHOẢN" << RESET << "\n\n";
                if(xacthucdangnhapdangky(danhsachnguoichoi, thongtinnguoichoi, 2)){
                    ThongTinPtr nguoichoi = timtaikhoan(
                        danhsachnguoichoi,
                        thongtinnguoichoi.tentaikhoan
                    );
                    chosaukhinhapthanhcong(2);
                    // Phân quyền vào sảnh người chơi và admin
                    if(thongtinnguoichoi.phanquyen == Nguoichoi){
                        sanhchoi(danhsachnguoichoi, nguoichoi);
                    } else {
                        sanhadmin(danhsachnguoichoi);
                    }
                }
                continue;
            } else {
                system("cls");
                inbanner(bannertambiet);
                hieuungamthanh_wav(dd_xinvinhbietcu, trangthaiamthanh);
                if(trangthaiamthanh) Sleep(3000);
                ancontrochuot(false);
                exit(0);
            }
            dungchuongtrinh();
        }
    }
}

void sanhadmin(DanhSachNguoiChoi& danhsachnguoichoi) {
    const int somuc = 6;
    const char* menu[somuc] = {
        "Nạp tiền", 
        "Trừ tiền",
        "Xem thông tin", 
        "Xem lịch sử", 
        "Xóa tài khoản", 
        "Đăng xuất",
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(banneradmin);
        taidulieujson(danhsachnguoichoi);
        hienthongtinadmin(TentaikhoanAdmin);
        cout << endl;

        cout << "┌──────── " << RED << "MENU" << RESET << " ────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            int chieu_dai_dong = do_rong_hien_thi_thuc(menu[i]);
            int khoang_trang = max(0, 15 - chieu_dai_dong);
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << (i == 6 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << (i == 6 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon << RESET << "] NẠP TIỀN" << RESET << "\n\n";
                naptienchonguoichoi(danhsachnguoichoi);
            } else if(chon == 1){
                cout << "\n[" << RED << chon << RESET << "] TRỪ TIỀN" << RESET << "\n\n";
                trutiennguoichoi(danhsachnguoichoi);
            } else if(chon == 2){
                cout << "\n[" << RED << chon << RESET << "] XEM THÔNG TIN" << RESET << "\n\n";
                vector<ThongTinNguoiChoi> danhsachthongtinnguoichoi = taithongtinnguoichoi(danhsachnguoichoi);
                if(danhsachthongtinnguoichoi.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
                else {
                    xuatbangthongtinnguoichoi(danhsachthongtinnguoichoi);
                }
            } else if(chon == 3){
                cout << "\n[" << RED << chon << RESET << "] XEM LỊCH SỬ" << RESET << "\n\n";
                xemlichsunguoichoi(danhsachnguoichoi);
            } else if(chon == 4){
                cout << "\n[" << RED << chon << RESET << "] XÓA TÀI KHOẢN" << RESET << "\n\n";
                xoataikhoannguoichoi(danhsachnguoichoi);
            } else {
                cout << "\n[" << RED << chon << RESET << "] ĐĂNG XUẤT" << RESET << "\n\n";
                chosaukhinhapthanhcong(2);
                return;
            }
            dungchuongtrinh();
        }
    }
}

void sanhchoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 7;
    const char* menu[somuc] = {
        "Tài xỉu 1xx", 
        "Tài xỉu 3xx", 
        "Đoán số A -> B", 
        "Chẵn lẻ 0 -> 9", 
        "Úp ngửa xu", 
        "Lịch sử chơi", 
        "Đăng xuất", 
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannercasino);
        taidulieujson(danhsachnguoichoi);
        nguoichoi = timtaikhoan(danhsachnguoichoi, nguoichoi->tentaikhoan);
        hiensodunguoichoi(nguoichoi);
        cout << endl;

        cout << "┌──────── " << RED << "MENU" << RESET << " ────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            int chieu_dai_dong = doronghienthi(menu[i]);
            int khoang_trang = 15 - chieu_dai_dong;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << (i == 7 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << (i == 7 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon << RESET << "] TÀI XỈU 1 XX" << RESET << "\n\n";
                game_taixiu1xx(danhsachnguoichoi, nguoichoi);
            }else if(chon == 1){
                cout << "\n[" << RED << chon << RESET << "] TÀI XỈU 3 XX" << RESET << "\n\n";
                game_taixiu3xx(danhsachnguoichoi, nguoichoi);
            } else if(chon == 2){
                cout << "\n[" << RED << chon << RESET << "] ĐOÁN SỐ" << RESET << "\n\n";
                game_doanso(danhsachnguoichoi, nguoichoi);
            } else if(chon == 3){
                cout << "\n[" << RED << chon << RESET << "] CHẴN LẺ" << RESET << "\n\n";
                game_chanle(danhsachnguoichoi, nguoichoi);
            } else if(chon == 4){
                cout << "\n[" << RED << chon << RESET << "] ÚP NGỬA" << RESET << "\n\n";
                game_upngua(danhsachnguoichoi, nguoichoi);
            } else if(chon == 5){
                cout << "\n[" << RED << chon << RESET << "] LỊCH SỬ CHƠI" << RESET << "\n\n";
                vector<LichSu> danhsachlichsu = tailichsujson(nguoichoi->tentaikhoan);
                if(danhsachlichsu.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
                else {
                    xuatbanglichsu(danhsachlichsu);
                }
            } else {
                // cái này thích thì bật (hơi ồn)
                hieuungamthanh_mp3(dd_maymuanuadi, trangthaiamthanh);
                cout << "\n[" << RED << chon << RESET << "] ĐĂNG XUẤT" << RESET << "\n\n";
                chosaukhinhapthanhcong(2);
                return;
            }
            dungchuongtrinh();
        }
    }
}

void loadraketqua(int sogiay){
    const char kytu[] = {'/', '-', '\\', '|'};
    int vitri = 0;
    while(sogiay > 0){
        cout << "\r\t(" << RED << kytu[vitri] << RESET << ") Vui lòng chờ kết quả trong giây lát...";  
        vitri = (vitri + 1) % 4;
        Sleep(1000);
        sogiay--;
    }
    cout << endl;
}

void chosaukhinhapthanhcong(int sogiay) {
    int phantramtientrinh = 0;
    const int dodaithanh = 25;
    int thoigiandung = static_cast<int>((sogiay * 1000) / dodaithanh);
    for (int i = 0; i <= dodaithanh; i++) {
        int phantram = (i * 100) / dodaithanh;
        cout << "\r\tĐang tải:" << " [";
        for (int j = 0; j < dodaithanh; j++) {
            if (j < i) cout << CYAN << "▆" << RESET;
            else cout << " ";
        }
        phantramtientrinh += 4;
        cout << "] " << RESET << phantramtientrinh << " %" << RESET;
        Sleep(thoigiandung/4);
    }
    cout << endl;
}

bool nhaptiencuoc(int& tiencuoc, ThongTinPtr &nguoichoi){
    bool tiencuochople = false; int solansaitiencuoc = 0;
    do {
        cout << "\t(?) Nhập tiền cược (VND): "; cin >> tiencuoc;
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập tiền cược hợp lệ !" << RESET << endl;
            solansaitiencuoc++;
            continue;
        }
        else if(tiencuoc < 1000){
            cout << YELLOW << "\t\t(!) Vui lòng nạp tiền để chơi tiếp" << RESET << endl;
            solansaitiencuoc++;
        }
        else if(tiencuoc > nguoichoi->sodu) {
            cout << YELLOW << "\t\t(!) Mức cược hợp lệ 1000 - " << nguoichoi->sodu << RESET << endl;
            solansaitiencuoc++;
        } else tiencuochople = true;
    } while(!tiencuochople && solansaitiencuoc < 3);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tiencuochople;
}

void naptienchonguoichoi(DanhSachNguoiChoi& danhsachnguoichoi){
    ThongTinPtr nguoiduocnap = NULL; 
    string tentaikhoan;
    bool tentaikhoanhople = false;
    int solansaitentaikhoan = 0;
    do {
        cout << "\t(?) Nhập tên tài khoản muốn nạp: "; 
        getline(cin, tentaikhoan);
        if(tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên tài khoản hợp lệ !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        }
        nguoiduocnap = timtaikhoan(danhsachnguoichoi, tentaikhoan);
        if(nguoiduocnap == NULL){
            cout << YELLOW << "\t\t(!) Tài khoản không tồn tại !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        } 
        tentaikhoanhople = true;
    } while(!tentaikhoanhople && solansaitentaikhoan < 3);
    if(solansaitentaikhoan == 3){
        cout << RED << "\t(!) Nạp tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    cout << GREEN << "\t(*) Số dư hiện tại: " << dinhdangtien(nguoiduocnap->sodu) << " VND" << RESET << endl; 
    if(nguoiduocnap->sodu >= 100000000){
        cout << YELLOW << "\t\t(!) Số dư cao hơn hoặc bằng 100.000.000 VND không thể nạp thêm" << RESET << endl;
        return;
    }
    bool tiennaphople = false;
    int tiennap = 0; int solansaitiennap = 0;
    do {
        cout << "\t(?) Nhập số tiền muốn nạp (VND): "; cin >> tiennap;
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập tiền nạp hợp lệ !" << RESET << endl;
            solansaitiennap++;
            continue;
        }
        else if(tiennap < 1000 || (nguoiduocnap->sodu + tiennap) > 100000000){
            cout << YELLOW << "\t\t(!) Tiền nạp hợp lệ trong khoảng 1000 -> " << dinhdangtien(100000000 - nguoiduocnap->sodu) << " VND" << RESET << endl;
            solansaitiennap++;
        } else tiennaphople = true;
    } while(!tiennaphople && solansaitiennap < 3);
    if(solansaitiennap == 3){
        cout << RED << "\t(!) Nạp tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    nguoiduocnap->sodu += tiennap;
    luudulieujson(danhsachnguoichoi);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << GREEN << "\t(*) Nạp tiền thành công cho tài khoản: " << nguoiduocnap->tentaikhoan << "\n\t(->) Số dư mới: " << dinhdangtien(nguoiduocnap->sodu) << " VND" << RESET << endl;
}

void trutiennguoichoi(DanhSachNguoiChoi& danhsachnguoichoi){
    ThongTinPtr nguoibitru = NULL; 
    string tentaikhoan;
    bool tentaikhoanhople = false;
    int solansaitentaikhoan = 0;
    do {
        cout << "\t(?) Nhập tên tài khoản muốn trừ tiền: "; 
        getline(cin, tentaikhoan);
        if(tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên tài khoản hợp lệ !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        }
        nguoibitru = timtaikhoan(danhsachnguoichoi, tentaikhoan);
        if(nguoibitru == NULL){
            cout << YELLOW << "\t\t(!) Tài khoản không tồn tại !" << RESET << endl;
            solansaitentaikhoan++;
            continue;
        } 
        tentaikhoanhople = true;
    } while(!tentaikhoanhople && solansaitentaikhoan < 3);
    if(solansaitentaikhoan == 3){
        cout << RED << "\t(!) Trừ tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    cout << GREEN << "\t(*) Số dư hiện tại: " << dinhdangtien(nguoibitru->sodu) << " VND" << RESET << endl; 
    if(nguoibitru->sodu < 1000){
        cout << YELLOW << "\t\t(!) Số dư bé hơn 1.000 VND không thể trừ thêm" << RESET << endl;
        return;
    }
    bool tientruhople = false;
    int tientru = 0; int solansaitientru = 0;
    do {
        cout << "\t(?) Nhập số tiền muốn trừ (VND): "; cin >> tientru;
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập tiền nạp hợp lệ !" << RESET << endl;
            solansaitientru++;
            continue;
        }
        else if(tientru < 1000 || tientru > nguoibitru->sodu){
            cout << YELLOW << "\t\t(!) Tiền nạp hợp lệ trong khoảng 1000 -> " << dinhdangtien(nguoibitru->sodu) << " VND" << RESET << endl;
            solansaitientru++;
        } else tientruhople = true;
    } while(!tientruhople && solansaitientru < 3);
    if(solansaitientru == 3){
        cout << RED << "\t(!) Trừ tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    nguoibitru->sodu -= tientru;
    luudulieujson(danhsachnguoichoi);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << GREEN << "\t(*) Đã trừ tiền tài khoản: " << nguoibitru->tentaikhoan << "\n\t(->) Số dư mới: " << dinhdangtien(nguoibitru->sodu) << " VND" << RESET << endl;
}

int main(){
    SetConsoleTitleA("Nhà Cái Châu Phi");
    SetConsoleCP(CP_UTF8); 
    SetConsoleOutputCP(CP_UTF8);
    ancontrochuot(true); 
    srand(time(NULL));
    DanhSachNguoiChoi danhsachnguoichoi; 
    khoitaolist(danhsachnguoichoi);
    taidulieujson(danhsachnguoichoi);
    ThongTinNguoiChoi thongtinnguoichoi; 
    trangchu(danhsachnguoichoi, thongtinnguoichoi);
    return 0;
}
