#include <string>
#include <fstream>
#include "..//lib//json.hpp"

// PHẦN CODE CỦA .TAIKHOAN

using namespace std;
using json = nlohmann::ordered_json;

#include <string>
#include <fstream>
#include "..//lib//json.hpp"

// PHẦN CODE CỦA .TAIKHOAN

using namespace std;
using json = nlohmann::ordered_json;

const string dd_dothd = "data\\taikhoan\\thongtintk.json";

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
    taikhoan["matkhau"] = matkhau;
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
            return i.value("matkhau", "");
        }
    }
    return "";
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
    taikhoan["matkhau"] = matkhau;
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
            return i.value("matkhau", "");
        }
    }
    return "";

}
