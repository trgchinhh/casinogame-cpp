<p align="center">
  <img height="300" src="img/logo.png"/>
</p>

<p align="center">
  <a href="https://en.cppreference.com/w/cpp/17">
    <img src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg" alt="Language"/>
  </a>
  <a href="https://github.com/trgchinhh/casinogame-cpp">
    <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-orange.svg" alt="Platform"/>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License"/>
  </a>
  <a href="https://github.com/trgchinhh">
    <img src="https://img.shields.io/badge/Author-Tr%C6%B0%E1%BB%9Dng%20Chinh-yellow" alt="Author"/>
  </a>
</p>


## CASINO GAME C++

**Casino Game C++** là một dự án game cá cược tập hợp gồm nhiều minigame bên trong, vận hành hoàn toàn trên môi trường dòng lệnh (custom TUI), được phát triển bằng ngôn ngữ **C++ (C++14+)**. dự án mang đến trải nghiệm đồ họa ASCII trực quan, hệ thống âm thanh sống động, cơ chế bảo mật mã hóa nâng cao và tích hợp mô hình AI dự đoán kết quả ngay trong Terminal.

---

![Casino launcher](docs/casino-launcher.png)

**Dự án được xây dựng với mục tiêu:**

* Rèn luyện tư duy lập trình C++ thông qua một project nhỏ
* Xây dựng 1 TUI của riêng mình (để hạn chế việc dùng chuột khi chơi)
* Làm quen với việc tổ chức mã nguồn, tách module và quản lý dữ liệu
* Mô phỏng một hệ thống game có tài khoản, phân quyền, cài đặt, xếp hạng, lịch sử chơi và bảo mật
* Tích hợp AI dự đoán kết quả vào game

**Tính năng cốt lõi**

- Custom TUI & điều hướng con trỏ: 
  - Giao diện custom TUI giúp tối ưu hóa phần điều hướng con trỏ, giúp người chơi dùng mũi tên (↑ ↓ ← →) di chuyển chọn menu mà không cần phải dùng chuột

- Hệ thống phân quyền:
  - User: Quản lý tiền chơi, đặt cược, theo dõi lịch sử game, ...
  - Admin: Quản lý tài khoản người chơi, số dư, theo dõi lịch sử game, nạp/trừ tiền

- Bảo mật:
  - User: đối với user, password sẽ được hash sha256 lúc đăng ký tài khoản để đối chứng khi đăng nhập lần tới
  - Admin: đối vói admin sẽ dùng AES để lưu password của user, tiện cho việc decode, admin sẽ dễ quan sát thông tin tài khoản thật 

- AI tích hợp:
  - Một số game đã được đặt AI (đã bao gồm prompt cho game đó) để AI phân tích lịch sử game và cho ra kết quả gợi ý

- Âm thanh / màu sắc:
  - Game cũng bao gồm âm thanh vui nhộn để tăng tính hài hước cho game, bên cạnh cũng có màu sắc (theme) có thể chỉnh trong cài đặt

![Casino demo](docs/demo.gif)

Giao diện và cách tổ chức menu được lấy cảm hứng và mở rộng thêm từ dự án trước đó: [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp).

> ⚠️ Lưu ý: Do sử dụng nhiều ký tự đặc biệt và ASCII art, nên khuyến nghị sử dụng các font monospace như **JetBrains Mono Nerd Font**, **Fira Code Nerd Font**, v.v. để hiển thị tốt nhất.

---

## Cấu Trúc Thư Mục Dự Án

```bash
casinogame-cpp/
├── bin/                    # folder chứa game.exe
├── data/                   # folder chứa data người chơi
├── docs/                   # folder chứa file gif demo
├── env/                    # folder chứa .env dùng cho API AI
├── img/                    # folder chứa logo
├── sound/                  # folder chứa hiệu ứng âm thanh (.wav/mp3)
├── src/                    # folder chứa mã nguồn
│   ├── main.cpp            # chương trình chính
│   ├── include.h           # include tổng của main
│   ├── lib/                # folder chứa lib cần thiết
│   ├── resource/           # folder chứa icon
│   └── game/               # folder chứa game 
│       ├── game_flag/      # folder chứa game flag (5 game)
│       ├── game_2_nguoi/   # folder chứa game 2 người (5 game)
│       ├── game_bai/       # folder chứa game bài (3 game)
│       ├── game_may_rui/   # folder chứa game may rủi (5 game)
│       └── game_xoc_xoc/   # folder chứa game xóc xóc (5 game)
├── .gitignore
├── build.cpp               # file dùng build toàn chương trình (giống makefile)
├── LICENSE
└── README.md
```
---

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

## Menu mọi thể loại game

| Thể loại game | Game 1 | Game 2 | Game 3 | Game 4 | Game 5 | Ghi chú |
|:---------|:-------|:-------|:-------|:-------|:-------|:--------|
| **Game bài** | Bài cào  | So bài 1 lá | Xì dách |   |   | Chơi với máy |
| **Game 2 người** | Bài cào  | Ném 1 xúc xắc | Ném 3 xúc xắc | So bài 1 lá | Xì dách | Chơi với người |
| **Game Xóc xóc** | Bầu cua  | Tài xỉu (1 xúc xắc) | Tài xỉu (3 xúc xắc) | Úp ngửa | Xóc đĩa | Có AI hỗ trợ |
| **Game may rủi** | Chẵn lẻ  | Dài ngắn | Đoán màu | Đoán số | Kéo búa bao | Có AI hỗ trợ |
| **Game Flag** | Bài cào  | Ném 1 xúc xắc | Ném 3 xúc xắc | So bài 1 lá | Xì dách | Chơi với người |


> ⚠️ Lưu ý: phần game flag chỉ chơi được khi gõ terminal `Casino.exe [tên game]`
* Xem lịch sử chơi
* Đăng xuất (quay về trang chủ)

---

## Bài viết
* Bài viết trên FB: [Bài viết chính thức trên Facebook](https://www.facebook.com/share/p/1DkLyLTCGQ/)

## Video demo
* Demo bản cũ: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)
* Demo bản mới: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)

---

## Yêu cầu hệ thống

* Trình biên dịch hỗ trợ **C++14** trở lên
* Terminal hỗ trợ hiển thị màu ANSI
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
* Code đã được chỉnh để chạy đa trình dịch trên GNU/GCC trên Windows và Linux
* Giao diện trực quan, tốc độ render cao, phân tách từng sảnh, game rõ ràng
* Cơ chế bảo mật cao tránh trùng lặp và đè dữ liệu lên nhau gây mất dữ liệu

## Hạn chế hiện tại
* Chưa tối ưu kiến trúc file module hoàn chỉnh
* Chưa mở rộng class mà còn lạm dụng struct nhiều
* Logic và giao diện vẫn còn gộp ở một số module
* Còn hardcore vài chổ như biến global 

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**<br>
**Ủng hộ:** [Nếu bạn thấy hữu ích hãy ủng hộ mình](https://github.com/sponsors/trgchinhh)<br>
**GitHub:** [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh. Nếu thấy dự án này thú vị hoặc hữu ích cho bạn, hãy tặng 1 sao cho repo này !!!
