# CASINO GAME C++

## Giới thiệu

**Casino Game C++** là một dự án game cá cược chạy trên môi trường dòng lệnh (CLI), được phát triển bằng ngôn ngữ **C++ (C++17+)**. Dự án mô phỏng nhiều trò chơi cá cược quen thuộc với giao diện ASCII trực quan, hiệu ứng màu sắc và âm thanh, mang lại trải nghiệm sinh động ngay trong terminal.

Dự án được xây dựng với mục tiêu:

* Rèn luyện tư duy lập trình C++ thông qua một project nhỏ
* Làm quen với việc tổ chức mã nguồn, tách module và quản lý dữ liệu
* Mô phỏng một hệ thống game có tài khoản, phân quyền và lịch sử chơi và bảo mật

Giao diện và cách tổ chức menu được lấy cảm hứng từ dự án trước đó: [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp).

> ⚠️ Lưu ý: Do sử dụng nhiều ký tự đặc biệt và ASCII art, nên khuyến nghị sử dụng các font monospace như **JetBrains Mono**, **Fira Code**, v.v. để hiển thị tốt nhất.

---

## Video demo
* Demo phiên bản cũ: [Xem tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)
* Demo phiên bản cũ (có phân quyền): [Xem tại đây](https://drive.google.com/file/d/1Hy8oKgY7B0qIRuHvk53ie2pSgyyENue0/view?usp=sharing)
* Demo phiên bản mới nhất: [Xem tại đây](https://drive.google.com/file/d/1Yp0qnBI1qSjZ2htpUJVHOjZOEJUkno1p/view?usp=sharing)

---

## Chức năng chính

### Trang chủ
* Bật / tắt hiệu ứng âm thanh
* Hướng dẫn chơi 
* Đăng ký / đăng nhập tài khoản
* Thoát chương trình

### Phân quyền người dùng
Hệ thống hỗ trợ **2 loại tài khoản**: `Admin` và `User`.

#### Quyền Admin
* Nạp tiền cho tài khoản người chơi
* Trừ tiền người chơi
* Xem thông tin tài khoản
* Xem lịch sử chơi
* Xóa tài khoản
* Đăng xuất (quay về trang chủ)

#### Quyền User (Trang game)
* Tài xỉu 1 xúc xắc
* Tài xỉu 3 xúc xắc
* Đoán dài / ngắn
* Đoán 2 / 7 màu sắc
* Đoán số trong khoảng A → B
* Chẵn / lẻ (0 → 9)
* Tung xu (úp / ngửa)
* Xì dách
* Lắc bầu cua
* Kéo búa bao
* Xem lịch sử chơi
* Đăng xuất

---

## Yêu cầu hệ thống

* Trình biên dịch hỗ trợ **C++17** trở lên
* Terminal hỗ trợ màu ANSI
* Font chữ monospace (khuyến nghị):

  * JetBrains Mono
  * Fira Code

---

## Cấu trúc thư mục

```text
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
│   │   ├── upngua.h
│   │   └── xidach.h
│   ├── lib
│   │   ├── admin.h
│   │   ├── banner.h
│   │   ├── dothd.h
│   │   ├── header.h
│   │   ├── instruct.h
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

---

## Cài đặt & Build

### Build tự động
Chạy file:
```bash
khoichay.cpp
```

### Build thủ công (Windows - MinGW)
```bash
g++ src\\main.cpp src\\resource\\resource.o -o Casino.exe -lwinmm -w
```

---

## Ảnh minh họa

### Đăng nhập
![Login](https://github.com/user-attachments/assets/9d6dde99-3f4e-43ce-a606-118a94dc608b)

### Trang Admin
![Admin](https://github.com/user-attachments/assets/0e0df5f5-e185-4223-8409-7fe425c97a2c)

### Trang Game
![Game](https://github.com/user-attachments/assets/4c7274df-9fd9-487d-b709-d73e26eb732f)

---

## Hạn chế hiện tại
* Chưa tối ưu kiến trúc file hoàn chỉnh
* Logic và giao diện vẫn còn gộp ở một số module
* Còn hardcore vài chổ như biến global 

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**
GitHub: [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án được phát triển với mục đích học tập và nghiên cứu. 
> 📌 Mọi góp ý và đóng góp đều được hoan nghênh.


