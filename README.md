# CASINO GAME C++

## Giới thiệu

**Casino Game C++** là một dự án game cá cược chạy trên môi trường dòng lệnh (custom TUI), được phát triển bằng ngôn ngữ **C++ (C++17+)**. Dự án mô phỏng nhiều trò chơi cá cược quen thuộc với giao diện ASCII trực quan, hiệu ứng màu sắc và âm thanh, có tích hợp AI, mang lại trải nghiệm sinh động ngay trong terminal.

Dự án được xây dựng với mục tiêu:

* Rèn luyện tư duy lập trình C++ thông qua một project nhỏ
* Xây dựng 1 TUI của riêng mình (để hạn chế việc dùng chuột khi chơi)
* Làm quen với việc tổ chức mã nguồn, tách module và quản lý dữ liệu
* Mô phỏng một hệ thống game có tài khoản, phân quyền, cài đặt, xếp hạng, lịch sử chơi và bảo mật
* Tích hợp AI dự đoán kết quả vào game

Giao diện và cách tổ chức menu được lấy cảm hứng và mở rộng thêm từ dự án trước đó: [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp).

> ⚠️ Lưu ý: Do sử dụng nhiều ký tự đặc biệt và ASCII art, nên khuyến nghị sử dụng các font monospace như **JetBrains Mono Nerd Font**, **Fira Code Nerd Font**, v.v. để hiển thị tốt nhất.

---

## Bài viết
* Bài viết trên facebook chính thức: [Xem tại đây](https://www.facebook.com/share/p/1DkLyLTCGQ/)

---

## Video demo
* Demo bản cũ: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)
* Demo bản mới: [Xem đầy đủ tại đây](https://drive.google.com/drive/my-drive?q=type:video%20parent:0AE8VmzF_NmdGUk9PVA)

![Casino demo](docs/casino-demo.gif)

---

## Chức năng chính

### Trang chủ
* Bật / tắt hiệu ứng âm thanh
* Thông tin game
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
* Xem bảng xếp hạng
* Xóa tài khoản
* Đăng xuất (quay về trang chủ)

> ⚠️ Lưu ý: với Admin thì có thể tạo nhiều tài khoản nhưng đều đến trang quản lý (không có phân chia tài khoản như của User)  

#### Quyền User (Trang game)
* Game Xóc xóc
* Game bài
* Game May rủi
* Game 2 người
* Game flag
* Bảng xếp hạng
* Lịch sử chơi
* Cài đặt
* Đăng xuất (quay về trang chủ)


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

## Ảnh minh họa
<img width="1919" height="1026" alt="image" src="https://github.com/user-attachments/assets/8cf1f487-9092-4e54-b72c-a0d24b55f350" />

---

## Ưu điểm
* Code đã được chỉnh để chạy trên trình biên dịch GNU/GCC trên Windows và Linux

## Hạn chế hiện tại
* Chưa tối ưu kiến trúc file hoàn chỉnh
* Chưa mở rộng class mà còn dùng struct
* Logic và giao diện vẫn còn gộp ở một số module
* Còn lặp lại nhiều chỗ trong main
* Còn hardcore vài chổ như biến global 

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**
GitHub: [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.
