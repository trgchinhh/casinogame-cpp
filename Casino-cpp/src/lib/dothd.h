#include <string>
#include <fstream>
#include <vector>
#include "..//lib//json.hpp"    // dùng định dạng json 
#include <openssl/evp.h>        // dùng mã hóa mật khẩu bằng AES
#include <openssl/rand.h>       // này cũng vậy

// PHẦN CODE CỦA FOLDER TAIKHOAN

using namespace std;
using json = nlohmann::ordered_json;

const string dd_dothd = "data\\taikhoan\\thongtintk.json";
unsigned char khoa[32] = "day_la_khoa_bi_mat_32_byte!!!!!";
unsigned char iv[16] = "iv_16_byte!!!!!";

// chuyển từ byte sang hex 
string bytestohex(const vector<unsigned char>& data) {
    static const char* hex = "0123456789abcdef";
    string out;
    out.reserve(data.size() * 2);
    for (unsigned char b : data) {
        out.push_back(hex[b >> 4]);
        out.push_back(hex[b & 0x0F]);
    }
    return out;
}

// chuyển từ hex sang byte 
vector<unsigned char> hextobytes(const string& hex) {
    vector<unsigned char> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byte = hex.substr(i, 2);
        bytes.push_back((unsigned char) strtol(byte.c_str(), nullptr, 16));
    }
    return bytes;
}

// hàm mã hóa mật khẩu chuẩn AES
vector<unsigned char> mahoaaes(const string& dulieugoc, unsigned char khoa[32], unsigned char iv[16]) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    vector<unsigned char> banma(dulieugoc.size() + 16);
    int dodai = 0, tong = 0;
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, khoa, iv);
    EVP_EncryptUpdate(ctx, banma.data(), &dodai, (unsigned char*)dulieugoc.c_str(), dulieugoc.size());
    tong = dodai;
    EVP_EncryptFinal_ex(ctx, banma.data() + tong, &dodai);
    tong += dodai;
    banma.resize(tong);
    EVP_CIPHER_CTX_free(ctx);
    return banma;
}

// hàm giải mã mật khẩu 
string giaimaaes(const vector<unsigned char>& banma, unsigned char khoa[32], unsigned char iv[16]) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    vector<unsigned char> banro(banma.size());
    int dodai = 0, tong = 0;
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, khoa, iv);
    EVP_DecryptUpdate(ctx, banro.data(), &dodai, banma.data(), banma.size());
    tong = dodai;
    EVP_DecryptFinal_ex(ctx, banro.data() + tong, &dodai);
    tong += dodai;
    EVP_CIPHER_CTX_free(ctx);
    return string((char*)banro.data(), tong);
}

void luudulieumatjson(string& tentaikhoan, string& matkhau){
    ifstream file(dd_dothd);
    if (!file.is_open()) return;
    json data; file >> data; file.close();
    for(auto& i : data){
        if(i["tentaikhoan"] == tentaikhoan){
            return;
        }
    }
    json taikhoan;
    taikhoan["tentaikhoan"] = tentaikhoan;
    auto mahoamatkhau = mahoaaes(matkhau, khoa, iv);
    taikhoan["matkhau"] = bytestohex(mahoamatkhau);
    taikhoan["iv"] = bytestohex(vector<unsigned char>(iv, iv + 16));
    data.push_back(taikhoan);
    ofstream fout(dd_dothd);
    fout << setw(4) << data; 
    fout.close();
}

void xoadulieumatjson(string& tentaikhoan){
    ifstream filemk_in(dd_dothd);
    if(filemk_in.is_open()){
        json data_mk;
        filemk_in >> data_mk;
        filemk_in.close();
        if(data_mk.is_array()){
            for(auto it = data_mk.begin(); it != data_mk.end(); ++it){
                if((*it).contains("tentaikhoan") && (*it)["tentaikhoan"] == tentaikhoan){
                    data_mk.erase(it);
                    break;
                }
            }
            ofstream filemk_out(dd_dothd);
            if(filemk_out.is_open()){
                filemk_out << setw(4) << data_mk;
                filemk_out.close();
            }
        }
    }
}

string laymatkhau(const string& tentaikhoan){
    ifstream fin(dd_dothd);
    if (!fin.is_open()) return "";
    json data;
    fin >> data;
    fin.close();
    if (!data.is_array()) return "";
    for (auto& i : data) {
        if (i.contains("tentaikhoan") && i["tentaikhoan"] == tentaikhoan) {
            string matkhaumahoahex = i.value("matkhau", "");
            string ivhex = i.value("iv", "");
            if(matkhaumahoahex.empty() || ivhex.empty()){
                return "";
            } 
            vector<unsigned char> matkhaumahoa = hextobytes(matkhaumahoahex);
            vector<unsigned char> iv = hextobytes(ivhex);
            return giaimaaes(matkhaumahoa, khoa, iv.data());
        }
    }
    return "";
}
