# CASINO GAME C++

## Giới thiệu
- Đây là game console viết bằng ngôn ngữ C++ với nhiều trò khác nhau
- Chạy trên môi trường dòng lệnh (commandline) với thiết kế giao diện dễ chơi và đẹp mắt
- Giao diện lấy cảm hứng từ [quanlysinhvien-cpp](https://github.com/trgchinhh/quanlysinhvien-cpp)

## Liên kết 
### Video demo chương trình
- Vide demo game: [Xem video tại đây](https://drive.google.com/file/d/1d1DOfslxWbXEJcciMRLrhgMa6Re98FzR/view?usp=sharing)

## Chức năng
### Trang chủ: 
- Bật tắt hiệu ứng âm thanh
- Đăng nhập/ Đăng ký/ Xóa tài khoản
- Thoát game
### Trang game
- Tài xỉu 1 xúc xắc / 3 xúc xắc
- Đoán số trong khoảng A -> B
- Chẵn lẻ trong khoảng 0 -> 9
- Tung xu úp ngửa
- Nạp thêm tiền
- Xem lịch sử chơi
- Đăng xuất (quay lại trang chủ)

## Yêu cầu
- Phiên bản C++ 17 trở lên
- Biên dịch bằng Mingw/GNU (g++) 

## Cấu trúc dự án
```
├── data
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
│   ├── lib
│   │   ├── banner.h
│   │   ├── header.h
│   │   ├── json.hpp
│   │   └── picosha2.h
│   ├── resource
│   │   ├── casino.ico
│   │   ├── resource.o
│   │   └── resource.rc
│   └── main.cpp
├── Casino.exe
├── LICENSE
├── build.cpp
├── build.exe
└── cautruc.md
```

## Cài đặt
- Để tự động build chương trình thì cần chạy file: `khoichay.cpp`
- Còn nếu muốn chạy thủ công thì build chương trình theo lệnh: `g++ src\\main.cpp src\\resource\\resource.o -o " + tenchuongtrinh + " -lwinmm -w`

## Screenshot

### 1 Phần đăng nhập
<img width="1918" height="1079" alt="image" src="https://github.com/user-attachments/assets/adbaaf0a-4fa8-445c-bf60-253400fa4c63" />

## 2 Chương trình
<img width="1919" height="1074" alt="image" src="https://github.com/user-attachments/assets/e5201695-7a4c-40e2-b8e2-a312e8e38b14" />

### 1 Tài xỉu 1 xúc xắc
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/655265c6-b02a-4b09-9a08-fa2ca4e53cb7" />

### 2 Tài xỉu 3 xúc xắc 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/69ca24c1-886d-42dc-85bd-d7b69766d226" />

### 3 Đoán số A -> B
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/990bcd7c-06ed-4602-aeb0-7e6b62b83b97" />

### 4 Đoán chẵn lẻ 0 -> 9
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/d684525a-053b-4398-ade8-c06c5d2128f7" />

### 5 Tung xu úp ngửa
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/d40b3fdb-6950-4b13-9e37-9748c10cd8f9" />

### 6 Nạp tiền 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/0c00e8f6-7b6e-4f21-b8ee-916eb6d88ce8" />

### 7 Lịch sử chơi
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/dc15c177-20f7-4932-b39a-f5db86c2aabb" />

### Thoát
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/12d8d082-3914-4bf3-ba4a-6f5a98688edd" />

## Tác giả : Nguyễn Trường Chinh (NTC++)
## Github  : https://github.com/trgchinhh
