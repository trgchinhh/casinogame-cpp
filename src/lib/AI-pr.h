// GROQ AI

// -----------------------------------------
// Thêm AI gợi ý kết quả bằng lịch sử chơi  
// -----------------------------------------

#pragma once 

#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <curl/curl.h>
#include "header.h"
#include "json.hpp"
#include "props.h"

using namespace std;
using namespace chrono;
using namespace this_thread;
using json = nlohmann::ordered_json;

#define s_npos string::npos

const string duongdan_lichsugame = "../data/player/lichsugame.json";
const string duongdan_env        = "../env/.env";

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string docfilelichsugame(const string tennguoichoi){
    ifstream file(duongdan_lichsugame);
    if(!file.is_open())
        return "Không đọc được file lịch sử !";
    json dulieu;
    file >> dulieu;
    string lichsugame;
    int dem = 0;
    for(auto &v : dulieu[tennguoichoi]){
        lichsugame += v["trochoi"].get<string>() + " ";
        lichsugame += to_string(v["tongdiem"].get<int>()) + " ";
        lichsugame += v["ketqua"].get<string>() + "\n";
        dem++;
        if(dem >= 10) break;
    }
    return lichsugame;
}

void hieuung_cho(atomic<bool>& dung){
    const char* frames[] = {".  ", ".. ", "..."}; 
    int i = 0;
    while(!dung){
        cout << "\r\t(" << RED << "*" << RESET 
             << ") Vui lòng chờ AI phản hồi " << frames[i] << flush;
        i = (i + 1) % 3;
        sleep_for(milliseconds(400));
    }
    cout << "\r                                             \r";
}

bool ketqua_ai(const string phanhoi){
    try{
        json j = json::parse(phanhoi);
        string ketqua =
        j["choices"][0]["message"]["content"].get<string>();
        size_t pos = ketqua.find('.');  // tìm dấu chấm
        if(pos != string::npos)
            ketqua = ketqua.substr(0, pos + 1); 
        cout << "\t[" << RED << "Groq AI" << RESET 
             << "]: " << ketqua << RESET << endl;
        return true;
    }
    catch(...){
        cout << RED << "\tAI gặp sự cố khi phản hồi !" << RESET << endl;
        cout << RED << "\tVui lòng kiểm tra API tại dường dẫn: ../env/.env" << RESET << endl; 
        return false;
    }
}

void load_env(const string& file){
    ifstream f(file);
    if(! f.is_open()){
        cout << RED << "\tKhông thể mở file .env" << RESET << endl;
        //cout << YELLOW "\tĐường dẫn: " << RESET << filesystem::current_path() << endl;
        return;
    }
    string line;
    while(getline(f,line)){
        if(line.empty() || line[0] == '#') continue;
        size_t pos = line.find('=');
        if(pos == string::npos) continue;
        string key = line.substr(0,pos);
        string val = line.substr(pos+1);
        string env = key + "=" + val;
        #ifdef _WIN32
            _putenv(_strdup(env.c_str()));
        #else
            putenv(strdup(env.c_str()));
        #endif
    }
}

