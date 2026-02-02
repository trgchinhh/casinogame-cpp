# CASINO GAME C++

## Giới thiệu
- Đây là game cá cược viết bằng ngôn ngữ C++ với nhiều trò khác nhau
- Chạy trên môi trường dòng lệnh (commandline) với thiết kế giao diện trực quan và dễ chơi
- Game có mô phỏng xúc xắc và các số bằng ký tự ASCII và hiệu ứng âm thanh  
- Game có nhiều ký tự đặc biệt nên cài JetbrainsMono Font để có trải nghiệm tốt nhất 
- Giao diện lấy cảm hứng từ dự án [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp)

## Liên kết 
### Video demo chương trình
- Video demo bản cũ: [Xem video tại đây](https://drive.google.com/file/d/1G6eV0DhiAYCDHklUTUk0BhvdWoKOh5SU/view?usp=sharing)
- Video demo bản cũ: [Xem video tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)
- Video demo bản mới (Phân quyền): [Xem video tại đây](https://drive.google.com/file/d/1Hy8oKgY7B0qIRuHvk53ie2pSgyyENue0/view?usp=sharing)

## Chức năng
### Trang chủ: 
- Bật tắt hiệu ứng âm thanh
- Đăng nhập / Đăng ký
- Quên mật khẩu
- Thoát game
## Phân quyền Admin và User
### Trang Admin
- Nạp tiền
- Trừ tiền
- Xem thông tin 
- Xem lịch sử
- Xóa tài khoản
- Đăng xuất (quay lại trang chủ)
### Trang game (User)
- Tài xỉu 1 xúc xắc / 3 xúc xắc
- Đoán số trong khoảng A -> B
- Chẵn lẻ trong khoảng 0 -> 9
- Tung xu úp ngửa
- Nạp thêm tiền
- Xem lịch sử chơi
- Đăng xuất (quay lại trang chủ)

## Yêu cầu
- Phiên bản C++ 17 trở lên
- Đổi font chữ terminal phù hợp để hiển thị ký tự đặc biệt
  + Ví dụ: Jetbrains Mono Font, Fira Code Font

## Cấu trúc dự án
```
├── data
│   ├── .taikhoan
│   │   └── thongtintk.json
│   ├── lichsugame.json
│   └── taikhoan.json
├── sound
│   ├── 1_dong_xu_roi.mp3
│   ├── chon_menu.mp3
│   ├── con_gi_nua_dau.mp3
│   ├── do_ngu_do_an_hai.mp3
│   ├── dung_la_con_trai_cua_ta.mp3
│   ├── giong_cuoi_thay_3.mp3
│   ├── hdpe_thi_ngon_luon.mp3
│   ├── lac_xuc_xac.mp3
│   ├── linda_chao_ca_nha.mp3
│   ├── linda_chao_ca_nha.wav
│   ├── mua_nua_di.mp3
│   ├── nhieu_dong_xu_roi.mp3
│   ├── xin_vinh_biet_cu.mp3
│   └── xin_vinh_biet_cu.wav
├── src
│   ├── game
│   │   ├── chanle.h
│   │   ├── doanso.h
│   │   ├── taixiu1xx.h
│   │   ├── taixiu3xx.h
│   │   └── upngua.h
│   ├── lib
│   │   ├── admin.h
│   │   ├── banner.h
│   │   ├── dothd.h
│   │   ├── header.h
│   │   ├── json.hpp
│   │   ├── picosha2.h
│   │   └── props.h
│   ├── resource
│   │   ├── casino.ico
│   │   ├── resource.o
│   │   └── resource.rc
│   ├── include.h
│   └── main.cpp
├── Casino.exe
├── LICENSE
├── README.md
├── build.cpp
├── build.exe
└── cautruc.md
```

## Cài đặt
- Phải cài thư viện `OpenSSL` trước khi chạy
- Để tự động build chương trình thì cần chạy file: `khoichay.cpp`
- Còn nếu muốn chạy thủ công thì build chương trình theo lệnh: `g++ src\main.cpp -IC:\OpenSSL-Win64\include -LC:\OpenSSL-Win64\lib src\resource\resource.o -o Casino.exe -lwinmm -lssl -lcrypto -w`


## Screenshot

### 1 Phần đăng nhập
<img width="1918" height="1079" alt="image" src="https://github.com/user-attachments/assets/adbaaf0a-4fa8-445c-bf60-253400fa4c63" />

### 2 Admin
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/59a578c7-d5f5-4efc-a57f-3663f1fb9168" />

### 3 Game 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/69ca24c1-886d-42dc-85bd-d7b69766d226" />

### 4 Lịch sử chơi
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/dc15c177-20f7-4932-b39a-f5db86c2aabb" />


## Tác giả : Nguyễn Trường Chinh (NTC++)
## Github  : https://github.com/trgchinhh



