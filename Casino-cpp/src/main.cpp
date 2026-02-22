//   _____          _             
//  / ____|        (_)            
// | |     __ _ ___ _ _ __   ___  
// | |    / _` / __| | '_ \ / _ \    Casino game C++ 
// | |___| (_| \__ \ | | | | (_) |   https://github.com/trgchinhh/casinogame-cpp
//  \_____\__,_|___/_|_| |_|\___/    Tác giả: Nguyễn Trường Chinh
//                    
// Bản quyền: MIT LICENSE 2026

/*******************************************************\
 * Hoàn thành ngày 19/02/2026                          *
 * Cấu trúc dữ liệu dựa trên danh sách liên kết kép    *
 * Gồm màu sắc chữ và hiệu ứng âm thanh                *
 * Lưu data và lịch sử ở các file định dạng JSON       *
 * Bảo mật bằng hash SHA256 (player) và RSA (admin)    *
 * Có thể viết thêm game trong folder src/game/        *
\*******************************************************/

#include "include.h"

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
    if(nguoichoi->sodu < sodunhonhat) return false;
    return true;
}

ThongTinPtr khoitaotaikhoan(ThongTinNguoiChoi& thongtinnguoichoi){
    ThongTinPtr tt = new ThongTinNguoiChoi();
    tt->sothutu = thongtinnguoichoi.sothutu;
    tt->tennguoichoi = thongtinnguoichoi.tennguoichoi;
    tt->tentaikhoan = thongtinnguoichoi.tentaikhoan;
    tt->matkhau = thongtinnguoichoi.matkhau;
    tt->makhoa6so = thongtinnguoichoi.makhoa6so;
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
    json data; file >> data; file.close();
    if(!data.contains(tentaikhoan)) return 0;
    if(!data[tentaikhoan].is_array()) return 0;
    if(data[tentaikhoan].empty()) return 0;
    return data[tentaikhoan].back()["phien"].get<int>();
}   

void intennguoichoi1(const ThongTinPtr nguoichoi){
    cout << "\t(*) Người chơi 1: " << YELLOW 
         << nguoichoi->tentaikhoan << RESET << endl;
}

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
        cout << RED << "\t(!) Đã hết lượt đăng ký tài khoản !" << RESET << endl;
        return false;
    }
    // nhap ten nguoi choi
    int solansainc = 0, solansaitk = 0, solansaimk = 0, solansaisd = 0, solansaima6so = 0;
    bool hoplenc = false, hopletk = false, hoplemk = false, hoplema6so = false;
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
        if(kiemtratentaikhoanadmin(thongtinnguoichoi.tennguoichoi)){
            cout << YELLOW << "\t\t(!) Vui lòng đặt tên khác !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansainc++;
            continue;
        }
        hoplenc = true;
    } while(!hoplenc && solansainc < solansaitoida);
    if(solansainc == solansaitoida) return false;
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
        if(kiemtratentaikhoanadmin(thongtinnguoichoi.tentaikhoan)){
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
    } while(!hopletk && solansaitk < solansaitoida);
    if(solansaitk == solansaitoida) return false;
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
    } while(!hoplemk && solansaimk < solansaitoida);
    if(solansaimk == solansaitoida) return false;

    // mã 6 số
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập mã 6 số: ";
        cin >> thongtinnguoichoi.makhoa6so;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập mã 6 số hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaima6so++;
            continue;
        }
        else if(thongtinnguoichoi.makhoa6so.length() < chieudaima6so 
             || thongtinnguoichoi.makhoa6so.length() > chieudaima6so){
            cout << YELLOW << "\t\t(!) Vui lòng nhập mã 6 số hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaima6so++;
            continue;
        } else hoplema6so = true;
    } while(!hoplema6so && solansaima6so < solansaitoida);
    if(solansaima6so == solansaitoida) return false;

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
    } while(!soduhople && solansaisd < solansaitoida);
    if(solansaisd == solansaitoida) return false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    thongtinnguoichoi.sothutu = sothutucuoicung(danhsachnguoichoi) + 1;
    luudulieumatjson(thongtinnguoichoi.tentaikhoan, thongtinnguoichoi.matkhau);
    thongtinnguoichoi.matkhau = mahoamatkhau(thongtinnguoichoi.matkhau);
    thongtinnguoichoi.makhoa6so = mahoamatkhau(thongtinnguoichoi.makhoa6so);
    ThongTinPtr tt = khoitaotaikhoan(thongtinnguoichoi);
    themcuoidanhsachtaikhoan(danhsachnguoichoi, tt);
    luudulieujson(danhsachnguoichoi);
    cout << GREEN << "\t(*) Tạo tài khoản thành công !" << RESET << endl;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    return true;
}

// che mật khẩu có ký tự (*)
string chematkhau(){
    string matkhau; char kytu;
    while ((kytu = _getch()) != '\r') { 
        if (kytu == '\b') { 
            if (!matkhau.empty()) {
                matkhau.pop_back();
                cout << "\b \b";
            }
        } else {
            matkhau += kytu;
            cout << "*";
            //cout << "●";
        }
    }
    cout << endl;
    return matkhau;
}

