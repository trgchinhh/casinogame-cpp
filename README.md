# CASINO GAME C++

## Giới thiệu

**Casino Game C++** là một dự án game cá cược chạy trên môi trường dòng lệnh (custom TUI), được phát triển bằng ngôn ngữ **C++ (C++17+)**. Dự án mô phỏng nhiều trò chơi cá cược quen thuộc với giao diện ASCII trực quan, hiệu ứng màu sắc và âm thanh, mang lại trải nghiệm sinh động ngay trong terminal.

Dự án được xây dựng với mục tiêu:

* Rèn luyện tư duy lập trình C++ thông qua một project nhỏ
* Xây dựng 1 TUI của riêng mình (để hạn chế việc dùng chuột khi chơi)
* Làm quen với việc tổ chức mã nguồn, tách module và quản lý dữ liệu
* Mô phỏng một hệ thống game có tài khoản, phân quyền và lịch sử chơi và bảo mật

Giao diện và cách tổ chức menu được lấy cảm hứng và mở rộng thêm từ dự án trước đó: [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp).

> ⚠️ Lưu ý: Do sử dụng nhiều ký tự đặc biệt và ASCII art, nên khuyến nghị sử dụng các font monospace như **JetBrains Mono**, **Fira Code**, v.v. để hiển thị tốt nhất.

---

## Video demo
* Demo phiên bản cũ: [Xem tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)
* Demo phiên bản cũ (có phân quyền): [Xem tại đây](https://drive.google.com/file/d/1Hy8oKgY7B0qIRuHvk53ie2pSgyyENue0/view?usp=sharing)
* Demo phiên bản đầy đủ mới nhất: [Xem tại đây](https://drive.google.com/file/d/1oOljz_fCsw7h26MSMgVNdi5Wh4vCp33_/view?usp=sharing)

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

> ⚠️ Lưu ý: với Admin thì có thể tạo nhiều tài khoản nhưng đều đến trang quản lý (không có phân chia tài khoản như của User)  

#### Quyền User (Trang game)
* Game Xóc xóc<br>
    ├─ Tài xỉu 1 xúc xắc<br>
    ├─ Tài xỉu 3 xúc xắc<br>
    ├─ Xóc dĩa<br>
    ├─ Úp ngửa xu<br>
    ├─ Lắc bầu cua<br>
    └─ Tung xu (úp / ngửa)<br>
* Game bài<br>
    ├─  Ba cào (cào 3 lá)<br>
    └─ Xì dách (21 điểm)<br>
* Game May rủi<br>
    ├─ Đoán dài / ngắn<br>
    ├─ Đoán 2 / 7 màu sắc<br>
    ├─ Đoán số trong khoảng A → B<br>
    ├─ Chẵn / lẻ (0 → 9)<br>
    └─ Kéo búa bao<br>
* Xem lịch sử chơi
* Đăng xuất (quay về trang chủ)

---

## Yêu cầu hệ thống

* Trình biên dịch hỗ trợ **C++17** trở lên
* Terminal hỗ trợ màu ANSI
* Font chữ monospace (khuyến nghị):

  * JetBrains Mono
  * Fira Code
  * Hoặc dùng các font hỗ trợ NerdFont

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
│   │   ├── bacao.h
│   │   ├── xocdia.h
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

### Đã cập nhật bản build chính thức ở Release: [Casino 1.0.0](https://github.com/trgchinhh/casinogame-cpp/releases/tag/v.1.0.0) 
---

> ⚠️ Lưu ý: trước khi build cần phải cài thư viện OpenSSL bằng MingW64/MSYS2. Nếu chưa có chạy lệnh dưới đây
```bash
pacman -S mingw-w64-x86_64-openssl
```
> Cần chạy lệnh trong MingW64

### Build tự động
Chạy file:
```bash
build.cpp
```
> Sau khi build và chạy file build.exe nó sẽ biên dịch tất cả và chạy chương trình chính 

### Build thủ công (Windows - MinGW)
```bash
g++ src\main.cpp -IC:\OpenSSL-Win64\include -LC:\OpenSSL-Win64\lib src\resource\resource.o -o Casino.exe -lwinmm -lssl -lcrypto -w
```
> Không build trực tiếp trong Mingw64 

---

## Ảnh minh họa

### Đăng nhập
![Login](https://github.com/user-attachments/assets/6c64cfe6-5e64-483d-bbb3-f8f1566b5182)

### Hướng dẫn
![Hướng dẫn](https://github.com/user-attachments/assets/bd1c06aa-efd7-45e7-b892-cee63ee661ee)

### Trang Admin
![Admin](https://github.com/user-attachments/assets/0e0df5f5-e185-4223-8409-7fe425c97a2c)

### Trang Player
![Game](https://github.com/user-attachments/assets/ec2e2017-592a-47c6-bbd6-c64ee5388d3d)

### Trang game xóc xóc 
![Xóc Xóc](https://github.com/user-attachments/assets/4959742b-b88f-4de8-93dd-5648bebc5a22)

### Trang game bài
![Game bài](https://github.com/user-attachments/assets/6339d5d3-f34a-42bd-a895-8661fe7ed1bc)

### Trang game may rủi
![Game may rủi](https://github.com/user-attachments/assets/265f8581-49be-4a91-8823-647eac3ace5b)

### Trang game 2 người
![Game 2 người](https://github.com/user-attachments/assets/1e656ce7-b07e-4a24-9103-43eeb6c0a3be)

### Lịch sử chơi
![Lịch sử chơi](https://github.com/user-attachments/assets/78e624a8-5cb1-4970-ac1d-e5be431e6b1e)

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

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.
