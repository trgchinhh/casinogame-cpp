# Cấu trúc dự án 

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

## Lưu ý:
- Để tự động build chương trình thì cần chạy file: `khoichay.cpp`
- Còn nếu muốn chạy thủ công thì build chương trình theo lệnh: `g++ main.cpp resource\\resource.o -o Casino.exe -lwinmm -w`

## Tác giả : Nguyễn Trường Chinh (NTC++)
## Github  : https://github.com/trgchinhh
