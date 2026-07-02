![Casino logo](docs/logo.png)

# Casino Game

**Casino Game C++** là một dự án game cá cược chạy trên môi trường dòng lệnh (custom TUI), được phát triển bằng ngôn ngữ **C++ (C++17+)**. Dự án mô phỏng nhiều trò chơi cá cược quen thuộc với giao diện ASCII trực quan, hiệu ứng màu sắc và âm thanh, có tích hợp AI, mang lại trải nghiệm sinh động ngay trong terminal.

![Casino demo](docs/casino-demo.gif)

Dự án được xây dựng với mục tiêu:

* Rèn luyện tư duy lập trình C++ thông qua một project nhỏ
* Xây dựng 1 TUI của riêng mình (để hạn chế việc dùng chuột khi chơi)
* Làm quen với việc tổ chức mã nguồn, tách module và quản lý dữ liệu
* Mô phỏng một hệ thống game có tài khoản, phân quyền, cài đặt, xếp hạng, lịch sử chơi và bảo mật
* Tích hợp AI dự đoán kết quả vào game

Giao diện và cách tổ chức menu được lấy cảm hứng và mở rộng thêm từ dự án trước đó: [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp).

> ⚠️ Lưu ý: Do sử dụng nhiều ký tự đặc biệt và ASCII art, nên khuyến nghị sử dụng các font monospace như **JetBrains Mono Nerd Font**, **Fira Code Nerd Font**, v.v. để hiển thị tốt nhất.

## Kiến trúc hệ thống vận hành
Hệ thống được thiết kế theo mô hình phân tầng chức năng quản lý từ khâu xác thực cho đến khi phân phối các sảnh trò chơi
```bash
              ┌─────────────────────────────────┐
              │            TRANG CHỦ            │
              ├─────────────────────────────────┤
              │ • Bật / tắt hiệu ứng âm thanh   │
              │ • Thông tin game                │
              │ • Hướng dẫn chơi                │
              │ • Đăng ký / đăng nhập tài khoản │
              │ • Thoát chương trình            │
              └────────────────┬────────────────┘
                               │ Đăng nhập
              ┌────────────────┴────────────────┐
              │       HỆ THỐNG PHÂN QUYỀN       │
              └──────┬───────────────────┬──────┘
                     │ Admin             │ User
┌────────────────────┴────┐     ┌────────┴────────────────┐
│      SẢNH QUẢN TRỊ      │     │       SẢNH TRÒ CHƠI     │
├─────────────────────────┤     ├─────────────────────────┤
│ • Nạp / Trừ tiền User   │     │ • Game Xóc xóc (Có AI)  │
│ • Xem lịch sử hệ thống  │     │ • Game Bài (Blackjack)  │
│ • Bảng xếp hạng đại gia │     │ • Game May rủi (Slots)  │
│ • Quản lý/Xóa tài khoản │     │ • Game 2 người / Flag   │
└─────────────────────────┘     └─────────────────────────┘

```
> ⚠️ Lưu ý: với Admin thì có thể tạo nhiều tài khoản nhưng đều đến trang quản lý (không có phân chia tài khoản như của User)  

---

## Bài viết
* Bài viết trên facebook chính thức: [Xem tại đây](https://www.facebook.com/share/p/1DkLyLTCGQ/)

---

## Video demo
* Demo bản cũ: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)
* Demo bản mới: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)

---

## Kiến trúc vận hành quyền user (trang game)
```bash
                  ┌─────────────────────────────────────────────────────────┐
                  │                HỆ THỐNG CÁC SẢNH TRÒ CHƠI               │
                  └────────────────────────────┬────────────────────────────┘
                                               │
      ┌──────────────────┬─────────────────────┼─────────────────────┬──────────────────┐
      ▼                  ▼                     ▼                     ▼                  ▼
┌───────────┐      ┌───────────┐         ┌───────────┐         ┌───────────┐      ┌───────────┐
│ GAME BÀI  │      │ GAME 2 NG │         │ GAME XÓC  │         │ MAY RỦI   │      │ GAME FLAG │
├───────────┤      ├───────────┤         ├───────────┤         ├───────────┤      ├───────────┤
│ • Bài cào │      │ • Bài cào │         │ • Bầu cua │         │ • Chẵn lẻ │      │ • Chế độ  │
│           │      │           │         │           │         │           │      │   ẩn kích │
│ • So bài  │      │ • Ném 1   │         │ • Tài xỉu │         │ • Dài     │      │   hoạt qua│
│   1 lá    │      │   xúc xắc │         │   1 XX    │         │   ngắn    │      │   tham số │
│           │      │           │         │           │         │           │      │   terminal│
│ • Xì dách │      │ • Ném 3   │         │ • Tài xỉu │         │ • Đoán    │      │           │
│           │      │   xúc xắc │         │   3 XX    │         │   màu     │      │ • Gồm đầy │
│           │      │           │         │           │         │           │      │  đủ 5 game│
│           │      │ • So bài  │         │ • Úp ngửa │         │ • Đoán số │      │   đối     │
│           │      │   1 lá 2ng│         │           │         │           │      │   kháng   │
│           │      │           │         │ • Xóc đĩa │         │ • Kéo búa │      │   như sảnh│
│           │      │ • Xì dách │         │           │         │   bao     │      │   2 người │
│           │      │   2 người │         │           │         │           │      │   nhưng có│
│           │      │           │         │           │         │           │      │   cờ cược │
└───────────┘      └───────────┘         └───────────┘         └───────────┘      └───────────┘
```

> ⚠️ Lưu ý: phần game flag chỉ chơi được khi gõ terminal `Casino.exe [game]`
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

## Cài đặt & Build

### Xem các bản cập nhật và bản build chính thức tại: [Realease](https://github.com/trgchinhh/casinogame-cpp/releases)

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
g++ src\main.cpp -IC:\OpenSSL-Win64\include -LC:\OpenSSL-Win64\lib src\resource\resource.o -o Casino.exe -lwinmm -lssl -lcrypto -lcurl -w
```
> Không build trực tiếp trong Mingw64 

---

## Ưu điểm
* Code đã được chỉnh để chạy trên trình biên dịch GNU/GCC trên Windows và Linux

## Hạn chế hiện tại
* Chưa tối ưu kiến trúc file module hoàn chỉnh
* Chưa mở rộng class mà còn lạm dụng struct nhiều
* Logic và giao diện vẫn còn gộp ở một số module
* Còn hardcore vài chổ như biến global 

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**
GitHub: [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.
