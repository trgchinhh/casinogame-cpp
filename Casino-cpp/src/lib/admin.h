#include <string>
using namespace std;

// Dùng để phân quyền cho người thường và admin
enum PhanQuyen {
    Nguoichoi, Admin
};

// Tên tài khoản và mật khẩu mặc định của admin
const string TentaikhoanAdmin = "admin";
const string MatkhauAdmin = "admin";