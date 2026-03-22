// Header chính 

///////////////////////////////////
//   XÂY DỰNG GAME ĐA NỀN TẢNG   //
///////////////////////////////////

#pragma once

#ifdef _WIN32               // Nếu là Windows 
    #define NOMINMAX
    #include <windows.h>
    #include <conio.h>
    #include <mmsystem.h>       // phát hiệu ứng âm thanh
#else                       // Nếu là Linux hoặc HDH khác
    #include <sys/ioctl.h>
    #include <unistd.h> 
    #include <termios.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <random>
#include <chrono>
#include <thread>
#include "props.h"          // chứa mặt xúc xắc và số
#include "banner.h"         // chứa nhiều banner 
#include "dothd.h"          // hàm ẩn file mật
#include "admin.h"          // phân quyền và thông tin admin
#include "json.hpp"         // dùng định dạng json 
#include "picosha2.h"       // dùng hash sha256
#include "instruct.h"       // hướng dẫn cách chơi
#include "info.h"           // thông tin game

// Định nghĩa tên hàm main
#define ___CasinoGames___ signed main
#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace chrono;
using namespace this_thread;
using json = nlohmann::ordered_json;

#define SoTaiKhoanToiDa 100           // đăng ký tối đa 100 tài khoản

struct ThongTinNguoiChoi {
    int sothutu;                      // số thứ tự
    string tennguoichoi;              // tên người chơi (dùng như nickname) 
    string tentaikhoan;               // tên tài khoản (đăng ký)
    string matkhau;                   // mật khẩu
    string makhoa6so;                 // mã khóa 6 số (phải nhớ khi quên mật khẩu)
    int sodu;                         // số dư (giới hạn 100.000.000)
    int sotiendachoi = 0;             // tổng số tiền đã chơi mọi game
    int sotienthang = 0;              // tống số tiền thắng chơi mọi game
    int levelnguoichoi = 0;           // level người chơi tính theo số tiền thắng 
    PhanQuyen phanquyen = Nguoichoi;  // quyền người chơi (admin - player) 
    ThongTinNguoiChoi* next;          // con trỏ next 
    ThongTinNguoiChoi* prev;          // con trỏ prev
    int mauchude;                     // màu chủ đề đã chọn (nếu chưa thì là màu mặc định)
};
typedef ThongTinNguoiChoi* ThongTinPtr;

struct DS_ThongTinNguoiChoi {
    ThongTinPtr first;
    ThongTinPtr last;
};
typedef DS_ThongTinNguoiChoi DanhSachNguoiChoi;

struct LichSu {
    int phien;        // phiên game
    string trochoi;   // tên game
    int sodu;         // số dư 
    int tiencuoc;     // tiền cược
    string luachon;   // lựa chọn
    int tongdiem;     // tổng điểm 
    string ketqua;    // kết quả 
};

/*
- Game flag là gì ?
  -> Nó giống như flag khi các bạn dùng các chương trình như cmatrix (linux)
  hoặc rs-matrix cần có flag là các cụm như:

    -c/--colour:       màu sắc
    -h/--help:         thể hiện xem lệnh
    -d/--direction:    dường dẫn
    -V/--version:      phiên bản
    ...

  ngay sau chương trình chính

  * Game flag truyền tham số [tên game] vào sau tên chương trình
  VD: Casino.exe bacao hoặc Casino.exe "bacao"
  Các game flag hợp lệ bao gồm: [nem1xx, nem3xx, bacao, xidach, sobai]
  Có thể phát triển thêm
*/

struct FlagGame {
    const char* game;
    void (*tenhamgame)();
};

// số lượng game flag
const int soluonggameflag           = 5;

// Các đường dẫn 
// Lưu dữ liệu
const string dd_danhsachtaikhoan    = "..//data/player/taikhoan.json";
const string dd_danhsachlichsu      = "..//data/player/lichsugame.json";
// Lưu âm thanh
const string dd_lindachaocanha      = "..//sound/linda_chao_ca_nha.wav";
const string dd_1dongxuroi          = "..//sound/1_dong_xu_roi.mp3";
const string dd_conginuadau         = "..//sound/con_gi_nua_dau.mp3";
const string dd_dongudoanhai        = "..//sound/do_ngu_do_an_hai.mp3";
const string dd_dunglacontraicuata  = "..//sound/dung_la_con_trai_cua_ta.mp3";
const string dd_giongcuoithay3      = "..//sound/giong_cuoi_thay_3.mp3";
const string dd_hdpethingonluon     = "..//sound/hdpe_thi_ngon_luon.mp3";
const string dd_lacxucxac           = "..//sound/lac_xuc_xac.mp3";
const string dd_nhieudongxuroi      = "..//sound/nhieu_dong_xu_roi.mp3";
const string dd_maymuanuadi         = "..//sound/mua_nua_di.mp3";
const string dd_dichuyenmenu        = "..//sound/chon_menu.mp3";
const string dd_xinvinhbietcu       = "..//sound/xin_vinh_biet_cu.wav";