//che mật khẩu không ký tự (giống sudo password linux)
// string chematkhau() {
//     string matkhau;
//     char kytu;
//     while ((kytu = _getch()) != '\r') {
//         if (kytu == '\b') {
//             if (!matkhau.empty()) {
//                 matkhau.pop_back();
//             }
//         } else {
//             matkhau += kytu;
//         }
//     }
//     cout << endl;
//     return matkhau;
// }

bool dangnhaptaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    if(kiemtrajsontrong(dd_danhsachtaikhoan)){
        cout << YELLOW << "\t(!) Chưa có tài khoản ! Vui lòng đăng ký trước !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return false;
    }
    // phân quyền là user tránh lỗi login vào tk admin
    thongtinnguoichoi.phanquyen = Nguoichoi;
    // nhap ten tai khoan
    bool hopletentaikhoan = false; int solansaitentaikhoan = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if (kiemtratentaikhoanadmin(thongtinnguoichoi.tentaikhoan)) {
            thongtinnguoichoi.phanquyen = Admin;
            break;
        } else thongtinnguoichoi.phanquyen = Nguoichoi;
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaitentaikhoan++;
            continue;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaitentaikhoan++;
            continue;
        } hopletentaikhoan = true;
    } while(!hopletentaikhoan && solansaitentaikhoan < solansaitoida);
    if(solansaitentaikhoan == solansaitoida) return false;

    bool hoplematkhau; int solansaimatkhau = 0;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    do {
        hoplematkhau = 0;
        // nhập pass cho admin và player
        if(thongtinnguoichoi.phanquyen == Admin) 
            cout << "\t(?) [" << RED << "Admin" << RESET << "] Nhập mật khẩu: ";
        else 
            cout << "\t(?) [" << GREEN << "Player" << RESET << "] Nhập mật khẩu: ";
        thongtinnguoichoi.matkhau = chematkhau();
        if(thongtinnguoichoi.phanquyen == Admin) {
            // Cập nhật tên tài khoản Admin khi login 
            TentaikhoanAdmin = thongtinnguoichoi.tentaikhoan;
            if (!kiemtramatkhauadmin(thongtinnguoichoi.matkhau)) {
                cout << YELLOW << "\t\t(!) Mật khẩu Admin không hợp lệ !" << RESET << endl;
                hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
                solansaimatkhau++;
                continue;
            } else break;
        }
        if(thongtinnguoichoi.matkhau.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống mật khẩu !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaimatkhau++;
            continue;
        } 
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 2)){
            cout << YELLOW << "\t\t(!) Mật khẩu không hợp lệ !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaimatkhau++;
            continue;
        }
        hoplematkhau = true;
    } while(!hoplematkhau && solansaimatkhau < solansaitoida);
    if(solansaimatkhau == solansaitoida) return false;
    cout << endl;
    if (thongtinnguoichoi.phanquyen == Admin) {
        cout << GREEN << "\t(*) Đăng nhập Admin thành công !" << RESET << endl;
    } else cout << GREEN << "\t(*) Đăng nhập thành công !" << RESET << endl;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    return true;
}

// lưu mật khẩu mới
void luumatkhaumoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    ThongTinPtr ptr = danhsachnguoichoi.first;
    while(ptr != NULL){
        if(ptr->tentaikhoan == thongtinnguoichoi.tentaikhoan){
            ptr->matkhau = mahoamatkhau(thongtinnguoichoi.matkhau);
            break;
        }
        ptr = ptr->next;
    }
    luudulieujson(danhsachnguoichoi);
}