void ai_goiy(const string tennguoichoi, int& sodunguoichoi, 
             const string tengame, 
             // Khoảng a đến b dùng cho trò đoán số A->B, đoán chẵn lẻ
             int a = NULL, 
             int b = NULL,
             bool trangthaiAIgoiy = false){

    // kiểm tra trạng thái (bật tắt) trước khi gợi ý
    if(!trangthaiAIgoiy){
        return;
    }

    // kiểm tra số dư nếu không đủ thì ko gợi ý
    if(sodunguoichoi < sodunhonhat || sodunguoichoi < phidungaigoiy){
        cout << YELLOW << "\t(!) Không đủ tiền để AI gợi ý ! Vui lòng nạp thêm" << RESET << endl;
        cout << "\t(>) Thanh toán không thành công !" << RESET << endl;
        return;
    }

    // load file .env
    load_env(duongdan_env);
    // Groq AI API
    const char* API_KEY = getenv("API_KEY");
    const char* URL = getenv("URL");

    // Kiểm tra API và URL
    if(! API_KEY){
        cout << RED << "\tAPI KEY không khả dụng ! Vui lòng nhập đúng API KEY" << RESET << endl;
        return;
    }
    if(! URL){
        cout << RED << "\tURL không khả dụng ! Vui lòng nhập đúng URL" << RESET << endl;
        return;
    }

    string lichsugame = docfilelichsugame(tennguoichoi);
    // Prompt (hướng dẫn AI cách trả lời) 
    string lenh = "";
    lenh = 
    "Bạn là AI Casino. Phân tích lịch sử và đưa ra gợi ý tiếp theo:\n"
    + lichsugame +
    "\nTôi đang chơi ";
    if(tengame.find("taixiu") != s_npos)
        lenh += "tài xỉu. Chỉ trả lời đúng 1 từ: Tài hoặc Xỉu";
    else if(tengame.find("xocdia") != s_npos)
        lenh += "xóc dĩa. Chỉ trả lời đúng 1 từ: Chẵn hoặc Lẻ";
    else if(tengame.find("upngua") != s_npos)
        lenh += "úp ngữa. Chỉ trả lời đúng 1 từ: Úp hoặc Ngửa";
    else if(tengame.find("baucua") != s_npos)
        lenh += "bầu cua. Chỉ trả lời đúng 3/6 từ sau: Bầu, Cua, Tôm, Cá, Nai hoặc Gà. "
                "Trả lời đúng 3 từ cách nhau bằng dấu cách. Ví dụ: Bầu Cua Tôm";
    else if(tengame.find("daingan") != s_npos)
        lenh += "dài ngắn. Chỉ trả lời đúng 1 từ: Dài hoặc Ngắn";
    else if(tengame.find("doanmau") != s_npos)
        lenh += "đoán màu. Chỉ trả lời đúng 3/7 từ sau: Đỏ, Cam, Vàng, Lục, Lam, Chàm hoặc Tím. "
                "Trả lời đúng 2 từ cách nhau bằng dấu cách. Ví dụ: Tím Cam";
    else if(tengame.find("doanso") != s_npos)
        lenh += "đoán số. Chỉ trả lời đúng 1 số trong khoảng " + to_string(a) + " đến " + to_string(b) + ". "
                "Nếu không chắc số nào thì chọn ngẫu nhiên 1 số trong khoảng đó";
    else if(tengame.find("chanle") != s_npos)
        lenh += "chẵn lẻ. Chỉ trả lời đúng 1 từ: Chẵn hoặc Lẻ";
    else if(tengame.find("keobuabao") != s_npos)
        lenh += "kéo búa bao. Chỉ trả lời đúng 1 từ: Kéo, Búa hoặc Bao";
    //lenh += "\nChỉ trả lời đúng 1 từ hoặc 1 số theo yêu cầu. Không giải thích, không viết thêm chữ nào khác.";
    lenh += "\nKhông được nhắc lại kết quả trước đó.";
    lenh += "\nKhông giải thích, không viết thêm chữ nào khác.";

    json body_json = {
        {"model","llama-3.1-8b-instant"},
        //{"max_tokens", 10},
        {"messages",{
            {
                {"role","user"},
                {"content",lenh}
            }
        }}
    };
    string body = body_json.dump();
    auto start = steady_clock::now();
    // hiệu ứng chờ
    atomic<bool> stop(false);
    thread loading(hieuung_cho, ref(stop));

    CURL *curl = curl_easy_init();
    if(!curl){
        stop = true;
        loading.join();
        cout << RED << "AI lỗi !" << RESET << endl;
        return;
    }
    string phanhoi;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers,"Content-Type: application/json");
    string auth = "Authorization: Bearer " + string(API_KEY);
    headers = curl_slist_append(headers,auth.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &phanhoi);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // loading chạy ít nhất 2s
    auto elapsed = duration_cast<seconds>(steady_clock::now() - start);
    if(elapsed.count() < 2){
        sleep_for(seconds(2) - elapsed);
    }
    stop = true;
    loading.join();

    // Phí dùng AI 
    bool checkketqua_ai = ketqua_ai(phanhoi);
    if(checkketqua_ai){
        sodunguoichoi -= phidungaigoiy;
        cout << "\t(>) Đã thanh toán phí AI: " << RED 
             << "-" << dinhdangtien(phidungaigoiy) << RESET << " (VND)" << endl;
        cout << "\t └> Số dư còn lại: " << YELLOW 
             << dinhdangtien(sodunguoichoi) << RESET << " (VND)" << endl;
    } else {
        cout << "\t(>) Thanh toán không thành công !" << RESET << endl;
    } 
    cout << "\n\t───────────────────────────────────────\n" << endl;
}