// Các giá trị bắt buộc 
const int levelthapnhat             = 0;             // level thấp nhất cho phép
const int levelcaonhat              = 10;            // level cao nhất cho phép
const int sodunhonhat               = 1000;          // số dư nhỏ nhất cho phép
const int sodulonnhat               = 100000000;     // số dư lớn nhất cho phép
const int phidungaigoiy             = 5000;          // phí dùng AI mỗi lượt
const int sogiaycho                 = 2;             // số giây load khi đăng nhập / xuất 
const int solansaitoida             = 3;             // số lần sai tối đa
const int chieudaima6so             = 6;             // chiều dài mã khóa 6 số
static bool trangthaiamthanh        = false;         // trạng thái bật tắt âm thanh (mới vào luôn tắt)
static bool trangthaiAIgoiy         = false;         // trạng thái bật tắt AI gợi ý kết quả
static bool trangthaicontrochuot    = false;         // trạng thái bật tắt con trỏ chuột
static string mauchude              = CYAN;          // màu chủ đề  
static int thutumautruoc            = 0;             // màu chủ đề khi đã setup (không lưu DB) 

// Dùng cho theme
const char* mangmau[] = {
    CYAN, RESET, RED, GREEN, YELLOW, BLUE, MAGENTA, ORANGE, INDIGO,
    VIOLET, GRAY, PINK, LIGHT_BLUE, LIME, TEAL, GOLD, SALMON, SKY, MINT, LAVENDER, PEACH,
    NEON_GREEN, NEON_BLUE, NEON_PINK, NEON_CYAN, NEON_ORANGE,
    SOFT_RED, SOFT_GREEN, SOFT_YELLOW, SOFT_BLUE, SOFT_PURPLE, SOFT_CYAN,
    PASTEL_PINK, PASTEL_GREEN, PASTEL_BLUE, PASTEL_PURPLE, PASTEL_YELLOW,
    BLOOD_RED, FIRE_ORANGE, DEEP_BLUE, DARK_GREEN, GOLDEN,
    DARK_BLUE, DARK_RED, DARK_PURPLE, DARK_CYAN, DARK_GRAY,
    AQUA, TURQUOISE, CORAL, ROSE, FUCHSIA,
    ELECTRIC_BLUE, LASER_GREEN, HOT_PINK, CYBER_YELLOW, MATRIX_GREEN,
    SAND, OLIVE, FOREST_GREEN, SEA_BLUE, SUNSET
};
// tên theme
const char* tenmau[] = {
    "CYAN", "DEFAULT", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "ORANGE", "INDIGO",
    "VIOLET", "GRAY", "PINK", "LIGHT_BLUE", "LIME", "TEAL", "GOLD", "SALMON", "SKY", "MINT", "LAVENDER", "PEACH",
    "NEON GREEN", "NEON BLUE", "NEON PINK", "NEON CYAN", "NEON ORANGE",
    "SOFT RED", "SOFT GREEN", "SOFT YELLOW", "SOFT BLUE", "SOFT PURPLE", "SOFT CYAN",
    "PASTEL PINK", "PASTEL GREEN", "PASTEL BLUE", "PASTEL PURPLE", "PASTEL YELLOW",
    "BLOOD RED", "FIRE ORANGE", "DEEP BLUE", "DARK GREEN", "GOLDEN",
    "DARK_BLUE", "DARK_RED", "DARK_PURPLE", "DARK_CYAN", "DARK_GRAY",
    "AQUA", "TURQUOISE", "CORAL", "ROSE", "FUCHSIA",
    "ELECTRIC_BLUE", "LASER_GREEN", "HOT_PINK", "CYBER_YELLOW", "MATRIX_GREEN",
    "SAND", "OLIVE", "FOREST_GREEN", "SEA_BLUE", "SUNSET"
};

