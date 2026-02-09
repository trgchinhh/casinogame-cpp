// Header chính 

#pragma once
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <random>
#include <mmsystem.h>       // phát hiệu ứng âm thanh
#include "props.h"          // chứa mặt xúc xắc và số
#include "banner.h"         // chứa nhiều banner 
#include "dothd.h"          // hàm ẩn file mật
#include "admin.h"          // phân quyền và thông tin admin
#include "json.hpp"         // dùng định dạng json 
#include "picosha2.h"       // dùng hash sha256
#include "instruct.h"       // hướng dẫn cách chơi

#pragma comment(lib, "winmm.lib")

using namespace std;
using json = nlohmann::ordered_json;

#define SoTaiKhoanToiDa 100           // đăng ký tối đa 100 tài khoản

struct ThongTinNguoiChoi {
    int sothutu;                      // số thứ tự
    string tennguoichoi;              // tên người chơi (dùng như nickname) 
    string tentaikhoan;               // tên tài khoản (đăng ký)
    string matkhau;                   // mật khẩu
    string makhoa6so;                 // mã khóa 6 số (phải nhớ khi quên mật khẩu)
    int sodu;                         // số dư (giới hạn 100.000.000)
    PhanQuyen phanquyen = Nguoichoi;  // quyền người chơi (admin - player) 
    ThongTinNguoiChoi* next;          // con trỏ next 
    ThongTinNguoiChoi* prev;          // con trỏ prev
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

// Các đường dẫn 
// Lưu dữ liệu
const string dd_danhsachtaikhoan = "data\\player\\taikhoan.json";
const string dd_danhsachlichsu = "data\\player\\lichsugame.json";
// Lưu âm thanh 
const string dd_lindachaocanha = "sound\\linda_chao_ca_nha.wav";
const string dd_1dongxuroi = "sound\\1_dong_xu_roi.mp3";
const string dd_conginuadau = "sound\\con_gi_nua_dau.mp3";
const string dd_dongudoanhai = "sound\\do_ngu_do_an_hai.mp3";
const string dd_dunglacontraicuata = "sound\\dung_la_con_trai_cua_ta.mp3";
const string dd_giongcuoithay3 = "sound\\giong_cuoi_thay_3.mp3";
const string dd_hdpethingonluon = "sound\\hdpe_thi_ngon_luon.mp3";
const string dd_lacxucxac = "sound\\lac_xuc_xac.mp3";
const string dd_nhieudongxuroi = "sound\\nhieu_dong_xu_roi.mp3";
const string dd_maymuanuadi = "sound\\mua_nua_di.mp3";
const string dd_dichuyenmenu = "sound\\chon_menu.mp3";
const string dd_xinvinhbietcu = "sound\\xin_vinh_biet_cu.wav";

// Các giá trị bắt buộc 
const int sodunhonhat = 1000;           // số dư lớn nhất cho phép
const int sodulonnhat = 100000000;      // số dư nhỏ nhất cho phép
const int sogiaycho = 2;                // số giây load khi đăng nhập / xuất 
const int solansaitoida = 3;            // số lần sai tối đa
const int chieudaima6so = 6;            // chiều dài mã khóa 6 số
static bool trangthaiamthanh = false;   // trạng thái âm thanh (mới vào luôn tắt)

// NGUYÊN MẪU HÀM

// Admin 
void sanhadmin(DanhSachNguoiChoi& danhsachnguoichoi);
void hienthongtinadmin(const string& tenadmin);
void xemthongtinnguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void xuatthongtinnguoichoi(ThongTinNguoiChoi& thongtinnguoichoi);
void xuatbangthongtinnguoichoi(vector<ThongTinNguoiChoi>& danhsachthongtinnguoichoi);
void xemlichsunguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void xoataikhoannguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void naptienchonguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);
void trutiennguoichoi(DanhSachNguoiChoi& danhsachnguoichoi);

// Người chơi
int kiemtrasoluongtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi);
int sothutucuoicung(DanhSachNguoiChoi& danhsachnguoichoi);
int phiencuoicung(string& tentaikhoan);
int laychieurongterminal();
int doronghienthi(const char* s);
int do_rong_hien_thi_thuc(const string& str);
int dodai_hienthi_utf8(const string& s);

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
bool quenmatkhau(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);

void inbanner(const string tenbanner);
void hieuungamthanh_mp3(string duongdanamthanh, bool trangthaiamthanh);
void hieuungamthanh_wav(string duongdanamthanh, bool trangthaiamthanh);
void chuyendoitrangthaiamthanh(bool& trangthaiamthanh);
void xoaansi(string s);
void ancontrochuot(bool trangthaichuot);
void khoitaolist(DanhSachNguoiChoi& danhsachnguoichoi);
void themcuoidanhsachtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr thongtinnguoichoi);
void taidulieujson(DanhSachNguoiChoi& danhsachnguoichoi);
void luudulieujson(DanhSachNguoiChoi& danhsachnguoichoi);
void luulichsujson(string& tentaikhoan, LichSu& lichsu);
void xuatlichsu(LichSu& lichsu, int stt);
void xuatbanglichsu(vector<LichSu>& danhsachlichsu);
void ingiuamanhinh(const string& cau, string mau);
void dungchuongtrinh();
void hiensodunguoichoi(ThongTinPtr& nguoichoi);
void trangchu(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);
void sanhchoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinPtr& nguoichoi);
void loadraketqua(int sogiay);
void chosaukhinhapthanhcong(int sogiay);
void luumatkhaumoi(DanhSachNguoiChoi& danhsachnguoichoi, ThongTinNguoiChoi& thongtinnguoichoi);

// game 
// void game_taixiu1xx(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_taixiu3xx(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_doanso(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_chanle(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_upngua(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_keobuabao(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_baucua(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_doanmau(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_daingan(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_bacao(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_xidach(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);
// void game_xocdia(DanhSachNguoiChoi &danhsachnguoichoi, ThongTinPtr &nguoichoi);

string chematkhau();
string mahoamatkhau(string matkhau);
string dinhdangtien(int sotien);

ThongTinPtr khoitaotaikhoan(ThongTinNguoiChoi& thongtinnguoichoi);
ThongTinPtr timtaikhoan(DanhSachNguoiChoi& danhsachnguoichoi, string& tentaikhoan);