// thay đổi mật khẩu
bool quenmatkhau(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    // nhập tên tài khoản để load tài khoản lên
    bool hopletentaikhoan = false; int solansaitentaikhoan = 0;
    do {
        cout << "\t(?) Nhập tên tài khoản: ";
        getline(cin, thongtinnguoichoi.tentaikhoan);
        if(thongtinnguoichoi.tentaikhoan.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống tên đăng nhập !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaitentaikhoan++;
            continue;
        }
        if(!xacthucthongtin(danhsachnguoichoi, thongtinnguoichoi, 1)){
            cout << YELLOW << "\t\t(!) Tên đăng nhập không tồn tại !" << RESET << endl;
            hieuungamthanh_mp3(dd_dongudoanhai, trangthaiamthanh);
            solansaitentaikhoan++;
            continue;
        }
        hopletentaikhoan = 1;
    } while(!hopletentaikhoan && solansaitentaikhoan < solansaitoida);
    if(solansaitentaikhoan == solansaitoida) return false;   

    // lấy mã khóa 6 số từ danh sách liên kết đã load trong bộ nhớ
    ThongTinPtr ptr = danhsachnguoichoi.first;
    while(ptr != NULL){
        if(ptr->tentaikhoan == thongtinnguoichoi.tentaikhoan){
            thongtinnguoichoi.makhoa6so = ptr->makhoa6so;
            thongtinnguoichoi.matkhau = ptr->matkhau;
        }
        ptr = ptr->next;
    }

    string makhoa6so;
    bool makhoa6sohople = false; int solansaimakhoa6so = 0;
    // nhập mã 6 số xác thực
    do {
        cout << "\t(?) Nhập mã 6 số của bạn: ";
        makhoa6so = chematkhau();
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập mã khóa 6 số hợp lệ !" << RESET << endl;
            solansaimakhoa6so++;
            continue;
        }
        else if(makhoa6so.length() < 6 || makhoa6so.length() > 6 || makhoa6so.empty()){
            cout << YELLOW << "\t\t(!) Vui lòng nhập mã khóa 6 số hợp lệ !" << RESET << endl;
            solansaimakhoa6so++;
            continue;
        }else if(mahoamatkhau(makhoa6so) != thongtinnguoichoi.makhoa6so){
            cout << YELLOW << "\t\t(!) Mã 6 số của bạn không hợp lệ !" << RESET << endl;
            solansaimakhoa6so++;
            continue;
        } else makhoa6sohople = true;
    } while(!makhoa6sohople && solansaimakhoa6so < solansaitoida);
    if(solansaimakhoa6so == solansaitoida) return false;

    // nhập đúng thì cho đổi mật khẩu mới
    string matkhaumoi;
    bool matkhauhoplemoi = false; int solansaimatkhaumoi = 0;
    do {
        cout << ORANGE << "\t(?) Nhập mật khẩu mới: " << RESET;
        getline(cin, matkhaumoi);
        if(cin.fail()){
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << YELLOW << "\t\t(!) Vui lòng nhập mật khẩu mới hợp lệ !" << RESET << endl;
            solansaimatkhaumoi++;
            continue;
        } else if(mahoamatkhau(matkhaumoi) == thongtinnguoichoi.matkhau){
            cout << YELLOW << "\t\t(!) Mật khẩu mới không được trùng với mật khẩu hiện tại !" << RESET << endl;
            solansaimatkhaumoi++;
            continue;
        } else if(matkhaumoi.empty()){
            cout << YELLOW << "\t\t(!) Không được để trống mật khẩu !" << RESET << endl;
            solansaimatkhaumoi++;
            continue;
        } else matkhauhoplemoi = true;
    } while(!matkhauhoplemoi && solansaimatkhaumoi < solansaitoida);
    if(solansaimatkhaumoi == solansaitoida) return false;
    thongtinnguoichoi.matkhau = matkhaumoi;
    luumatkhaumoi(danhsachnguoichoi, thongtinnguoichoi);
    cout << GREEN << "\t(*) Đổi mật khẩu mới thành công !" << RESET << endl;
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
    if(dangnhapdangky == 3){
        if(!quenmatkhau(danhsachnguoichoi, thongtinnguoichoi)){
            cout << RED << "\t(!) Thay đổi mật khẩu không thành công !" << RESET << endl;
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
    int check2, solansaimk = 0;
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
    } while(check1 && solansaitk < solansaitoida);
    if(solansaitk == solansaitoida) {
        goto XOAKHONGTHANHCONG;
    }
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
    } while(check2 && solansaimk < solansaitoida);
    if(solansaimk == solansaitoida) return;
    hieuungamthanh_mp3(dd_dunglacontraicuata, trangthaiamthanh);
    if(xoataikhoanjson(thongtinnguoichoi.tentaikhoan)){
        cout << GREEN << "\t(*) Xóa tài khoản " << thongtinnguoichoi.tentaikhoan << " thành công !" << RESET << endl;
        return;
    }
    XOAKHONGTHANHCONG:
        cout << RED << "\t(!) Xóa tài khoản không thành công !" << RESET << endl;
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
        ttnc.makhoa6so    = i["makhoa6so"];
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
        i["makhoa6so"]    = p->makhoa6so;
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
    ingiuamanhinh(oss.str(), RESET);
    cout << endl;
}

// màu trắng đậm
// void xuatbangthongtinnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi) {
//     ingiuamanhinh("DANH SÁCH THÔNG TIN NGƯỜI CHƠI", YELLOW); cout << endl << endl;
//     ingiuamanhinh("┌─────┬─────────────────┬────────────────┬──────────────┬─────────────┐", WHITE); cout << endl;
//     ingiuamanhinh(WHITE "│" RED " STT " WHITE "│" RED " Tên người chơi  " WHITE "│" RED " Tên tài khoản  " WHITE "│" 
//                   RED "   Mật khẩu   " WHITE "│" RED "    Số dư    " WHITE "│", WHITE);  cout << endl;
//     ingiuamanhinh("├─────┼─────────────────┼────────────────┼──────────────┼─────────────┤", WHITE); cout << endl;
//     for (int i = 0; i < danhsachthongtinnguoichoi.size(); i++) {
//         xuatthongtinnguoichoi(danhsachthongtinnguoichoi[i], danhsachthongtinnguoichoi[i].sothutu);
//     }
//     ingiuamanhinh("└─────┴─────────────────┴────────────────┴──────────────┴─────────────┘", WHITE);
//     cout << endl;
// }

// màu reset (trắng mặc định của terminal)
void xuatbangthongtinnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi) {
    ingiuamanhinh("DANH SÁCH THÔNG TIN NGƯỜI CHƠI", YELLOW); cout << endl << endl;
    ingiuamanhinh("┌─────┬─────────────────┬────────────────┬──────────────┬─────────────┐", RESET); cout << endl;
    ingiuamanhinh(RESET "│" RED " STT " RESET "│" RED " Tên người chơi  " RESET "│" RED " Tên tài khoản  " 
                  RESET "│" RED "   Mật khẩu   " RESET "│" RED "    Số dư    " RESET "│", RESET); cout << endl;
    ingiuamanhinh("├─────┼─────────────────┼────────────────┼──────────────┼─────────────┤", RESET);
    cout << endl;
    for (int i = 0; i < danhsachthongtinnguoichoi.size(); i++) {
        xuatthongtinnguoichoi(
            danhsachthongtinnguoichoi[i],
            danhsachthongtinnguoichoi[i].sothutu
        );
    }
    ingiuamanhinh("└─────┴─────────────────┴────────────────┴──────────────┴─────────────┘", RESET); cout << endl;
}