// NGUYÊN MẪU HÀM

// Admin 
void sanhadmin(DanhSachNguoiChoi& danhsachnguoichoi);
void hienthongtinadmin(const string& tenadmin);
void xuatbangthongtinnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi);
void xemlichsunguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void xuatthongtinxephang(ThongTinNguoiChoi& thongtinnguoichoi, int top);
void xuatbangxephangnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi, ThongTinPtr nguoichoi = NULL);
void xoataikhoannguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void naptienchonguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void trutiennguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);

// Người chơi
int tinhlevelnguoichoi(ThongTinPtr& nguoichoi);
string tinhranknguoichoi(int level);
int sothutucuoicung(DanhSachNguoiChoi& danhsachnguoichoi);
int phiencuoicung(string& tentaikhoan);
int laychieurongterminal();
int laychieucaoterminal();
int doronghienthi(const char* s);
int doronghienthithuc(const string& str);
int dodaihienthiutf8(const string& s);
int docphim();
int xoaansinumber(string s);

void mogithub(); // Mở repo github bằng trình duyệt
void sleep(int sogiaymili); // Delay 
void clear(); // Xóa màn hình  
bool xoataikhoanjson(string& tentaikhoan);
bool kiemtrasodutaikhoan(ThongTinPtr& nguoichoi);
bool kiemtrarongdanhsach(DanhSachNguoiChoi& danhsachnguoichoi);
bool kiemtrajsontrong(string duongdanjson);
bool xacthucthongtin(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi, int thongtin);
bool dangkytaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);
bool dangnhaptaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);
bool xacthucdangnhapdangky(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi, int dangnhapdangky);
bool nhaptiencuoc(int& tiencuoc, ThongTinPtr& nguoichoi);
// viết hàm quên mật khẩu (nhập mã 6 số)
bool quenmatkhau(DanhSachNguoiChoi& danhsachnguoichoi,ThongTinNguoiChoi& thongtinnguoichoi);
// hàm kiểm tra flag game trước khi chạy chương trình
int kiemtraflag(char* flag);
bool taidulieujson(DanhSachNguoiChoi& danhsachnguoichoi);

void doimauchude(const string mau, int thutumau);
void inbanner(const string tenbanner, const string mau = mauchude);
void intennguoichoi1(const ThongTinPtr nguoichoi);
void hieuungamthanh_mp3(string duongdanamthanh, bool trangthaiamthanh);
void hieuungamthanh_wav(string duongdanamthanh, bool trangthaiamthanh);
void chuyendoitrangthaiamthanh(bool& trangthaiamthanh);
void chuyendoitrangthaiAIgoiy(bool& trangthaiAIgoiy);
void chuyendoitrangthaitrochuot(bool& trangthaicontrochuot);
void ancontrochuot(bool trangthaicontrochuot);
void khoitaolist(DanhSachNguoiChoi& danhsachnguoichoi);
void themcuoidanhsachtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr thongtinnguoichoi);
//void taidulieujson(DanhSachNguoiChoi& danhsachnguoichoi);
void luudulieujson(DanhSachNguoiChoi& danhsachnguoichoi);
void luulichsujson(string& tentaikhoan, LichSu& lichsu);
void xuatlichsu(LichSu& lichsu, int stt);
void xuatbanglichsu(vector<LichSu>& danhsachlichsu);
void ingiuamanhinh(const string& cau, string mau);
void dungchuongtrinh();
void hienthongtinnguoichoi(ThongTinPtr& nguoichoi);
void trangchu(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);

// sảnh 
void sanhadmin(DanhSachNguoiChoi& danhsachnguoichoi);
void sanh_caidat(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void sanh_gamexocxoc(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void sanh_gamebai(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void sanh_gamemayrui(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void sanh_game2nguoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void sanhchoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);

void loadraketqua(int sogiay);
void chosaukhinhapthanhcong(int sogiay);
void luumatkhaumoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);
void huongdanflag();

char getchlinux();

string chematkhau();
string mahoamatkhau(string matkhau);
string dinhdangtien(int sotien);
string xoaansi(string s);

ThongTinPtr khoitaotaikhoan(ThongTinNguoiChoi& thongtinnguoichoi);
ThongTinPtr timtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, string& tentaikhoan);
