#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Dùng để phân quyền cho người thường và admin
enum PhanQuyen {
    Nguoichoi, Admin 
};

// Lưu tên tk admin hiện tại để hiển thị 
static string TentaikhoanAdmin = "";
// Mỗi tài khoản admin xếp theo vị trí giống mật khẩu 
// Nếu vtrí tk là 1 thì vtrí mk cũng là 1
static int vitritaikhoan = -1;

// Tạo mảng chứa nhiều tài khoản admin 
// Lưu ý: tuy nhiều tk admin nhưng chỉ có 1 trang quản lý cho admin 
// --> nên mọi tài khoản admin đều chung hệ thống 
const vector<string> tentaikhoanadmin = {
    "admin", "root", "sudo", "super"
};

const vector<string> matkhauadmin = {
    "admin", "root", "sudo", "super"
};

bool kiemtratentaikhoanadmin(const string tentaikhoan){
    for(int i = 0; i < tentaikhoanadmin.size(); i++){
        if(tentaikhoanadmin[i] == tentaikhoan){
            vitritaikhoan = i;
            return true;
        }
    }
    return false;
}

bool kiemtramatkhauadmin(const string matkhau){
    if(vitritaikhoan == -1 || 
       vitritaikhoan > tentaikhoanadmin.size()){
        cout << "\tThiết lập mật khẩu admin còn thiếu !" << endl;
        return false;
    }
    if(matkhauadmin[vitritaikhoan] == matkhau) return true;
    return false;
}