void xuatlichsu(LichSu& lichsu, int stt) {
    int r_trochoi = do_rong_hien_thi_thuc(lichsu.trochoi);
    int r_luachon = do_rong_hien_thi_thuc(lichsu.luachon); 
    int r_ketqua  = do_rong_hien_thi_thuc(lichsu.ketqua);
    int pad_trochoi = (10 - r_trochoi) > 0 ? (10 - r_trochoi) : 0;
    int pad_luachon = (22 - r_luachon) > 0 ? (22 - r_luachon) : 0;
    int pad_ketqua  = (9 - r_ketqua) > 0 ? (9 - r_ketqua) : 0;
    ostringstream oss;
    oss << "│" << right << setw(5) << stt
        << "│" << right << setw(6) << lichsu.phien
        << "│" << string(pad_trochoi, ' ') << lichsu.trochoi
        << "│" << right << setw(12) << dinhdangtien(lichsu.tiencuoc)
        << "│" << string(pad_luachon, ' ') << lichsu.luachon
        << "│" << right << setw(6) << lichsu.tongdiem
        << "│" << string(pad_ketqua, ' ') << lichsu.ketqua
        << "│" << right << setw(13) << dinhdangtien(lichsu.sodu)
        << "│";
    string dong = oss.str();
    ingiuamanhinh(dong, RESET); 
    cout << endl;
}

void xuatbanglichsu(vector<LichSu>& danhsachlichsu){
    if(danhsachlichsu.empty()){
        cout << YELLOW << "\t(!) Chua co lich su choi !" << RESET << endl;
        return;
    }
    hieuungamthanh_mp3(dd_hdpethingonluon, trangthaiamthanh);
    ingiuamanhinh("LỊCH SỬ CHƠI 10 PHIÊN GẦN NHẤT", YELLOW); cout << endl << endl;
    ingiuamanhinh("┌─────┬──────┬──────────┬────────────┬──────────────────────┬──────┬─────────┬─────────────┐", RESET); cout << endl;
    ingiuamanhinh(RESET "│" RED " STT " RESET "│" RED " Phiên" RESET "│" RED " Trò chơi " RESET "│" RED " Tiền cược  " 
                  RESET "│" RED "         Chọn         " 
                  RESET "│" RED " Tổng " RESET "│" RED " Kết quả " RESET "│" RED "    Số dư    " RESET "│", RESET); cout << endl;
    ingiuamanhinh("├─────┼──────┼──────────┼────────────┼──────────────────────┼──────┼─────────┼─────────────┤", RESET); cout << endl;
    int stt = 1;
    for(auto i = danhsachlichsu.rbegin(); i != danhsachlichsu.rend(); i++){
        xuatlichsu(*i, stt++);
    }
    ingiuamanhinh("└─────┴──────┴──────────┴────────────┴──────────────────────┴──────┴─────────┴─────────────┘", RESET); cout << endl;
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
    } while(!nhaphople && solansaitentaikhoan < solansaitoida);
    if(solansaitentaikhoan == solansaitoida){
        cout << RED << "\t(!) Tìm lịch sừ người chơi không thành công !" << RESET << endl;
        return;
    }
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

void hienthongtinadmin(const string& tentaikhoanadmin){
    const int chieurong = 31;
    string taikhoan = "(-) Tài khoản: ";
    cout << "┌────────────────────────────┐\n";
    cout << "│" << YELLOW << taikhoan << RESET << UNDERLINE << tentaikhoanadmin 
         << NO_UNDERLINE << string(chieurong - taikhoan.length() - tentaikhoanadmin.length(), ' ') << "│\n";
    cout << "└────────────────────────────┘\n";
}

void hiensodunguoichoi(ThongTinPtr& nguoichoi){
    const int chieurong = 31;
    string tnc = nguoichoi->tennguoichoi;
    string ttk = nguoichoi->tentaikhoan;
    string sd  = dinhdangtien(nguoichoi->sodu);
    string tennguoichoi = "(-) Đại gia: ";
    string taikhoan = "(-) Tài khoản: ";
    string sodu = "(-) Số dư: ";
    cout << "┌────────────────────────────┐\n";
    cout << "│" << YELLOW << tennguoichoi << RESET << UNDERLINE << tnc 
         << NO_UNDERLINE << string(chieurong - tennguoichoi.length() - tnc.length(), ' ') << "│\n";  
    cout << "│" << YELLOW << taikhoan << RESET << UNDERLINE << ttk 
         << NO_UNDERLINE << string(chieurong - taikhoan.length() - ttk.length(), ' ') << "│\n";
    cout << "│" << YELLOW << sodu << RESET << UNDERLINE << sd 
         << NO_UNDERLINE << " (VND)" << string(chieurong - sodu.length() - sd.length() - 6, ' ') << "│\n";
    cout << "└────────────────────────────┘\n";
}

