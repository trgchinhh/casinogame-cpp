#include "lib//header.h"

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
    mciSendString(cmd.c_str(), NULL, 0, NULL);
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
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập tên người chơi: ";
        getline(cin, thongtinnguoichoi.tennguoichoi);
        if(thongtinnguoichoi.tennguoichoi.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập tên hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansainc++;
        }
    } while(thongtinnguoichoi.tennguoichoi.empty() && solansainc < 3);
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
        }    
        if(xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên tài khoản đã tồn tại ! Vui lòng nhập tên khác !" << RESET << endl;
            hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
            check_ttk = 1;
            solansaitk++;
        }
    } while(check_ttk && solansaitk < 3);
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
        }
    } while(thongtinnguoichoi.matkhau.empty() && solansaimk < 3);
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
    // nhap ten tai khoan
    int check1, solansaitk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check1 = 0;
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
        }
    } while(check1 && solansaitk < 3);

    if(solansaitk == 3) return false;
    int check2, solansaimk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check2 = 0;
        cout << "\t(?) Nhập mật khẩu: ";
        getline(cin, thongtinnguoichoi.matkhau);
        if(thongtinnguoichoi.matkhau.empty()){
            cout << YELLOW << "\t(!) Không được để trống mật khẩu !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
        } 
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 2)){
            cout << YELLOW << "\t(!) Mật khẩu không hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
        }
    } while(check2 && solansaimk < 3);
    if(solansaimk == 3) return false;
    cout << GREEN << "\t(*) Đăng nhập thành công !" << RESET << endl;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    return true;
}

