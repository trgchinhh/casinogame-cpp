# CASINO GAME C++

## Giới thiệu
- Đây là game cá cược viết bằng ngôn ngữ C++ với nhiều trò chơi tết (cá cược) khác nhau 
- Chạy trên môi trường dòng lệnh (commandline) với thiết kế giao diện trực quan và dễ chơi và đẹp mắt
- Game có mô phỏng xúc xắc và các số bằng ký tự ASCII, ngoài ra còn có ký tự đặc biêt và hiệu ứng âm thanh  
- Game có nhiều ký tự đặc biệt nên cài JetbrainsMono Font hoặc những font khác ngoài font mặc định để có trải nghiệm tốt nhất 
- Giao diện lấy cảm hứng từ dự án [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp)

## Liên kết 
### Video demo chương trình
- Video demo bản cũ: [Xem video tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)
- Video demo bản cũ (Phân quyền): [Xem video tại đây](https://drive.google.com/file/d/1Hy8oKgY7B0qIRuHvk53ie2pSgyyENue0/view?usp=sharing)
- Video demo bản mới nhất: [Xem tại đây](https://drive.google.com/file/d/1c7uQ_GcHkBOLcvkximw3A-mDyji1HHS6/view?usp=sharing)

## Chức năng
### Trang chủ: 
- Bật tắt hiệu ứng âm thanh
- Đăng nhập / Đăng ký
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
- Tài xỉu 1 xúc xắc 
- Tài xỉu 3 xúc xắc
- Đoán dài ngắn 
- Đoán 2/7 màu sắc
- Đoán số trong khoảng A -> B
- Đoán chẵn lẻ trong khoảng 0 -> 9
- Tung xu úp ngửa
- Lắc bầu cua 
- Kéo búa bao 
- Xem lịch sử chơi
- Đăng xuất (quay lại trang chủ)

## Yêu cầu
- Phiên bản C++ 17 trở lên
- Đổi font chữ terminal phù hợp để hiển thị ký tự đặc biệt
  + Ví dụ: Jetbrains Mono Font, Fira Code Font, ...

## Cấu trúc dự án
```
├── data
│   ├── admin
│   │   └── thongtintk.json
│   └── player
│       ├── lichsugame.json
│       └── taikhoan.json
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
│   │   ├── baucua.h
│   │   ├── chanle.h
│   │   ├── daingan.h
│   │   ├── doanmau.h
│   │   ├── doanso.h
│   │   ├── keobuabao.h
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
├── LICENSE
├── README.md
└── build.cpp
```

## Cài đặt
- Để tự động build chương trình thì cần chạy file: `khoichay.cpp`
- Còn nếu muốn chạy thủ công thì build chương trình theo lệnh: `g++ src\\main.cpp src\\resource\\resource.o -o " + tenchuongtrinh + " -lwinmm -w`

## Demo Screenshot

### 1 Phần đăng nhập
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/beee556c-d633-4a38-b0c6-6a353f0c34b3" />

### 2 Admin
<img width="1919" height="1077" alt="image" src="https://github.com/user-attachments/assets/16878db4-ba60-42b9-ac8a-4d5ea2626a9c" />

### 3 Game 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/23cd0582-5a31-452b-995e-d0c3821f4437" />

## Tác giả : Nguyễn Trường Chinh (NTC++)
## Github  : https://github.com/trgchinhh