void trangchu(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi){
    const int somuc = 6;
    const char* menu[somuc] = {
        "Âm thanh", 
        "Hướng dẫn", 
        "Đăng ký", 
        "Đăng nhập", 
        "Quên mật khẩu", 
        "Thoát game",
    };
    int chon = 0; char phim;
    //hieuungamthanh_wav(dd_lindachaocanha, trangthaiamthanh);
    while(1){
        system("cls");
        taidulieujson(danhsachnguoichoi);
        inbanner(bannertrangchu);
        cout << "┌─────────── " << RESET << RED << "GỢI Ý" << RESET << " ────────────┐" << endl;
        cout << "│ " << YELLOW << "▶ " << RESET << "Dùng phím " << RED << "↑ ↓" << RESET << " để di chuyển │" << RESET << endl;
        cout << "│ " << YELLOW << "▶ " << RESET << "Dùng phím " << RED << "Enter" << RESET << " để chọn    │" << RESET << endl;
        cout << "└──────────────────────────────┘" << RESET << endl;
        cout << endl;

        const int dorongmenu = 19;
        cout << "┌──────── " << RED << "MENU" << RESET << " ────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string noidung;
            if (i == 0) {
                ostringstream oss;
                oss << setw(1) << right << (i + 1) 
                    << "/ Âm thanh: "
                    << (trangthaiamthanh ? GREEN "Bật   " RESET : RED "Tắt   " RESET);
                noidung = oss.str();
            } 
            else {
                ostringstream oss;
                oss << setw(1) << right << (i + 1) 
                    << "/ " << menu[i];
                noidung = oss.str();
            }
            int chieudaidong = doronghienthi(noidung.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if (khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " 
                     << noidung << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " 
                     << noidung << string(khoangtrang, ' ')  << "│" << endl;
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
                system("cls");
                //ingiuamanhinh("HƯỚNG DẪN CÁCH CHƠI", CYAN);
                inbanner(bannerhuongdan);
                cout << noidunghuongdan << endl;
                //ingiuamanhinh("CHÚC BẠN CHƠI GAME VUI VẺ", CYAN);
            } else if(chon == 2){
                cout << "\n[" << RED << chon + 1 << RESET << "] ĐĂNG KÝ TÀI KHOẢN" << RESET << "\n\n";
                xacthucdangnhapdangky(danhsachnguoichoi, thongtinnguoichoi, 1);
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] ĐĂNG NHẬP TÀI KHOẢN" << RESET << "\n\n";
                if(xacthucdangnhapdangky(danhsachnguoichoi, thongtinnguoichoi, 2)){
                    ThongTinPtr nguoichoi = timtaikhoan(
                        danhsachnguoichoi,
                        thongtinnguoichoi.tentaikhoan
                    );
                    chosaukhinhapthanhcong(sogiaycho);
                    // Phân quyền vào sảnh người chơi và admin
                    if(thongtinnguoichoi.phanquyen == Nguoichoi){
                        sanhchoi(danhsachnguoichoi, nguoichoi);
                    } else {
                        sanhadmin(danhsachnguoichoi);
                    }
                }
                continue;
            }else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] THAY ĐỔI MẬT KHẨU" << RESET << "\n\n";
                xacthucdangnhapdangky(danhsachnguoichoi, thongtinnguoichoi, 3);
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

        const int dorongmenu = 19;
        cout << "┌──────── " << RED << "MENU" << RESET << " ────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = do_rong_hien_thi_thuc(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└──────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon + 1 << RESET << "] NẠP TIỀN" << RESET << "\n\n";
                naptienchonguoichoi(danhsachnguoichoi);
            } else if(chon == 1){
                cout << "\n[" << RED << chon + 1<< RESET << "] TRỪ TIỀN" << RESET << "\n\n";
                trutiennguoichoi(danhsachnguoichoi);
            } else if(chon == 2){
                cout << "\n[" << RED << chon + 1<< RESET << "] XEM THÔNG TIN" << RESET << "\n\n";
                vector<ThongTinNguoiChoi> danhsachthongtinnguoichoi = taithongtinnguoichoi(danhsachnguoichoi);
                if(danhsachthongtinnguoichoi.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
                else {
                    xuatbangthongtinnguoichoi(danhsachthongtinnguoichoi);
                }
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] XEM LỊCH SỬ" << RESET << "\n\n";
                xemlichsunguoichoi(danhsachnguoichoi);
            } else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] XÓA TÀI KHOẢN" << RESET << "\n\n";
                xoataikhoannguoichoi(danhsachnguoichoi);
            } else {
                cout << "\n[" << RED << chon + 1 << RESET << "] ĐĂNG XUẤT" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

// sảnh con chứa game xóc xóc 
void sanh_gamexocxoc(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 6;
    const char* menu[somuc] = {
        "Tài xỉu 1xx", 
        "Tài xỉu 3xx", 
        "Úp ngửa xu",
        "Xóc dĩa",
        "Lắc bầu cua",
        "Quay lại", 
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannergamexocxoc);
        taidulieujson(danhsachnguoichoi);
        nguoichoi = timtaikhoan(danhsachnguoichoi, nguoichoi->tentaikhoan);
        hiensodunguoichoi(nguoichoi);
        cout << endl;

        const int dorongmenu = 21;
        cout << "┌───────── " << RED << "GAME" << RESET << " ─────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = doronghienthi(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└────────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon + 1 << RESET << "] TÀI XỈU 1 XX" << RESET << "\n\n";
                game_taixiu1xx(danhsachnguoichoi, nguoichoi);
            }else if(chon == 1){
                cout << "\n[" << RED << chon + 1 << RESET << "] TÀI XỈU 3 XX" << RESET << "\n\n";
                game_taixiu3xx(danhsachnguoichoi, nguoichoi);
            } else if(chon == 2){
                cout << "\n[" << RED << chon + 1 << RESET << "] XU ÚP NGỬA" << RESET << "\n\n";
                game_upngua(danhsachnguoichoi, nguoichoi);
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] XÓC DĨA" << RESET << "\n\n";
                game_xocdia(danhsachnguoichoi, nguoichoi);
            } else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] LẮC BẦU CUA" << RESET << "\n\n";
                game_baucua(danhsachnguoichoi, nguoichoi);
            } else {
                cout << "\n[" << RED << chon + 1 << RESET << "] QUAY LẠI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

// sảnh con chứa game bài 
void sanh_gamebai(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 3;
    const char* menu[somuc] = {
        "Ba cào", 
        "Xì dách",
        "Quay lại", 
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannergamebai);
        taidulieujson(danhsachnguoichoi);
        nguoichoi = timtaikhoan(danhsachnguoichoi, nguoichoi->tentaikhoan);
        hiensodunguoichoi(nguoichoi);
        cout << endl;

        const int dorongmenu = 21;
        cout << "┌───────── " << RED << "GAME" << RESET << " ─────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = doronghienthi(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└────────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon + 1 << RESET << "] BA CÀO" << RESET << "\n\n";
                game_bacao(danhsachnguoichoi, nguoichoi);
            } else if(chon == 1){
                cout << "\n[" << RED << chon + 1 << RESET << "] XÌ DÁCH" << RESET << "\n\n";
                game_xidach(danhsachnguoichoi, nguoichoi);
            } else {
                cout << "\n[" << RED << chon + 1 << RESET << "] QUAY LẠI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

// sảnh con chứa game may rủi
void sanh_gamemayrui(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 6;
    const char* menu[somuc] = {
        "Đoán dài ngắn",
        "Đoán 3/7 màu", 
        "Đoán số A -> B",
        "Chẵn lẻ 0 -> 9", 
        "Kéo búa bao", 
        "Quay lại", 
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannergamemayrui);
        taidulieujson(danhsachnguoichoi);
        nguoichoi = timtaikhoan(danhsachnguoichoi, nguoichoi->tentaikhoan);
        hiensodunguoichoi(nguoichoi);
        cout << endl;

        const int dorongmenu = 21;
        cout << "┌───────── " << RED << "GAME" << RESET << " ─────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = doronghienthi(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└────────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n" << RED << chon + 1 << RESET << "] ĐOÁN DÀI NGẮN" << RESET << "\n\n";
                game_daingan(danhsachnguoichoi, nguoichoi);
            } else if(chon == 1){
                cout << "\n" << RED << chon + 1 << RESET << "] ĐOÁN MÀU 7 SẮC" << RESET << "\n\n";
                game_doanmau(danhsachnguoichoi, nguoichoi);
            } else if(chon == 2){
                cout << "\n[" << RED << chon + 1 << RESET << "] ĐOÁN SỐ" << RESET << "\n\n";
                game_doanso(danhsachnguoichoi, nguoichoi);
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] SỐ CHẴN LẺ" << RESET << "\n\n";
                game_chanle(danhsachnguoichoi, nguoichoi);
            }  else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] KÉO BÚA BAO" << RESET << "\n\n";
                game_keobuabao(danhsachnguoichoi, nguoichoi);
            } else {
                cout << "\n[" << RED << chon + 1 << RESET << "] QUAY LẠI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

void sanh_game2nguoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 6;
    const char* menu[somuc] = {
        "Ném 1 xúc xắc",
        "Ném 3 xúc xắc",
        "Ba cào", 
        "Xì dách",  
        "So bài 1 lá",
        "Quay lại", 
    };
    int chon = 0;
    char phim;
    hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
    while(1){
        system("cls");
        inbanner(bannergame2nguoi);
        taidulieujson(danhsachnguoichoi);
        nguoichoi = timtaikhoan(danhsachnguoichoi, nguoichoi->tentaikhoan);
        hiensodunguoichoi(nguoichoi);
        cout << endl;

        const int dorongmenu = 21;
        cout << "┌───────── " << RED << "GAME" << RESET << " ─────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = doronghienthi(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└────────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n" << RED << chon + 1 << RESET << "] NÉM 1 XÚC XẮC" << RESET << "\n\n";
                game_nem1xucxac(danhsachnguoichoi, nguoichoi);
            } else if(chon == 1){
                cout << "\n" << RED << chon + 1 << RESET << "] NÉM 3 XÚC XẮC" << RESET << "\n\n";
                game_nem3xucxac(danhsachnguoichoi, nguoichoi);
            } else if(chon == 2){
                cout << "\n" << RED << chon + 1 << RESET << "] BA CÀO 2 NGƯỜI" << RESET << "\n\n";
                game_bacao2nguoi(danhsachnguoichoi, nguoichoi);
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] XÌ DÁCH 2 NGƯỜI" << RESET << "\n\n";
                game_xidach2nguoi(danhsachnguoichoi, nguoichoi);
            } else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] SO BÀI 1 LÁ" << RESET << "\n\n";
                game_sobai1la2nguoi(danhsachnguoichoi, nguoichoi);
            } else {
                cout << "\n[" << RED << chon + 1 << RESET << "] QUAY LẠI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

void sanhchoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi){
    const int somuc = 6;
    const char* menu[somuc] = {
        "Game xóc xóc",
        "Game bài",
        "Game may rủi",
        "Game 2 người",
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

        const int dorongmenu = 21;
        cout << "┌───────── " << RED << "GAME" << RESET << " ─────────┐" << endl;
        for (int i = 0; i < somuc; i++) {
            string so = to_string(i + 1);
            ostringstream oss;
            oss << setw(1) << right << (i + 1) << " - " << menu[i];
            string dong = oss.str();
            int chieudaidong = doronghienthi(dong.c_str());
            int khoangtrang = dorongmenu - chieudaidong;
            if(khoangtrang < 0) khoangtrang = 0;
            if (i == chon){
                cout << "│"  << CYAN << " ▶ " << dong
                     << string(khoangtrang, ' ') << RESET << "│" << endl;
            }
            else{
                cout << "│   " << dong
                     << string(khoangtrang, ' ')  << "│" << endl;
            }
        }
        cout << "└────────────────────────┘" << endl;
        phim = _getch();
        if(phim == 72) chon = (chon - 1 + somuc) % somuc;
        else if(phim == 80) chon = (chon + 1) % somuc;
        else if(phim == 13) {
            hieuungamthanh_mp3(dd_dichuyenmenu, trangthaiamthanh);
            if(chon == 0){
                cout << "\n[" << RED << chon + 1 << RESET << "] GAME XÓC XÓC" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                sanh_gamexocxoc(danhsachnguoichoi, nguoichoi);
                continue;
            } else if(chon == 1){
                cout << "\n[" << RED << chon + 1 << RESET << "] GAME BÀI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                sanh_gamebai(danhsachnguoichoi, nguoichoi);
                continue;
            } else if(chon == 2){
                cout << "\n[" << RED << chon + 1 << RESET << "] GAME MAY RỦI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                sanh_gamemayrui(danhsachnguoichoi, nguoichoi);
                continue;
            } else if(chon == 3){
                cout << "\n[" << RED << chon + 1 << RESET << "] GAME 2 NGƯỜI" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                sanh_game2nguoi(danhsachnguoichoi, nguoichoi);
                continue;
            } else if(chon == 4){
                cout << "\n[" << RED << chon + 1 << RESET << "] LỊCH SỬ CHƠI" << RESET << "\n\n";
                vector<LichSu> danhsachlichsu = tailichsujson(nguoichoi->tentaikhoan);
                if(danhsachlichsu.empty()) cout << YELLOW << "\t(!) Chưa có lịch sử chơi !" << RESET << endl;
                else {
                    xuatbanglichsu(danhsachlichsu);
                }
            } else {
                // cái này thích thì bật (hơi ồn)
                //hieuungamthanh_mp3(dd_maymuanuadi, trangthaiamthanh);
                cout << "\n[" << RED << chon + 1 << RESET << "] ĐĂNG XUẤT" << RESET << "\n\n";
                chosaukhinhapthanhcong(sogiaycho);
                return;
            }
            dungchuongtrinh();
        }
    }
}