bool xacthucdangnhapdangky(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi, int dangnhapdangky){
    if(dangnhapdangky == 1){
        if(!dangkytaikhoan(danhsachnguoichoi, thongtinnguoichoi)){
            cout << RED << "\t(!) Đăng ký tài khoản không thành công !" << RESET << endl;
            dungchuongtrinh();
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

void xoathongtintaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    if(kiemtrajsontrong(dd_danhsachtaikhoan)){
        cout << YELLOW << "\t(!) Chưa có tài khoản để xóa" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    int check1, solansaitk = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        check1 = 0;
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check1 = 1;
            solansaitk++;
            continue;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
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
            cout << YELLOW << "\t(!) Không được để trống mật khẩu !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
            continue;
        } 
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 2)){
            cout << YELLOW << "\t(!) Mật khẩu không hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            check2 = 1;
            solansaimk++;
        }
    } while(check2 && solansaimk < 3);
    if(solansaimk == 3) return;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    if(xoataikhoanjson(thongtinnguoichoi.tentaikhoan)){
        cout << GREEN << "\t(*) Xóa tài khoản " << thongtinnguoichoi.tentaikhoan << " thành công !" << RESET << endl;
        return;
    }
    cout << RED << "\t(*) Xóa tài khoản " << thongtinnguoichoi.tentaikhoan << " không thành công !" << RESET << endl;
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
    getch();
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
    const int somuc = 5;
    const char* menu[somuc] = {
        "Âm thanh", "Đăng ký", "Đăng nhập", "Xóa tài khoản", "Thoát",
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
                cout << "│"  << CYAN << " ▶ " << (i == 5 ? 0 : i + 1)
                     << " - " << noidung << string(khoang_trang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << (i == 5 ? 0 : i + 1)
                     << " - " << noidung << string(khoang_trang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = getch();
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
                    if(nguoichoi) {
                        chosaukhinhapthanhcong(2);
                        sanhchoi(danhsachnguoichoi, nguoichoi);
                    }
                }
                continue;
            } else if(chon == 3){
                cout << "\n[" << RED << chon << RESET << "] XÓA TÀI KHOẢN" << RESET << "\n\n";
                xoathongtintaikhoan(danhsachnguoichoi, thongtinnguoichoi);
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

void sanhchoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 8;
    const char* menu[somuc] = {
        "Tài xỉu 1xx", "Tài xỉu 3xx", "Đoán số A -> B", "Chẵn lẻ 0 -> 9", "Úp ngửa xu", "Nạp tiền", "Lịch sử chơi", "Đăng xuất", 
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
                cout << "│"  << CYAN << " ▶ " << (i == 8 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << (i == 8 ? 0 : i + 1)
                     << " - " << menu[i] << string(khoang_trang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = getch();
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
                cout << "\n[" << RED << chon << RESET << "] NẠP TIỀN" << RESET << "\n\n";
                napthemtien(danhsachnguoichoi, nguoichoi);
            } else if(chon == 6){
                cout << "\n[" << RED << chon << RESET << "] LỊCH SỬ CHƠI" << RESET << "\n\n";
                vector<LichSu> danhsachlichsu = tailichsujson(nguoichoi->tentaikhoan);
                if(danhsachlichsu.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
                else {
                    xuatbanglichsu(danhsachlichsu);
                }
            } else {
                // cái này thích thì bật (hơi ồn)
                //hieuungamthanh_mp3(dd_maymuanuadi);
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

void napthemtien(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(nguoichoi->sodu >= 100000000){
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
        else if(tiennap < 1000 || (nguoichoi->sodu + tiennap) > 100000000){
            cout << YELLOW << "\t\t(!) Tiền nạp hợp lệ trong khoảng 1000 -> " << dinhdangtien(100000000 - nguoichoi->sodu) << " VND" << RESET << endl;
            solansaitiennap++;
        } else tiennaphople = true;
    } while(!tiennaphople && solansaitiennap < 3);
    if(solansaitiennap == 3){
        cout << RED << "\t(*) Nạp tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    nguoichoi->sodu += tiennap;
    luudulieujson(danhsachnguoichoi);
    cout << GREEN << "\t(*) Nạp tiền thành công !" << RESET << endl;
}

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
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "t" || luachon == "tai" ? "Tài" : "Xỉu") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    hieuungamthanh_mp3(dd_lacxucxac, trangthaiamthanh); loadraketqua(5);
    int xucxac = rand() % 6 + 1;
    cout << YELLOW << "\tXúc xắc: " << RESET << "[" << xucxac << "]" << endl;
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matxucxac[xucxac][i], WHITE);
        cout << endl;
    } 
    cout << endl;
    string ketqua = (xucxac > 3 ? "Tài" : "Xỉu");
    cout << YELLOW << "\tKết quả: " << RESET << "[" << ketqua << "] - [" << xucxac << "]" << endl;
    if (
        ((luachon == "t" || luachon == "tai") && ketqua == "Tài") ||
        ((luachon == "x" || luachon == "xiu") && ketqua == "Xỉu")) {
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
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
    return;
}

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
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
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
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
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
    } while(!(luachon == "c" || luachon == "chan" || luachon == "l" || luachon == "le" || solansai == 3));
    if(solansai == 3) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannerchanle);
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
    string ketqua = (songaunhien % 2 == 0 ? "Chẵn" : "Lẻ");
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "] - [" << songaunhien << "]" << endl;
    if (
        ((luachon == "c" || luachon == "chan") && ketqua == "Chẵn") ||
        ((luachon == "l" || luachon == "le") && ketqua == "Lẻ")) {
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng" << RESET << "\n\tTiền thắng: " << YELLOW << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
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
    return;
}

void game_upngua(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    if(!kiemtrasodutaikhoan(nguoichoi)){
        cout << YELLOW << "\t\t(!) Số dư tài khoản không đủ ! Vui lòng nạp thêm" << RESET << endl;
        return;
    }
    string luachon; int tiencuoc = 0; int tongxucxac = 0; int solansai = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập lựa chọn (u/n): "; 
        getline(cin, luachon);
        if(!(luachon == "u" || luachon == "up" || luachon == "n" || luachon == "ngua")){
            cout << YELLOW << "\t\t(!) Vui lòng nhập u/up hoặc n/ngua" << RESET << endl;
            solansai++;
        } 
    } while(!(luachon == "u" || luachon == "up" || luachon == "n" || luachon == "ngua" || solansai == 3));
    if(solansai == 3) return;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    if(!nhaptiencuoc(tiencuoc, nguoichoi)){
        return;
    }
    nguoichoi->sodu -= tiencuoc;
    int phienhientai = phiencuoicung(nguoichoi->tentaikhoan) + 1;
    system("cls");
    inbanner(bannertungxu);
    cout << "\tSố dư sau khi cược: " << YELLOW << dinhdangtien(nguoichoi->sodu) << RESET << " VND" << endl;
    cout << YELLOW << "\tPhiên: " << RESET << phienhientai << 
            YELLOW << "\tCược: " << RESET << (luachon == "u" || luachon == "up" ? "Úp" : "Ngửa") <<
            YELLOW << "\tTiền cược: " << RESET << dinhdangtien(tiencuoc) << " VND" << endl;
    hieuungamthanh_mp3(dd_1dongxuroi, trangthaiamthanh); loadraketqua(5);
    int songaunhien = rand() % 2 + 1;
    cout << YELLOW << "\tMặt đồng xu: " << RESET << "[" << (songaunhien == 1 ? "Úp" : "Ngửa") << "]" << endl;
    cout << endl;
    for(int i = 0; i < 5; i++){
        ingiuamanhinh(matdongxu[songaunhien][i], ORANGE);
        cout << endl;
    }
    cout << endl;
    string ketqua = (((luachon == "u" || luachon == "up") && songaunhien == 1) || ((luachon == "n" || luachon == "ngua") && songaunhien == 2) ? "Thắng" : "Thua");
    cout << YELLOW << "\tKết quả:" << RESET << " [" << ketqua << "]" << endl;
    if((luachon == "u" || luachon == "up") && songaunhien == 1 ||
       (luachon == "n" || luachon == "ngua") && songaunhien == 2){
        int tienthang = tiencuoc * 1.9;
        nguoichoi->sodu += (int)tienthang;
        cout << GREEN << "\tChúc mừng bạn đã thắng " << RESET << "\n\tTiền thắng: " << YELLOW << dinhdangtien(tienthang) << RESET << " VND" << endl; 
        hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    } else {
        cout << RED << "\tChúc bạn may mắn lần sau" << RESET << "\n\tTiền thua: " << YELLOW << dinhdangtien(tiencuoc) << RESET << " VND"<< endl;
        hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
    }
    LichSu lichsu;
    lichsu.phien      = phienhientai;
    lichsu.trochoi    = "Upngua";
    lichsu.sodu       = nguoichoi->sodu;
    lichsu.tiencuoc   = tiencuoc;
    lichsu.luachon    = luachon;
    lichsu.tongdiem   = songaunhien;
    lichsu.ketqua     = ketqua;
    luulichsujson(nguoichoi->tentaikhoan, lichsu);
    luudulieujson(danhsachnguoichoi);
    return;
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
