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
* Demo phiên bản cũ: [Xem tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)

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
![Game 2 người](https://github.com/user-attachments/assets/15fc5d79-22dd-49d9-9345-17fcce442742)

### Lịch sử chơi
![Lịch sử chơi](https://github.com/user-attachments/assets/78e624a8-5cb1-4970-ac1d-e5be431e6b1e)

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