// void loadraketqua(int sogiay){
//     const char kytu[] = {'/', '-', '\\', '|'};
//     int vitri = 0;
//     while(sogiay > 0){
//         cout << "\r\t(" << RED << kytu[vitri] << RESET << ") Vui lòng chờ kết quả trong giây lát...";  
//         vitri = (vitri + 1) % 4;
//         Sleep(1000);
//         sogiay--;
//     }
//     cout << endl;
// }

// load spinner xoay nhanh hơn
void loadraketqua(int sogiay){
    const char kytu[] = {'/', '-', '\\', '|'};
    int vitri = 0;
    // độ trễ xoay spinner
    const int dotre = 100;    
    const int tickpersec = 1000 / dotre;
    int tongtick = sogiay * tickpersec;
    for (int tick = 0; tick < tongtick; tick++){
        cout << "\r\t(" << RED << kytu[vitri] << RESET
             << ") Vui lòng chờ kết quả trong giây lát...";
        vitri = (vitri + 1) % 4;
        Sleep(dotre);
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
        else if(tiencuoc < sodunhonhat){
            cout << YELLOW << "\t\t(!) Tiền cược phải lớn hơn " << dinhdangtien(sodunhonhat) << " VND" << RESET << endl;
            solansaitiencuoc++;
        }
        else if(tiencuoc > nguoichoi->sodu) {
            cout << YELLOW << "\t\t(!) Mức cược hợp lệ 1000 - " << dinhdangtien(nguoichoi->sodu) << " VND"<< RESET << endl;
            solansaitiencuoc++;
        } else tiencuochople = true;
    } while(!tiencuochople && solansaitiencuoc < solansaitoida);
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
    } while(!tentaikhoanhople && solansaitentaikhoan < solansaitoida);
    if(solansaitentaikhoan == solansaitoida){
        cout << RED << "\t(!) Nạp tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    cout << "\t └> [" << RED << tentaikhoan << RESET << "] Số dư hiện tại: " << YELLOW << dinhdangtien(nguoiduocnap->sodu) << RESET << " VND" << endl; 
    if(nguoiduocnap->sodu >= sodulonnhat){
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
        else if(tiennap < sodunhonhat || (nguoiduocnap->sodu + tiennap) > sodulonnhat){
            cout << YELLOW << "\t\t(!) Tiền nạp hợp lệ trong khoảng 1000 -> " 
                 << dinhdangtien(sodulonnhat - nguoiduocnap->sodu) << " VND" << RESET << endl;
            solansaitiennap++;
        } else tiennaphople = true;
    } while(!tiennaphople && solansaitiennap < solansaitoida);
    if(solansaitiennap == solansaitoida){
        cout << RED << "\t(!) Nạp tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    nguoiduocnap->sodu += tiennap;
    luudulieujson(danhsachnguoichoi);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\t │" << GREEN "\t(*)" << RESET << " Đã nạp thành công " << YELLOW << dinhdangtien(tiennap) 
         << RESET << " VND vào tài khoản: " << RESET
         << nguoiduocnap->tentaikhoan << "\n\t └> [" << RED << tentaikhoan 
         << RESET << "] Số dư mới: " << YELLOW << dinhdangtien(nguoiduocnap->sodu) << RESET << " VND" << endl;
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
    } while(!tentaikhoanhople && solansaitentaikhoan < solansaitoida);
    if(solansaitentaikhoan == solansaitoida){
        cout << RED << "\t(!) Trừ tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    cout << "\t └> [" << RED << tentaikhoan 
         << RESET << "] Số dư hiện tại: " << YELLOW << dinhdangtien(nguoibitru->sodu) << RESET << " VND" << RESET << endl; 
    if(nguoibitru->sodu < sodunhonhat){
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
        else if(tientru < sodunhonhat || tientru > nguoibitru->sodu){
            cout << YELLOW << "\t\t(!) Tiền nạp hợp lệ trong khoảng 1000 -> "
                 << dinhdangtien(nguoibitru->sodu) << " VND" << RESET << endl;
            solansaitientru++;
        } else tientruhople = true;
    } while(!tientruhople && solansaitientru < solansaitoida);
    if(solansaitientru == solansaitoida){
        cout << RED << "\t(!) Trừ tiền không thành công !" << RESET << endl;
        hieuungamthanh_mp3(dd_giongcuoithay3, trangthaiamthanh);
        return;
    }
    nguoibitru->sodu -= tientru;
    luudulieujson(danhsachnguoichoi);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\t │" << GREEN << "\t(*)" << RESET << " Đã trừ " << YELLOW << dinhdangtien(tientru) 
         << RESET << " VND vào tài khoản: " << RESET 
         << nguoibitru->tentaikhoan << "\n\t └> [" << RED << tentaikhoan 
         << RESET << "] Số dư mới: " << YELLOW << dinhdangtien(nguoibitru->sodu) << RESET << " VND" << endl;
}

// danh sách game flag 
FlagGame games[soluonggameflag] = {
    {"nem1xx", game_nem1xucxac_flag},
    {"nem3xx", game_nem3xucxac_flag},
    {"bacao",  game_bacao2nguoi_flag},
    {"xidach", game_xidach2nguoi_flag},
    {"sobai",  game_sobai1la2nguoi_flag}
};

int kiemtraflag(char* flag){
     for(int i = 0; i < soluonggameflag; i++){
        if(strcmp(flag, games[i].game) == 0)
            return i;
    }
    return -1;
}

void huongdanflag(){
    cout << RED << "Vui lòng nhập đúng tên game !" << RESET << endl; 
    cout << "Các game hợp lệ: [";
    for(int i = 0; i < soluonggameflag -1; i++){
        cout << YELLOW << games[i].game << RESET << ", ";
    }
    cout << YELLOW << games[soluonggameflag -1].game << RESET;
    cout << "]";
}

___TruongChinh___(int argc, char** argv) {
    SetConsoleCP(CP_UTF8);                          // hiện được tiếng việt và ký tự đặc biệt
    SetConsoleOutputCP(CP_UTF8);                    // này cũng vậy 
    ancontrochuot(true);                            // ẩn con trỏ chuột
    srand(time(NULL) ^ clock());                    // khởi tạo random cho game 

    // Phần ưu tiên kiểm tra dành cho flag game
    if(argc > 1){
        int vitrigameflag = kiemtraflag(argv[1]);
        if(vitrigameflag == -1){
            huongdanflag();
            ancontrochuot(false);
            return -1;
        }
        cout << endl;
        games[vitrigameflag].tenhamgame();
        ancontrochuot(false);
        return 0;
    }                       

    // Phần chạy chương trình chính 
    SetConsoleTitleA("Casino Game");                // tiêu đề terminal        
    DanhSachNguoiChoi danhsachnguoichoi;            
    khoitaolist(danhsachnguoichoi);
    taidulieujson(danhsachnguoichoi);
    ThongTinNguoiChoi thongtinnguoichoi;
    trangchu(danhsachnguoichoi, thongtinnguoichoi);
    ancontrochuot(false);
    return 0;
}

